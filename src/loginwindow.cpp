#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QThread>

LoginWindow::LoginWindow(QWidget *parent, Peer &p) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    QPixmap pix("/home/saraseleem/Desktop/Steganogram/Steganogram/logo.png");
    ui->LogoLabel->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));
    ui->authError->hide();
    peer=&p;
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_LoginButton_clicked()
{
    QString username = ui->UsernameLineEdit->text();
    QString password = ui->PasswordLineEdit->text();

    if (peer->login(username.toStdString(),password.toStdString())) {
        //QMessageBox::information(this, "Login", "Username and password are correct");
        hide();
        userWindow = new UserWindow(this, *peer);

        userWindow->show();
    }

    else
        ui->authError->setStyleSheet("color: #ff0000");
        ui->authError->show();
        //QMessageBox::information(this, "Login", "Username and password are not correct");
}

