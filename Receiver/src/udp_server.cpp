#include "udp_server.h"
UdpServer::UdpServer(asio::io_context &io_context, unsigned int port, std::mutex *mutex, std::vector<double> *received_data)
    : socket_(io_context, udp::endpoint(udp::v4(), port))
{
    mutex_ = mutex;
    received_data_ = received_data;
    is_run_ = true;
    read_thread_ = std::make_unique<std::thread>(&UdpServer::Read, this);
}

UdpServer::~UdpServer()
{
    is_run_ = false;
    read_thread_->join();
}

void UdpServer::Read()
{
    while(is_run_)
    {
        socket_.async_receive_from(asio::buffer(data_), endpoint_, std::bind(&UdpServer::OnRead, this, std::placeholders::_1, std::placeholders::_2));
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void UdpServer::OnRead(const std::error_code &error, const std::size_t &length)
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
