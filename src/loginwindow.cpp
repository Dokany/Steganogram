#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QThread>
#include <iostream>

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    QPixmap pix("/home/saraseleem/Desktop/Steganogram/Steganogram/logo.png");
    ui->LogoLabel->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));
    ui->authError->hide();
    peer = new Peer("10.7.57.229",4444,"10.7.57.200",4444);
  //  peer=&p;
    this->setAttribute( Qt::WA_QuitOnClose, false );
}

void LoginWindow::on_LoginButton_clicked()
{
    QString username = ui->UsernameLineEdit->text();
    QString password = ui->PasswordLineEdit->text();

    if (peer->login(username.toStdString(),password.toStdString())) {
        //QMessageBox::information(this, "Login", "Username and password are correct");
        hide();
        std::cout << "login sucessfully\n";
        userWindow = new UserWindow(this, peer);
        std::cout << "call user window\n";
        userWindow->show();
        reset();
    }

    else
    {
        ui->authError->setStyleSheet("color: #ff0000");
        ui->authError->show();
    }
        //QMessageBox::information(this, "Login", "Username and password are not correct");

}
void LoginWindow::reset()
{
    ui->UsernameLineEdit->clear();
    ui->PasswordLineEdit->clear();
    ui->authError->hide();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}
