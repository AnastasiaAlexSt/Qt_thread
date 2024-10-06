#include "tcp_client.h"
TcpClient::TcpClient(asio::io_context &io_context, const std::string &host, const unsigned int port) : socket_(io_context)
{
    asio::ip::tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(host, std::to_string(port));
    Connect(endpoints);
}

TcpClient::~TcpClient()
{
    socket_.close();
}

void TcpClient::SendData(const std::vector<double> &dataToSend) {
    asio::async_write(socket_, asio::buffer(dataToSend.data(), dataToSend.size()*sizeof (double)),
                      std::bind(&TcpClient::OnSend, this, std::placeholders::_1, std::placeholders::_2));
}

void TcpClient::Connect(asio::ip::tcp::resolver::results_type endpoints)
{
    asio::async_connect(socket_, endpoints, std::bind(&TcpClient::OnConnect, this, std::placeholders::_1, std::placeholders::_2));

}

void TcpClient::OnConnect(const std::error_code &error, tcp::endpoint endpoint)
{
    if (error)
    {
        std::cout << error.message() << std::endl;
    }
}

void TcpClient::OnSend(const std::error_code &error, const std::size_t &length)
{
    if(error)
    {
        std::cout << error.message() << std::endl;
    }
}
