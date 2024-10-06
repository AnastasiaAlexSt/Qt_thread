#include "udp_client.h"
UdpClient::UdpClient(asio::io_context &io_context, const std::string &host, const unsigned int port) : socket_(io_context, udp::endpoint(udp::v4(), 0))
{
    udp::resolver resolver(io_context);
    udp::resolver::query query(udp::v4(), host, std::to_string(port));
    udp::resolver::iterator iter = resolver.resolve(query);
    endpoint_ = *iter;
}

void UdpClient::SendData(const std::vector<double> &dataToSend)
{
    socket_.async_send_to(asio::buffer(dataToSend.data(), dataToSend.size()*sizeof (double)), endpoint_,
                          std::bind(&UdpClient::OnSend, this, std::placeholders::_1, std::placeholders::_2));
}

void UdpClient::OnSend(const std::error_code &error, const std::size_t &length)
{
    if(error)
    {
        std::cout << error.message() << std::endl;
    }
}
