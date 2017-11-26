#include "imageviewer.h"
#include "ui_imageviewer.h"
#include <QPixmap>
#include <stdio.h>
#include<QMessageBox>
#include <QStandardItem>
imageviewer::imageviewer(QWidget *parent, std::string path, bool mine, Peer &p) :
    QMainWindow(parent),
    ui(new Ui::imageviewer)
{

    std::string name=path;
    std::reverse(name.begin(),name.end());
    name=name.substr(0,name.find('/'));
    std::reverse(name.begin(),name.end());
    setWindowTitle(name.c_str());
    ui->setupUi(this);
    QPixmap pix(path.c_str());
    this->mine=mine;
    image_name=name;
    //ui->image->setPixmap(pix.scaled(700,700,Qt::KeepAspectRatio));
    ui->image->setPixmap(pix.scaled(ui->image->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->image->setScaledContents(true);
    //ui->image->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    view = new QTableView;
    model = new QStandardItemModel;
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);

    if(mine)
    {
       // model->setTitle("Shared with");
        model->setHorizontalHeaderItem(0, new QStandardItem(QString("Name")));
        model->setHorizontalHeaderItem(1, new QStandardItem(QString("Count")));
        vector<pair<std::string,int> > ret = p.getCurrentImageViewers(name);
        int i=0;
        for(pair<std::string,int> p:ret)
        {
            QStandardItem *first = new QStandardItem(p.first.c_str());
            model->setItem(i,0,first);
            QStandardItem *second = new QStandardItem(p.second);
            model->setItem(i,1,second);
            i++;
        }

    }
    else
    {
        //model->setTable("Status");
         model->setHorizontalHeaderItem(0, new QStandardItem(QString("Count")));
         current=path;
    }

    this->setAttribute( Qt::WA_QuitOnClose, false );

}
void imageviewer::closeEvent(QCloseEvent *event)
{
    if(!mine)remove(current.c_str());
    //delete file
}
imageviewer::~imageviewer()
{
    delete ui;
}
