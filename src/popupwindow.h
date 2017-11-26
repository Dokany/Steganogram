#ifndef POPUPWINDOW_H
#define POPUPWINDOW_H

#include <QDialog>

namespace Ui {
class popupwindow;
}

class popupwindow : public QDialog
{
    Q_OBJECT

public:
    explicit popupwindow(QWidget *parent = 0);
    ~popupwindow();

private:
    Ui::popupwindow *ui;
};

#endif // POPUPWINDOW_H
