#include "userwindow.h"
#include "ui_userwindow.h"
#include "imageviewer.h"
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
#include <QWidget>

UserWindow::UserWindow(QWidget *parent, Peer* p) :
    QMainWindow(parent),
    ui(new Ui::UserWindow)
{
    cout << "Beginning: Constructing\n";
    this->p = p;
    cout<<"Copying Peer\n";
    ui->setupUi(this);
    cout<<"Setup UI\n";
    QPixmap pix("logo.png");
    ui->LogoLabel->setPixmap(pix.scaled(50,50,Qt::KeepAspectRatio));
    cout<<"middle\n";
    model = new QStringListModel(this);
    model_2 = new QStringListModel(this);
    cout<<"after models\n";
    viewImageWidget();
    viewSharedWidget();
    //working=true;

    // Updates Online User List
    //updateOnlineList();
    updateOnlineWidget();

    //t = std::thread(&UserWindow::updateOnlineList,this);
    cout<<"construction done";
}

//void UserWindow::updateOnlineList()
//{
//    model->setStringList(list);

//    ui->usersList->setModel(model);

//    ui->usersList->setEditTriggers(QAbstractItemView::NoEditTriggers);

//    std::map<string,pair<string,int> > list_1 = p->getStatus();
//    std::map<string,pair<string,int> >::iterator it;

//    for(it=list_1.begin();it!=list_1.end();++it)
//    {
//        list << (it->second.first).c_str();
//    }

//    list.removeDuplicates();
//}


