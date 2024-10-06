#include <QApplication>
#include "receiver.h"

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        std::cerr << "Usage: <port_tcp> <port_udp> <com_port>\n";
        return 1;
    }
    QApplication a(argc, argv);
    Receiver w;
    w.SetSettings(std::stoi(argv[1]), std::stoi(argv[2]), argv[3]);
    w.show();
    return a.exec();
}
