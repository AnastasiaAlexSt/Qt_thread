#include "sender.h"
#include "./ui_sender.h"

Sender::Sender(QWidget *parent): QMainWindow(parent), ui(new Ui::Sender)
{
    ui->setupUi(this);
    ui->tcp_widget->SetInitHarmonicParameters(1, 25, 0);
    ui->udp_widget->SetInitHarmonicParameters(1, 50, 0);
    ui->serial_widget->SetInitHarmonicParameters(1, 75, 0);
}

Sender::~Sender()
{
    is_run_tasks_ = false;
    io_context_.stop();
    io_thread_->join();
    tcp_thread_->join();
    udp_thread_->join();
    serial_thread_->join();
    delete ui;
}

void Sender::SetSettings(const unsigned int tcp_port, const unsigned int udp_port, const std::string serial_port)
{
    tcp_client_ = std::make_unique<TcpClient>(io_context_, "127.0.0.1", tcp_port);
    udp_client_ = std::make_unique<UdpClient>(io_context_, "127.0.0.1", udp_port);
    serial_send_ = std::make_unique<SerialSend>(io_context_, serial_port, 115200);
    Start();
}

void Sender::Start()
{
    io_thread_ = std::make_unique<std::thread>(&Sender::DoConnect, this);
    tcp_thread_ = std::make_unique<std::thread>(&Sender::OnSendTcp, this);
    udp_thread_ = std::make_unique<std::thread>(&Sender::OnSendUdp, this);
    serial_thread_ = std::make_unique<std::thread>(&Sender::OnSendSerial, this);
}

void Sender::OnSendTcp()
{
    while(is_run_tasks_)
    {
        std::vector<double> dataToSend = GetData(ui->tcp_widget);
        tcp_client_->SendData(dataToSend);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void Sender::OnSendUdp()
{
    while(is_run_tasks_)
    {
        std::vector<double> dataToSend = GetData(ui->udp_widget);
        udp_client_->SendData(dataToSend);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void Sender::OnSendSerial()
{
    while(is_run_tasks_)
    {
        std::vector<double> dataToSend = GetData(ui->serial_widget);
        serial_send_->SendData(dataToSend);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

std::vector<double> Sender::GetData(DataSendWidget *widget)
{
    std::vector<double> dataToSend;
    DataSendWidgetInfo::TypeFunction type = widget->GetTypeFunction();
    if(type == DataSendWidgetInfo::TypeFunction::sin || type == DataSendWidgetInfo::TypeFunction::cos)
    {

        int a = widget->GetAmplitude();
        int f =  widget->GetFrequency();
        double p = widget->GetPhase() * M_PI / 180.0;
        int fd = 1000;
        double w = 2 * M_PI * f / fd;
        int N = 100;
        for(int i = 0 ; i < N; i++)
        {
            if(type == DataSendWidgetInfo::TypeFunction::sin)
            {
                dataToSend.push_back(a*std::sin(w*i+p));
            }
            else
            {
               dataToSend.push_back(a*std::cos(w*i+p));
            }
        }
    }
    else if(type == DataSendWidgetInfo::TypeFunction::random)
    {
        std::random_device rd;
        std::mt19937 g(rd());

        dataToSend.resize(100);

        std::uniform_int_distribution<int> num{-100, 100};
        auto gen = [&](){return num(g);};
        std::generate(dataToSend.begin(), dataToSend.end(), gen);
    }

    return dataToSend;
}

void Sender::DoConnect()
{
    is_run_tasks_ = true;
    io_context_.run();
}




