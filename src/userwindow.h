#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include "Peer.h"

namespace Ui {
class UserWindow;
}

class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserWindow(QWidget *parent, Peer& p);
    ~UserWindow();
    void etsaraf();

private slots:

private:
    Peer* p;
    Ui::UserWindow *ui;
};

#endif // USERWINDOW_H
