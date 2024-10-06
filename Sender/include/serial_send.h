#ifndef SERIAL_SEND_H
#define SERIAL_SEND_H
#include <iostream>
#include <memory>
#include <string>
#include <functional>
#include "asio.hpp"

class SerialSend
{
public:
    SerialSend(asio::io_context& io_context, const std::string& port_name, unsigned int baud_rate);
    ~SerialSend();
    void SendData(const std::vector<double> &dataToSend);

private:
    asio::serial_port serial_port_;

private:
    void OnSend(const std::error_code &error, const std::size_t &length);
};

#endif /* SERIAL_SEND_H */
