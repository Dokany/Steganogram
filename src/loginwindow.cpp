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
    QPixmap pix("logo.png");
    ui->LogoLabel->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));
    ui->authError->hide();
    peer = new Peer("10.7.57.117",4454,"10.7.57.200",4444);
  //  peer=&p;
    this->setAttribute( Qt::WA_QuitOnClose, false );
}

void LoginWindow::on_LoginButton_clicked()
{
    QString username = ui->UsernameLineEdit->text();
    QString password = ui->PasswordLineEdit->text();
    int ret=peer->login(username.toStdString(),password.toStdString());
    if (ret==1) {
        //QMessageBox::information(this, "Login", "Username and password are correct");
        hide();
        std::cout << "login sucessfully\n";
        userWindow = new UserWindow(this, peer, username.toStdString());
        std::cout << "call user window\n";
        userWindow->show();
        reset();
    }

    else if(ret==0)
    {
        ui->authError->setStyleSheet("color: #ff0000");
        ui->authError->show();
    }
    else
    {
        reset();
        QMessageBox::warning(this,"Connection Error!", "Cannot connect to service... \n");
    }

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
