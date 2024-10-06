#include "serial_send.h"
SerialSend::SerialSend(asio::io_context &io_context, const std::string &port_name, unsigned int baud_rate) : serial_port_(io_context)
{
    serial_port_.open(port_name);
    serial_port_.set_option(asio::serial_port_base::baud_rate(baud_rate));
    serial_port_.set_option(asio::serial_port_base::character_size(8));
    serial_port_.set_option(asio::serial_port_base::flow_control(asio::serial_port_base::flow_control::none));
    serial_port_.set_option(asio::serial_port_base::parity(asio::serial_port_base::parity::none));
    serial_port_.set_option(asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::one));
}

SerialSend::~SerialSend()
{
    if (serial_port_.is_open())
    {
        serial_port_.close();
    }
}

void SerialSend::SendData(const std::vector<double> &dataToSend)
{
    asio::async_write(serial_port_, asio::buffer(dataToSend.data(), dataToSend.size()*sizeof (double)),
                      std::bind(&SerialSend::OnSend, this, std::placeholders::_1, std::placeholders::_2));
}

void SerialSend::OnSend(const std::error_code &error, const std::size_t &length)
{
    if(error)
    {
        std::cout << error.message() << std::endl;
    }
}
