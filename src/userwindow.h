#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <thread>
#include <QtCore>
#include "Peer.h"
#include "imageviewer.h"
namespace Ui {
class UserWindow;
}

class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserWindow(QWidget *parent, Peer& p);
    ~UserWindow();

    QStringList list, list_2;
    void updateOnlineList();
    void myImageListView();

private slots:

    void on_uploadButton_clicked();

private:
    Peer* p;
    std::thread t;
    Ui::UserWindow *ui;
    imageviewer *iv;
    QStringListModel *model;
    QStringListModel *model_2;
};

#endif // USERWINDOW_H
