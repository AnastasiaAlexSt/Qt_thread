#include "datasendwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DataSendWidget w;
    w.show();
    return a.exec();
}
