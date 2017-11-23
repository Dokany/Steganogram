#include "userwindow.h"
#include "ui_userwindow.h"
#include <QPixmap>
#include <map>
#include <string>
#include <QThread>
#include<iostream>

UserWindow::UserWindow(QWidget *parent, Peer& p) :
    QMainWindow(parent),
    ui(new Ui::UserWindow)
{
    this->p = &p;

    ui->setupUi(this);
    QPixmap pix("/home/saraseleem/Desktop/Steganogram/Steganogram/logo.png");
    ui->LogoLabel->setPixmap(pix.scaled(50,50,Qt::KeepAspectRatio));

    etsaraf();


}
void UserWindow::etsaraf()
{

    QThread::sleep(30);

    std::map<string,pair<string,int> > list = p->getStatus();
    std::map<string,pair<string,int> >::iterator it;
    cout<<"I am here"<<endl;
    for(it=list.begin();it!=list.end();++it)
    {
        cout<<it->second.first<<endl;
        ui->Online_Users_list->addItem((it->second.first).c_str());
    }
    ui->Online_Users_list->update();
}

UserWindow::~UserWindow()
{
    delete ui;
}

