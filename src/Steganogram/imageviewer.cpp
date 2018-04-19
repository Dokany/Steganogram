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
    cout<<"IMAGE VIEWER NAME: "<<name<<endl;
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
    //refresh(mine, name, path, p);

    if(mine)
    {
       // model->setTitle("Shared with");
        model->setHorizontalHeaderItem(0, new QStandardItem(QString("Name")));
        model->setHorizontalHeaderItem(1, new QStandardItem(QString("Count")));
        vector<pair<std::string,int> > ret = p.getCurrentImageViewers(name);

        int i=0;
        for(pair<std::string,int> pp:ret)
        {
            cout<<"fffff "<<pp.first<<" "<<pp.second<<endl;
            QStandardItem *first = new QStandardItem(pp.first.c_str());
            model->setItem(i,0,first);
            QStandardItem *second = new QStandardItem((to_string(pp.second)).c_str());
            model->setItem(i,1,second);
            i++;
        }

    }
    else
    {
        //model->setTable("Status");
         model->setHorizontalHeaderItem(0, new QStandardItem(QString("Count")));
         current=path;


         reverse(image_name.begin(),image_name.end());
         string ext = image_name.substr(0,image_name.find('.'));
         reverse(ext.begin(),ext.end());
         reverse(image_name.begin(),image_name.end());
         cout<<"IMAGE NAME "<<image_name.substr(0,image_name.find('.'))+ext<<endl;

        int count=p.getImageStatus(image_name.substr(0,image_name.find('.'))+ext);
        QStandardItem *ss = new QStandardItem((to_string(count)).c_str());
         model->setItem(0,ss);
    }
    ui->countList->setStyleSheet("QTableView {color: white;}");
    ui->countList->setModel(model);
    this->setAttribute( Qt::WA_QuitOnClose, false );
}

void imageviewer::closeEvent(QCloseEvent *event)
{
    if(!mine)remove(current.c_str());
    //delete file
}
void imageviewer::refresh(bool mine, string name, string path, Peer&p)
{
        this->mine=mine;
    model = new QStandardItemModel;
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    cout<<"MINE IS "<<mine<<endl;
    QPixmap pix(path.c_str());

    image_name=name;
    //ui->image->setPixmap(pix.scaled(700,700,Qt::KeepAspectRatio));
    ui->image->setPixmap(pix.scaled(ui->image->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->image->setScaledContents(true);
    if(mine)
    {
       // model->setTitle("Shared with");
        model->setHorizontalHeaderItem(0, new QStandardItem(QString("Name")));
        model->setHorizontalHeaderItem(1, new QStandardItem(QString("Count")));
        vector<pair<std::string,int> > ret = p.getCurrentImageViewers(name);
        int i=0;
         cout<<"GOT "<<ret.size()<<" ENTRIES IN IMAGEVIEWER\n";
        for(pair<std::string,int> pp:ret)
        {
            cout<<" count in imviewer "<<pp.second<<endl;
            QStandardItem *first = new QStandardItem(pp.first.c_str());
            model->setItem(i,0,first);
            QStandardItem *second = new QStandardItem((to_string(pp.second)).c_str());
            model->setItem(i,1,second);
            i++;
        }

    }
    else
    {
        //model->setTable("Status");
         model->setHorizontalHeaderItem(0, new QStandardItem(QString("Count")));
         cout<<"deleteing "<<path<<endl;
         current=path;
         int cnt=p.getMBoxCount();
         QStandardItem *qq = new QStandardItem((to_string(cnt)).c_str());

         model->setItem(0,qq);
    }
    ui->countList->setStyleSheet("QTableView {color: white;}");
    ui->countList->selectAll();
    ui->countList->setModel(model);


}

imageviewer::~imageviewer()
{
    delete ui;
}
