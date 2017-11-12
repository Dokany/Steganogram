#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <QPixmap>

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    QPixmap pix("/Users/macbookair/Desktop/Fall '17/CSCE 445:4411 - Distributed Systems/Project/Steganogram/logo.png");
    ui->LogoLabel->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_LoginButton_clicked()
{
    QString username = ui->UsernameLineEdit->text();
    QString password = ui->PasswordLineEdit->text();

    if (username == "test" && password == "test") {
        QMessageBox::information(this, "Login", "Username and password are correct");
        hide();
        userWindow = new UserWindow(this);
        userWindow->show();
    }

    else
        QMessageBox::information(this, "Login", "Username and password are not correct");
}
