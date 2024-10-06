#include "receiver.h"
#include "./ui_receiver.h"

Receiver::Receiver(QWidget *parent) : QMainWindow(parent), ui(new Ui::Receiver)
{
    ui->setupUi(this);
    SetSize();
    ConnectSlots();
    Init();
}

Receiver::~Receiver()
{
    is_running_task_ = false;
    io_context_.stop();
    io_thread_->join();
    graph_thread_->join();
    delete ui;
}

void Receiver::SetSettings(const unsigned int tcp_port, const unsigned int udp_port, const std::string serial_port)
{
    tcp_server_ = std::make_unique<TcpServer>(io_context_, tcp_port, &m_tcp_, &tcp_data_);
    udp_server_ = std::make_unique<UdpServer>(io_context_, udp_port, &m_udp_, &udp_data_);
    serial_receive_ = std::make_unique<SerialReceive>(io_context_, serial_port, 115200, &m_serial_, &serial_data_);
    Start();
}

void Receiver::Init()
{
    ui->tcp_plot->clearGraphs();
    ui->serial_plot->clearGraphs();
    ui->udp_plot->clearGraphs();
    m_serial_.unlock();
    m_udp_.unlock();
    m_tcp_.unlock();

    qRegisterMetaType<DataPlot>("DataPlot");
}

void Receiver::ConnectSlots()
{
    connect(this, &Receiver::DoDraw, this, &Receiver::DrawPlot);
    connect(this, &Receiver::DoDrawTwoPlot, this, &Receiver::DrawTwoPlot);
    connect(this, &Receiver::DoLog, this, &Receiver::AddLog);
}

void Receiver::Start()
{
    is_running_task_ = true;
    io_thread_ = std::make_unique<std::thread>(&Receiver::DoConnect, this);
    graph_thread_ = std::make_unique<std::thread>(&Receiver::DrawAllData, this);
}

void Receiver::SetSize()
{
    ui->tcp_logs->setFixedWidth(this->width()/3);
    ui->udp_logs->setFixedWidth(this->width()/3);
    ui->serial_logs->setFixedWidth(this->width()/3);
    ui->tcp_gb->setFixedHeight(this->height()*0.2);
    ui->udp_gb->setFixedHeight(this->height()*0.2);
    ui->serial_gb->setFixedHeight(this->height()*0.2);
    ui->result_gb->setFixedHeight(this->height()*0.2);
}

void Receiver::DoConnect()
{
    io_context_.run();
}


