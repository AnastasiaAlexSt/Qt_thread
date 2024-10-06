#ifndef RECEIVER_H
#define RECEIVER_H

#include <QMainWindow>
#include <QVector>
#include <QResizeEvent>
#include <thread>
#include <cmath>
#include <algorithm>
#include <vector>
#include "asio.hpp"
#include "qcustomplot.h"
#include "tcp_server.h"
#include "udp_server.h"
#include "serial_receive.h"


struct DataPlot
{
    QVector<double> x;
    QVector<double> y;
    double min_value = 0;
    double max_value = 0;
    QString log;
};

QT_BEGIN_NAMESPACE
namespace Ui { class Receiver; }
QT_END_NAMESPACE

class Receiver : public QMainWindow
{
    Q_OBJECT

public:
    Receiver(QWidget *parent = nullptr);
    ~Receiver();
    void SetSettings(const unsigned int tcp_port, const unsigned int udp_port, const std::string serial_port);

    signals:
    void DoDraw(QCustomPlot *plot, DataPlot data_plot);
    void DoDrawTwoPlot(QCustomPlot *plot, DataPlot data_plot_1, DataPlot data_plot_2);
    void DoLog(QTextBrowser *browser, const QString &log);

private:
    Ui::Receiver *ui;
    std::unique_ptr<std::thread> io_thread_;
    std::unique_ptr<std::thread> graph_thread_;

    asio::io_context io_context_;
    std::atomic_bool is_running_task_;
    std::unique_ptr<TcpServer> tcp_server_;
    std::unique_ptr<UdpServer> udp_server_;
    std::unique_ptr<SerialReceive> serial_receive_;

    std::mutex m_tcp_, m_udp_, m_serial_;
    std::vector<double> tcp_data_;
    std::vector<double> udp_data_;
    std::vector<double> serial_data_;
    DataPlot tcp_plot_data_mem_;
    DataPlot udp_plot_data_mem_;
    DataPlot serial_plot_data_mem_;

    private:
    void Init();
    void SetSize();
    void DoConnect();
    void ConnectSlots();
    void Start();

    void DrawAllData();
    bool HandleData(std::vector<double> &data_rec, DataPlot &data_plot, std::mutex *mtx);
    bool GetSumAndMulData(DataPlot &data_sum, DataPlot &data_mul);
    double AddData(unsigned int i, const DataPlot &data, double empty_data = 0);
    void DrawPlot(QCustomPlot *plot, DataPlot data_plot);
    void DrawTwoPlot(QCustomPlot *plot, DataPlot data_plot_1, DataPlot data_plot_2);
    void AddLog(QTextBrowser *browser, const QString &log);

    void resizeEvent(QResizeEvent *event) override;
};
#endif // RECEIVER_H
