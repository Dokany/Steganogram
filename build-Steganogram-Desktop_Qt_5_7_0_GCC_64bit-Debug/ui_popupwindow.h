/********************************************************************************
** Form generated from reading UI file 'popupwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POPUPWINDOW_H
#define UI_POPUPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_popupwindow
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *popupwindow)
    {
        if (popupwindow->objectName().isEmpty())
            popupwindow->setObjectName(QStringLiteral("popupwindow"));
        popupwindow->resize(400, 300);
        buttonBox = new QDialogButtonBox(popupwindow);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(popupwindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), popupwindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), popupwindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(popupwindow);
    } // setupUi

    void retranslateUi(QDialog *popupwindow)
    {
        popupwindow->setWindowTitle(QApplication::translate("popupwindow", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class popupwindow: public Ui_popupwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POPUPWINDOW_H
