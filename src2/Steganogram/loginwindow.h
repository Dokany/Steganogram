#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "userwindow.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent);
    ~LoginWindow();
    void reset();

private slots:
    void on_LoginButton_clicked();

private:
    Ui::LoginWindow *ui;
    UserWindow * userWindow;
    Peer* peer;
};

#endif // LOGINWINDOW_H
