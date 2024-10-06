#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H
#include <iostream>
#include <string>
#include <functional>
#include "asio.hpp"

using asio::ip::udp;

class UdpClient
{
public:
    UdpClient(asio::io_context& io_context, const std::string& host, const unsigned int port);
    void SendData(const std::vector<double> &dataToSend);
private:
    udp::socket socket_;
    udp::endpoint  endpoint_;

private:

    void OnSend(const std::error_code &error, const std::size_t &length);
};
#endif // UDP_CLIENT_H
