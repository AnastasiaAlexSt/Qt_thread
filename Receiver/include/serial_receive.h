#ifndef SERIAL_RECEIVE_H
#define SERIAL_RECEIVE_H
#include <iostream>
#include <memory>
#include <string>
#include <functional>
#include <thread>

#include "asio.hpp"
#define DATASIZE_MAX 1024*1024
class SerialReceive
{
public:
    SerialReceive(asio::io_context& io_context, const std::string& port_name, unsigned int baud_rate, std::mutex *mutex, std::vector<double> *received_data);
    ~SerialReceive();

private:
    asio::serial_port serial_port_;

    std::array<uint8_t, DATASIZE_MAX> data_;

    std::mutex *mutex_;
    std::vector<double> *received_data_;

    std::unique_ptr<std::thread> read_thread_;
    std::atomic_bool is_run_;

private:
    void Read();
    void OnRead(const std::error_code &error, const std::size_t &length);
};

#endif /* SERIAL_RECEIVE_H */
