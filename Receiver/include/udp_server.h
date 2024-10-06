#ifndef UDP_SERVER_H
#define UDP_SERVER_H
#include <iostream>
#include <memory>
#include <string>
#include <functional>
#include <thread>
#include "asio.hpp"

#define DATASIZE_MAX 1024*1024
using asio::ip::udp;
class UdpServer {
public:
    UdpServer(asio::io_context& io_context, unsigned int port, std::mutex *mutex, std::vector<double> *received_data);
    ~UdpServer();
private:
    udp::socket socket_;
    udp::endpoint endpoint_;

    std::array<char, DATASIZE_MAX> data_;

    std::mutex *mutex_;
    std::vector<double> *received_data_;

    std::unique_ptr<std::thread> read_thread_;
    std::atomic_bool is_run_;
private:
    void Read();
    void OnRead(const std::error_code &error, const std::size_t &length);
};
#endif /* UDP_SERVER_H */
