#include "serial_receive.h"

SerialReceive::SerialReceive(asio::io_context &io_context, const std::string &port_name, unsigned int baud_rate, std::mutex *mutex, std::vector<double> *received_data) : serial_port_(io_context)
{
    serial_port_.open(port_name);
    serial_port_.set_option(asio::serial_port_base::baud_rate(baud_rate));
    serial_port_.set_option(asio::serial_port_base::baud_rate(baud_rate));
    serial_port_.set_option(asio::serial_port_base::character_size(8));
    serial_port_.set_option(asio::serial_port_base::flow_control(asio::serial_port_base::flow_control::none));
    serial_port_.set_option(asio::serial_port_base::parity(asio::serial_port_base::parity::none));
    serial_port_.set_option(asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::one));
    mutex_ = mutex;
    received_data_ = received_data;
    is_run_ = true;
    if(serial_port_.is_open())
    {
        read_thread_ = std::make_unique<std::thread>(&SerialReceive::Read, this);
    }
}

SerialReceive::~SerialReceive()
{
    is_run_ = false;
    read_thread_->join();
    if (serial_port_.is_open())
    {
        serial_port_.close();
    }
}

void SerialReceive::Read()
{
    while(is_run_)
    {
        serial_port_.async_read_some(asio::buffer(data_), std::bind(&SerialReceive::OnRead, this, std::placeholders::_1, std::placeholders::_2));
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void SerialReceive::OnRead(const std::error_code &error, const std::size_t &length)
{
    if(!error && length > 0)
    {
        if(length % sizeof (double) == 0)
        {
            std::vector<double> data(reinterpret_cast<double*>(data_.data()), reinterpret_cast<double*>(data_.data() + length));
            {
                std::lock_guard<std::mutex> lock(*mutex_);
                *received_data_ = data;
            }
        }
    }
}
