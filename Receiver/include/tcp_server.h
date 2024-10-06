#ifndef TCP_SERVER_H
#define TCP_SERVER_H
#include <iostream>
#include <memory>
#include <string>
#include <functional>
#include <thread>
#include "asio.hpp"

#define DATASIZE_MAX 1024*1024

using asio::ip::tcp;
class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket, bool *is_connection, std::mutex *mutex, std::vector<double> *received_data);
    ~Session();
    void Start();

private:
    tcp::socket socket_;
    bool *is_connection_;

    std::array<uint8_t, DATASIZE_MAX> data_;

    std::mutex *mutex_;
    std::vector<double> *received_data_;

    std::unique_ptr<std::thread> read_thread_;
    std::atomic_bool is_run_;
private:
    void Read();
    void OnRead(const std::error_code &error, const std::size_t &length);
};

class TcpServer
{
public:
    TcpServer(asio::io_context& io_context, unsigned int port, std::mutex *mutex, std::vector<double> *received_data);

private:
    bool is_connection_ = false;
    std::shared_ptr<Session> connection_;
    tcp::acceptor acceptor_;

    std::mutex *mutex_;
    std::vector<double> *received_data_;
private:
    void DoAccept();
    void OnAccept(const std::error_code &error, tcp::socket socket);
};
#endif /* TCP_SERVER_H */
