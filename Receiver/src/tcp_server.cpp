#include "tcp_server.h"
Session::Session(tcp::socket socket, bool *is_connection, std::mutex *mutex, std::vector<double> *received_data) : socket_(std::move(socket))
{
    mutex_ = mutex;
    received_data_ = received_data;
    is_connection_ = is_connection;
    is_run_ = true;
}

Session::~Session()
{
    is_run_ = false;
    read_thread_->join();
}

void Session::Start()
{
    read_thread_ = std::make_unique<std::thread>(&Session::Read, this);
}

void Session::Read()
{
    while(is_run_)
    {
        if(socket_.is_open())
        {
            socket_.async_read_some(asio::buffer(data_),std::bind(&Session::OnRead, this, std::placeholders::_1, std::placeholders::_2));
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    }
}

void Session::OnRead(const std::error_code &error, const std::size_t &length)
{
    if(!error && length > 0)
    {
        if(length % sizeof (double) == 0)
        {
            std::vector<double> data(reinterpret_cast<double*>(data_.data()), reinterpret_cast<double*>(data_.data() + length));
            {
                std::lock_guard<std::mutex> lock(*mutex_);
                *received_data_ = data;
            }
        }
    }
    else if (error == asio::error::eof)
    {
        *is_connection_ = false;
        socket_.close();
    }
}

TcpServer::TcpServer(asio::io_context &io_context, unsigned int port, std::mutex *mutex, std::vector<double> *received_data) : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
{
    mutex_ = mutex;
    received_data_ = received_data;
    DoAccept();
}

void TcpServer::DoAccept()
{
    acceptor_.async_accept(std::bind(&TcpServer::OnAccept, this,  std::placeholders::_1, std::placeholders::_2));
}

void TcpServer::OnAccept(const std::error_code &error, tcp::socket socket)
{
    if(!error)
    {
        if(!is_connection_)
        {
            connection_.reset();
            is_connection_ = true;
            connection_ = std::make_shared<Session>(std::move(socket), &is_connection_, mutex_, received_data_);
            connection_->Start();
        }
        DoAccept();
    }
}