void Receiver::DrawAllData()
{
    while(is_running_task_)
    {
        DataPlot tcp_plot_data;
        if(HandleData(tcp_data_, tcp_plot_data, &m_tcp_))
        {
            tcp_plot_data_mem_ = tcp_plot_data;
            emit DoDraw(ui->tcp_plot, tcp_plot_data);
            emit DoLog(ui->tcp_logs, tcp_plot_data.log);
        }

        DataPlot udp_plot_data;
        if(HandleData(udp_data_, udp_plot_data, &m_udp_))
        {
            udp_plot_data_mem_ = udp_plot_data;
            emit DoDraw(ui->udp_plot, udp_plot_data);
            emit DoLog(ui->udp_logs, udp_plot_data.log);
        }

        DataPlot serial_plot_data_;
        if(HandleData(serial_data_, serial_plot_data_, &m_serial_))
        {
            serial_plot_data_mem_ = serial_plot_data_;
            emit DoDraw(ui->serial_plot, serial_plot_data_);
            emit DoLog(ui->serial_logs, serial_plot_data_.log);
        }

        DataPlot data_sum, data_mul;
        if(GetSumAndMulData(data_sum, data_mul))
        {
            emit DoDrawTwoPlot(ui->result_plot, data_sum, data_mul);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

bool Receiver::HandleData(std::vector<double> &data_rec, DataPlot &data_plot, std::mutex *mtx)
{
    QVector<double> data;
    {
        std::lock_guard<std::mutex> lock_serial(*mtx);
        if(data_rec.empty()){return false;}

        data = QVector<double>::fromStdVector(data_rec);
        data_rec.clear();
    }
    data_plot.max_value = *std::max_element(data.begin(), data.end());
    data_plot.min_value = *std::min_element(data.begin(), data.end());

    data_plot.log = "Receive data: \n";
    for(int i = 0; i < data.size(); i++)
    {
        data_plot.log += QString::number(data[i]) + " ";
        data_plot.x.push_back(i);
        data_plot.y.push_back(data[i]);
    }
    return true;
}

bool Receiver::GetSumAndMulData(DataPlot &data_sum, DataPlot &data_mul)
{
    if(tcp_plot_data_mem_.y.empty() || udp_plot_data_mem_.y.empty() || serial_plot_data_mem_.y.empty()){return false;}
    std::vector<int> ticks{tcp_plot_data_mem_.x.size(), udp_plot_data_mem_.x.size(), serial_plot_data_mem_.x.size()};
    unsigned int max_ticks = *std::max_element(ticks.begin(), ticks.end());

    QVector<double> el_sum, el_mul;

    for(unsigned int i = 0; i < max_ticks; ++i)
    {
        el_sum.clear();
        el_mul.clear();
        data_sum.x.push_back(i);
        data_mul.x.push_back(i);

        el_sum.push_back(AddData(i, tcp_plot_data_mem_));
        el_sum.push_back(AddData(i, udp_plot_data_mem_));
        el_sum.push_back(AddData(i, serial_plot_data_mem_));

        el_mul.push_back(AddData(i, tcp_plot_data_mem_, 1));
        el_mul.push_back(AddData(i, udp_plot_data_mem_, 1));
        el_mul.push_back(AddData(i, serial_plot_data_mem_, 1));


        double sum = std::accumulate(el_sum.begin(), el_sum.end(), 0.0);
        double mul = std::accumulate(el_mul.begin(), el_mul.end(), 1.0, std::multiplies<double>());
        data_sum.y.push_back(sum);
        data_mul.y.push_back(mul);
    }


    data_sum.max_value= *std::max_element(data_sum.y.begin(), data_sum.y.end());
    data_sum.min_value= *std::min_element(data_sum.y.begin(), data_sum.y.end());
    data_mul.max_value= *std::max_element(data_mul.y.begin(), data_mul.y.end());
    data_mul.min_value= *std::min_element(data_mul.y.begin(), data_mul.y.end());
    return true;
}

double Receiver::AddData(unsigned int i, const DataPlot &data, double empty_data)
{
    if(i < data.x.size())
    {
        return data.y[i];
    }
    {
        return empty_data;
    }
}

void Receiver::DrawPlot(QCustomPlot *plot, DataPlot data_plot)
{
    plot->clearGraphs();
    plot->xAxis->setRange(0,data_plot.x.size());
    plot->yAxis->setRange(data_plot.min_value,data_plot.max_value);
    plot->addGraph();
    plot->graph(0)->addData(data_plot.x,data_plot.y);
    plot->replot();
}

void Receiver::DrawTwoPlot(QCustomPlot *plot, DataPlot data_plot_1, DataPlot data_plot_2)
{
    double min = data_plot_1.min_value < data_plot_2.min_value ? data_plot_1.min_value : data_plot_2.min_value;
    double max = data_plot_1.max_value > data_plot_2.max_value ? data_plot_1.max_value : data_plot_2.max_value;
    plot->clearGraphs();
    plot->legend->setVisible(true);
    plot->legend->setBrush(QBrush(QColor(255,255,255,230)));
    plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);
    plot->xAxis->setRange(0,data_plot_1.x.size());
    plot->yAxis->setRange(min,max);


    plot->addGraph();
    plot->graph(0)->setPen(QPen(Qt::blue));
    plot->graph(0)->addData(data_plot_1.x,data_plot_1.y);
    plot->graph(0)->setName("Sum");

    plot->addGraph();
    plot->graph(1)->setPen(QPen(Qt::red));
    plot->graph(1)->addData(data_plot_2.x,data_plot_2.y);
    plot->graph(1)->setName("Product");
    plot->replot();
}

void Receiver::AddLog(QTextBrowser *browser, const QString &log)
{
    browser->append(log);
}

void Receiver::resizeEvent(QResizeEvent *event)
{
    SetSize();
}