void UserWindow:: viewImageWidget()
{
    std::set<string> imgs;

    const QString folderPath = "Images/";
     if(folderPath.isEmpty())cout<<"EMPTY --fbadf\n";
    if(!folderPath.isEmpty())
    {
        cout<<"NOT EMPTY -asdas\n";
        QDir mdir(folderPath);
        QStringList filter;
        cout<<"NOT EMPTY -2\n";

        filter << QLatin1String("*.png");
        filter << QLatin1String("*.jpeg");
        filter << QLatin1String("*.jpg");
        cout<<"NOT EMPTY -3\n";

        mdir.setNameFilters(filter);
        cout<<"NOT EMPTY -4\n";

        QFileInfoList filelistinfo = mdir.entryInfoList(filter, QDir::Files|QDir::NoDotAndDotDot);
        cout<<"NOT EMPTY -5\n";
       // cout << (filelistinfo.back().filePath().toStdString())<< " ---------------------------------------------------------\n";

        foreach (const QFileInfo &fileinfo, filelistinfo) {
            cout << "FOREACH---------------------------------------------------------\n";

            QString tmp = fileinfo.fileName();
            ui->imageWidget->addItem(tmp);
            std::string tmp2 = tmp.toStdString();

            std::cout << tmp2 << std::endl;

            imgs.insert(tmp2);
        }
    }

    //model_2->setStringList(list_2);

    //ui->imageWidget->setModel(model_2);

    ui->imageWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void UserWindow:: viewSharedWidget()
{
    std::set<string> imgs;

    const QString folderPath = ".Shared/";

    if(folderPath.isEmpty())cout<<"EMPTY --fbadf\n";
    if(!folderPath.isEmpty())
    {
        cout<<"NOT EMPTY -asdas\n";
        QDir mdir(folderPath);
        QStringList filter;
        cout<<"NOT EMPTY -2\n";

        filter << QLatin1String("*.png");
        filter << QLatin1String("*.jpeg");
        filter << QLatin1String("*.jpg");
        cout<<"NOT EMPTY -3\n";

        mdir.setNameFilters(filter);
        cout<<"NOT EMPTY -4\n";

        QFileInfoList filelistinfo = mdir.entryInfoList(filter, QDir::Files|QDir::NoDotAndDotDot);
        cout<<"NOT EMPTY -5\n";
       // cout << (filelistinfo.back().filePath().toStdString())<< " ---------------------------------------------------------\n";

        foreach (const QFileInfo &fileinfo, filelistinfo) {
            cout << "FOREACH---------------------------------------------------------\n";

            QString tmp = fileinfo.fileName();
            ui->imageWidget->addItem(tmp);
            std::string tmp2 = tmp.toStdString();

            std::cout << tmp2 << std::endl;

            imgs.insert(tmp2);
        }
    }

    //model_2->setStringList(list_2);

    //ui->imageWidget->setModel(model_2);

    ui->imageWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void UserWindow::on_imageWidget_itemClicked(QListWidgetItem *item)
{
    QString qs = item->text();
    string s = qs.toStdString();
    cout << "File Name ---------- " << s;
    QMessageBox* imageOptions = new QMessageBox(this);

    //imageOptions.setWindowFlags(Qt::WindowStaysOnTopHint);

    imageOptions->setWindowTitle("Image Options");
    imageOptions->setText("Select Image Options");

    QAbstractButton* pButtonView = imageOptions->addButton(tr("View"), QMessageBox::ActionRole);
    QAbstractButton* pButtonDelete =imageOptions->addButton(tr("Delete"), QMessageBox::ActionRole);
    QAbstractButton* pButtonCancel =imageOptions->addButton(tr("Cancel"), QMessageBox::NoRole);

    imageOptions->exec();

    if (imageOptions->clickedButton()==pButtonView) {
        // Opening ImageViewer Pop-up Window
        iv = new imageviewer(this, std::string("Images/"+s), true, *p);
        iv->show();
    }
    else if (imageOptions->clickedButton()==pButtonDelete)
    {
        this->activateWindow();
        //this->setWindowFlags(Qt::WindowSystemMenuHint);

        // Delete image from directory
        string command = "rm -f Images/" + s;

        char* command_char = new char[command.length()+1];
        strcpy(command_char, command.c_str());
        system(command_char);

        // Remove filename from imageWidget
        delete ui->imageWidget->takeItem(ui->imageWidget->row(item));
    }
}

void UserWindow::on_uploadButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open File"), "/home/saraseleem/Desktop/", "All Files (*.*);; Png Image (*.png)");
    cout<<filename.toStdString()<<endl;
    string name=filename.toStdString();
    std::reverse(name.begin(),name.end());
    name=name.substr(0,name.find('/'));
    std::reverse(name.begin(),name.end());
    cout<<name<<endl;
    ui->imageWidget->addItem(name.c_str());
    p->addImage(name,filename.toStdString());
}

void UserWindow::on_LogoutButton_clicked()
{
//    loginWindow = new LoginWindow(this, *p);
//    LoginWindow->show();
//    working=false;
//    t.join();
     //this->activateWindow();
    // this->setWindowFlags(Qt::WindowCloseButtonHint);
     //this->hide();
   // LoginWindow * login = new LoginWindow(this, p);
   // login->show();
    //this->parentWidget()->show();
    p->logOff();
this->parentWidget()->show();
    this->close();

}

void UserWindow::on_RefreshButton_clicked()
{
    // Updates Online User List
   updateOnlineWidget();
}


void UserWindow::updateOnlineWidget()
{
    //model->setStringList(list);

    //ui->usersList->setModel(model);
    ui->usersWidget->clear();

    ui->usersWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    std::map<string,pair<string,int> > list_1 = p->getStatus();
    std::map<string,pair<string,int> >::iterator it;

    for(it=list_1.begin();it!=list_1.end();++it)
    {
        ui->usersWidget->addItem((it->second.first).c_str());
    }
}

void UserWindow::on_sharedWidget_itemClicked(QListWidgetItem *item)
{
    QString qs = item->text();
    string s = qs.toStdString();
    cout << "File Name ---------- " << s;
    QMessageBox* imageOptions = new QMessageBox(this);

    //imageOptions.setWindowFlags(Qt::WindowStaysOnTopHint);

    imageOptions->setWindowTitle("Image Options");
    imageOptions->setText("Select Image Options");

    QAbstractButton* pButtonView = imageOptions->addButton(tr("View"), QMessageBox::YesRole);
    QAbstractButton* pButtonDelete =imageOptions->addButton(tr("Delete"), QMessageBox::NoRole);

    imageOptions->exec();

    if (imageOptions->clickedButton()==pButtonView) {
        // Opening ImageViewer Pop-up Window
        iv = new imageviewer(this, std::string(".Shared/"+s), false, *p);
        iv->show();
    }
    else if (imageOptions->clickedButton()==pButtonDelete)
    {
        this->activateWindow();
        //this->setWindowFlags(Qt::WindowSystemMenuHint);

        // Delete image from directory
        string command = "rm -f .Shared/" + s;

        char* command_char = new char[command.length()+1];
        strcpy(command_char, command.c_str());
        system(command_char);

        // Remove filename from imageWidget
        delete ui->sharedWidget->takeItem(ui->sharedWidget->row(item));
    }
}

UserWindow::~UserWindow()
{
    delete ui;

    std::cout << "DESTRUCT";
}
