#include "userwindow.h"
#include "ui_userwindow.h"
#include <QPixmap>

UserWindow::UserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserWindow)
{
    ui->setupUi(this);
    QPixmap pix("/Users/macbookair/Desktop/Fall '17/CSCE 445:4411 - Distributed Systems/Project/Steganogram/logo.png");
    ui->LogoLabel->setPixmap(pix.scaled(50,50,Qt::KeepAspectRatio));
}

UserWindow::~UserWindow()
{
    delete ui;
}
