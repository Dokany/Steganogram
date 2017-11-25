#include "imagelist.h"
#include "ui_imagelist.h"
#include<QMessageBox>

ImageList::ImageList(QWidget *parent, Peer &p, std::string username) :
    QDialog(parent),
    ui(new Ui::ImageList)
{
    ui->setupUi(this);

    imageList = p.getUserImages(username);

    if (imageList.empty())
    {
        QMessageBox::warning(this,"Image List Empty", "The user sent no images to view!\n");
        this->close();
    }
    else viewImageListWidget();
}

void ImageList:: viewImageListWidget()
{
    // Viewing Image List Entries

    for (auto& a: imageList) {

        ui->imageListWidget->addItem(QString::fromStdString(a));
    }

    ui->imageListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ImageList::on_imageListWidget_itemClicked(QListWidgetItem *item)
{
    // Requesting Image
}

ImageList::~ImageList()
{
    delete ui;
}