#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <thread>
#include <QtCore>
#include <QListWidgetItem>
#include<atomic>
#include <QMessageBox>

#include "imageviewer.h"

namespace Ui {
class UserWindow;
}

class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserWindow(QWidget *parent, Peer *p);
    UserWindow();
    UserWindow(const UserWindow& uw);
    ~UserWindow();
    //virtual ~UserWindow();

    QStringList list, list_2;
   // void updateOnlineList();
    void updateOnlineWidget();
    void myImageListView();
    void viewImageWidget();
    void viewSharedWidget();



 private slots:
    void handleMBox();
    void terminateBox();
    void on_uploadButton_clicked();
    void on_imageWidget_itemClicked(QListWidgetItem *item);
    void on_LogoutButton_clicked();

    void on_RefreshButton_clicked();

    void on_sharedWidget_itemClicked(QListWidgetItem *item);


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
