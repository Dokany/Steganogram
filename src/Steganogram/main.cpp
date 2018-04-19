#include "loginwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    LoginWindow w(0);
    w.show();

    return a.exec();
}
