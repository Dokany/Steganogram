#ifndef POPUP_H
#define POPUP_H

#include <QWidget>

namespace Ui {
class PopUp;
}

class PopUp : public QWidget
{
    Q_OBJECT

public:
    explicit PopUp(QWidget *parent = 0);
    ~PopUp();

private:
    Ui::PopUp *ui;
};

#endif // POPUP_H
