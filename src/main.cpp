#include "loginwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    Peer p("10.7.57.229",4444,"10.7.57.200",4444);
    QApplication a(argc, argv);
    LoginWindow w(0,p);
    w.show();

    return a.exec();
}
