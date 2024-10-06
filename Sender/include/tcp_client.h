#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H
#include <iostream>
#include <asio.hpp>
#include <string>
#include <functional>
using asio::ip::tcp;

class TcpClient
{
public:
    TcpClient(asio::io_context& io_context, const std::string& host, const unsigned int port);
    ~TcpClient();
    void SendData(const std::vector<double> &dataToSend);

private:
    tcp::socket socket_;
private:
    void Connect(asio::ip::tcp::resolver::results_type endpoints);
    void OnConnect(const std::error_code &error, tcp::endpoint endpoint);
    void OnSend(const std::error_code &error, const std::size_t &length);
};


#endif // TCP_CLIENT_H
