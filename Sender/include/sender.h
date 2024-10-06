#ifndef SENDER_H
#define SENDER_H

#include <QMainWindow>
#include <QPushButton>
#include <thread>
#include <cmath>
#include <atomic>
#include <chrono>
#include <random>
#include "asio.hpp"
#include "tcp_client.h"
#include "udp_client.h"
#include "serial_send.h"
#include "datasendwidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Sender; }
QT_END_NAMESPACE


struct SinCosData
{
    int amplitude;
    int w;
    int phase;
};

class Sender : public QMainWindow
{
    Q_OBJECT

public:
    Sender(QWidget *parent = nullptr);
    ~Sender();
    void SetSettings(const unsigned int tcp_port, const unsigned int udp_port, const std::string serial_port);

private:
    Ui::Sender *ui;
    std::unique_ptr<std::thread> io_thread_;
    std::unique_ptr<std::thread> tcp_thread_;
    std::unique_ptr<std::thread> udp_thread_;
    std::unique_ptr<std::thread> serial_thread_;
    asio::io_context io_context_;
    std::unique_ptr<TcpClient> tcp_client_;
    std::unique_ptr<UdpClient> udp_client_;
    std::unique_ptr<SerialSend> serial_send_;
    std::atomic_bool is_run_tasks_ = false;

    void Start();
    void DoConnect();

    void OnSendTcp();
    void OnSendUdp();
    void OnSendSerial();

    std::vector<double> GetData(DataSendWidget *widget);
};
#endif // SENDER_H
