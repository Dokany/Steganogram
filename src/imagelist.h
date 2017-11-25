#ifndef IMAGELIST_H
#define IMAGELIST_H

#include <set>
#include <string>
#include <QDialog>
#include "Peer.h"

namespace Ui {
class ImageList;
}

class ImageList : public QDialog
{
    Q_OBJECT

public:
    explicit ImageList(QWidget *parent = 0);
    ~ImageList();

private slots:
    void on_imageListWidget_itemClicked(QListWidgetItem *item, Peer &p, std::string username);

private:
    std::set<std::string> imageList;
    Ui::ImageList *ui;
};

#endif // IMAGELIST_H
