#ifndef IMAGELIST_H
#define IMAGELIST_H

#include <set>
#include <string>
#include <QDialog>
#include "Peer.h"
#include <QListWidgetItem>

namespace Ui {
class ImageList;
}

class ImageList : public QDialog
{
    Q_OBJECT

public:
    explicit ImageList(QWidget *parent, Peer *p, std::string username);
    void viewImageListWidget();
    ~ImageList();

private slots:
    void on_imageListWidget_itemClicked(QListWidgetItem *item);

private:
    Peer *p;
    std::string username;
    std::set<std::string> imageList;
    Ui::ImageList *ui;
};

#endif // IMAGELIST_H
