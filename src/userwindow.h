#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <thread>
#include <QtCore>
#include "Peer.h"
#include <QListWidgetItem>
#include<atomic>
#include "imageviewer.h"

namespace Ui {
class UserWindow;
}

class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserWindow(QWidget *parent, Peer *p);
    ~UserWindow();

    QStringList list, list_2;
    void updateOnlineList();
    void myImageListView();
    void viewImageWidget();

private slots:
    void on_uploadButton_clicked();
    void on_imageWidget_itemClicked(QListWidgetItem *item);
    void on_LogoutButton_clicked();

    void on_RefreshButton_clicked();

private:
    std::atomic<bool> working;
    Peer* p;
    std::thread t;
    Ui::UserWindow *ui;
    imageviewer *iv;
    QStringListModel *model;
    QStringListModel *model_2;
};

#endif // USERWINDOW_H
