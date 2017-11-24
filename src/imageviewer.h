#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include<string>
#include "Peer.h"
namespace Ui {
class imageviewer;
}

class imageviewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit imageviewer(QWidget *parent, std::string path, bool mine, Peer &p);
    ~imageviewer();

private:
    Ui::imageviewer *ui;
    QTableView *view;
    QStandardItemModel *model;
};

#endif // IMAGEVIEWER_H
