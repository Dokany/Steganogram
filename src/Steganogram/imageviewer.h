#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <string>
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
    void closeEvent(QCloseEvent *event);
    void refresh(bool, string, string, Peer &p);
private slots:

private:
    Ui::imageviewer *ui;
    QTableView *view;
    QStandardItemModel *model;
    bool mine;
    string current, image_name;



};

#endif // IMAGEVIEWER_H
