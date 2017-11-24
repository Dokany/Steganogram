#include "userwindow.h"
#include "ui_userwindow.h"
#include <QPixmap>
#include <map>
#include <string>
#include <QThread>
#include <iostream>
#include <chrono>
#include <set>
#include <string>
#include <QDir>
#include <QDebug>
#include <QFileInfo>
#include <QFileDialog>

UserWindow::UserWindow(QWidget *parent, Peer& p) :
    QMainWindow(parent),
    ui(new Ui::UserWindow)
{
    cout << "Beginning: Constructing\n";
    this->p = &p;

    ui->setupUi(this);
    QPixmap pix("/home/saraseleem/Downloads/Steganogram/Steganogram/logo.png");
    ui->LogoLabel->setPixmap(pix.scaled(50,50,Qt::KeepAspectRatio));

    model = new QStringListModel(this);
    model_2 = new QStringListModel(this);

    myImageListView();
    t = std::thread(&UserWindow::updateOnlineList,this);
}

void UserWindow::updateOnlineList()
{
    while (1) {
        model->setStringList(list);

        ui->usersList->setModel(model);

        ui->usersList->setEditTriggers(QAbstractItemView::NoEditTriggers);

        std::map<string,pair<string,int> > list_1 = p->getStatus();
        std::map<string,pair<string,int> >::iterator it;

        for(it=list_1.begin();it!=list_1.end();++it)
        {
            list << (it->second.first).c_str();
        }

        list.removeDuplicates();
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void UserWindow::myImageListView()
{
    std::set<string> imgs;

    //const QString folderPath = QFileDialog::getExistingDirectory(this, tr("./Images"));
    const QString folderPath = "Images";

    if(!folderPath.isEmpty())
    {
        QDir mdir(folderPath);
        QStringList filter;

        filter << QLatin1String("*.png");
        filter << QLatin1String("*.jpeg");
        filter << QLatin1String("*.jpg");

        mdir.setNameFilters(filter);

        QFileInfoList filelistinfo = mdir.entryInfoList(filter, QDir::Files|QDir::NoDotAndDotDot);
        cout << (filelistinfo.back().filePath().toStdString())<< " ---------------------------------------------------------\n";

        foreach (const QFileInfo &fileinfo, filelistinfo) {
            cout << "FOREACH---------------------------------------------------------\n";

            QString tmp = fileinfo.fileName();
            list_2 << tmp;

            std::string tmp2 = tmp.toStdString();

            std::cout << tmp2 << std::endl;

            imgs.insert(tmp2);
        }
    }

    model_2->setStringList(list_2);

    ui->myImagesList->setModel(model_2);

    ui->myImagesList->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

UserWindow::~UserWindow()
{
    t.join();
    delete ui;
}


void UserWindow::on_uploadButton_clicked()
{

    QString filename = QFileDialog::getOpenFileName(this,tr("Open File"), "/home/saraseleem/Downloads/", "All Files (*.*);; Png Image (*.png)");
    cout<<filename.toStdString()<<endl;
    string name=filename.toStdString();
    std::reverse(name.begin(),name.end());
    name=name.substr(0,name.find('/'));
    std::reverse(name.begin(),name.end());
    cout<<name<<endl;
    list_2 << name.c_str();
    model_2->setStringList(list_2);
    p->addImage(name,filename.toStdString());
}
