/********************************************************************************
** Form generated from reading UI file 'userwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERWINDOW_H
#define UI_USERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserWindow
{
public:
    QWidget *centralwidget;
    QLabel *LogoLabel;
    QGroupBox *onlineUserGroup;
    QListWidget *usersWidget;
    QPushButton *LogoutButton;
    QPushButton *uploadButton;
    QPushButton *RequestsButton;
    QGroupBox *myImages;
    QListWidget *imageWidget;
    QPushButton *RefreshButton;
    QGroupBox *sharedList;
    QListWidget *sharedWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *UserWindow)
    {
        if (UserWindow->objectName().isEmpty())
            UserWindow->setObjectName(QStringLiteral("UserWindow"));
        UserWindow->resize(640, 480);
        UserWindow->setStyleSheet(QLatin1String("QMainWindow{\n"
"background-color:#EEEEDA;\n"
"}\n"
"\n"
"QMenuBar{\n"
"background-color:#1d1d1d;\n"
"padding:5px;\n"
"	font: 12pt \"MS Shell Dlg 2\";\n"
"}\n"
"\n"
"QMenuBar::item{\n"
"background-color:#1d1d1d;\n"
"color:#fff;\n"
"padding:5px;\n"
"\n"
"}\n"
"\n"
"QMenu{\n"
"color:#fff;\n"
"padding:0;\n"
"}\n"
"\n"
"QMenu::item:selected{\n"
"color:#fff;\n"
"background-color:#00aba9;\n"
"}\n"
"\n"
"QGroupBox {\n"
"    background-color: #FFB200;\n"
"}\n"
"\n"
"QTableWidget{\n"
"background-color:#3d3d3d;\n"
"color:#fff;\n"
"  selection-background-color: #da532c;\n"
"border:solid;\n"
"border-width:3px;\n"
"border-color:#da532c;\n"
"}\n"
"QHeaderView::section{\n"
"background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(20, 158, 217, 255), stop:1 rgba(36, 158, 217, 255));\n"
"border:none;\n"
"border-top-style:solid;\n"
"border-width:1px;\n"
"border-top-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(20, 158, 217, 255), stop:1 rgba(36, 158, 217, 255));\n"
"color:#fff;\n"
""
                        "\n"
"}\n"
"QHeaderView{\n"
"background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(20, 158, 217, 255), stop:1 rgba(36, 158, 217, 255));\n"
"\n"
"border:none;\n"
"border-top-style:solid;\n"
"border-width:1px;\n"
"border-top-color:#149ED9;\n"
"color:#fff;\n"
"	font: 75 12pt \"Calibri\";\n"
"}\n"
"\n"
"QTableCornerButton::section{\n"
"border:none;\n"
"background-color:#149ED9;\n"
"}\n"
"\n"
"QListWidget{\n"
"background-color:#6A6A6A;\n"
"color:#fff;\n"
"}\n"
"\n"
"QMenu{\n"
"background-color:#FFB200;\n"
"}\n"
"QStatusBar{\n"
"background-color:#FFB200;\n"
"color:#fff;\n"
"}\n"
"\n"
"QPushButton{\n"
"border-style:solid;\n"
"\n"
"background-color:#3d3d3d;\n"
"color:#fff;\n"
"border-radius:7px;\n"
"}\n"
"QPushButton:hover{\n"
"color:#ccc;\n"
"	background-color: qlineargradient(spread:pad, x1:0.517, y1:0, x2:0.517, y2:1, stop:0 rgba(45, 45, 45, 255), stop:0.505682 rgba(45, 45, 45, 255), stop:1 rgba(29, 29, 29, 255));\n"
"	border-color:#2d89ef;\n"
"border-width:2px;\n"
"}\n"
"\n"
"QPushButton:"
                        "pressed{\n"
"background-color: qlineargradient(spread:pad, x1:0.517, y1:0, x2:0.517, y2:1, stop:0 rgba(29, 29, 29, 255), stop:0.505682 rgba(45, 45, 45, 255), stop:1 rgba(29, 29, 29, 255));\n"
"}\n"
"\n"
"\n"
"QTabWidget::tab{\n"
"background-color:#FFB200;\n"
"}\n"
"\n"
"QLineEdit{\n"
"border-radius:0;\n"
"}\n"
"\n"
"QProgressBar{\n"
"border-radius:0;\n"
"text-align:center;\n"
"color:#fff;\n"
"background-color:transparent;\n"
"border: 2px solid #e3a21a;\n"
"border-radius:7px;\n"
"	font: 75 12pt \"Open Sans\";\n"
"\n"
"}\n"
"\n"
"QProgressBar::chunk{\n"
"background-color:#2d89ef;\n"
"width:20px;\n"
"}"));
        centralwidget = new QWidget(UserWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        LogoLabel = new QLabel(centralwidget);
        LogoLabel->setObjectName(QStringLiteral("LogoLabel"));
        LogoLabel->setGeometry(QRect(0, 0, 51, 41));
        onlineUserGroup = new QGroupBox(centralwidget);
        onlineUserGroup->setObjectName(QStringLiteral("onlineUserGroup"));
        onlineUserGroup->setGeometry(QRect(419, 40, 221, 381));
        usersWidget = new QListWidget(onlineUserGroup);
        usersWidget->setObjectName(QStringLiteral("usersWidget"));
        usersWidget->setGeometry(QRect(10, 30, 201, 341));
        LogoutButton = new QPushButton(centralwidget);
        LogoutButton->setObjectName(QStringLiteral("LogoutButton"));
        LogoutButton->setGeometry(QRect(579, 0, 61, 41));
        uploadButton = new QPushButton(centralwidget);
        uploadButton->setObjectName(QStringLiteral("uploadButton"));
        uploadButton->setGeometry(QRect(499, 0, 71, 41));
        RequestsButton = new QPushButton(centralwidget);
        RequestsButton->setObjectName(QStringLiteral("RequestsButton"));
        RequestsButton->setGeometry(QRect(420, 0, 71, 41));
        myImages = new QGroupBox(centralwidget);
        myImages->setObjectName(QStringLiteral("myImages"));
        myImages->setGeometry(QRect(10, 40, 401, 191));
        imageWidget = new QListWidget(myImages);
        imageWidget->setObjectName(QStringLiteral("imageWidget"));
        imageWidget->setGeometry(QRect(10, 31, 381, 151));
        RefreshButton = new QPushButton(centralwidget);
        RefreshButton->setObjectName(QStringLiteral("RefreshButton"));
        RefreshButton->setGeometry(QRect(340, 0, 71, 41));
        sharedList = new QGroupBox(centralwidget);
        sharedList->setObjectName(QStringLiteral("sharedList"));
        sharedList->setGeometry(QRect(10, 230, 401, 191));
        sharedWidget = new QListWidget(sharedList);
        sharedWidget->setObjectName(QStringLiteral("sharedWidget"));
        sharedWidget->setGeometry(QRect(10, 31, 381, 151));
        UserWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(UserWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 640, 39));
        UserWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(UserWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        UserWindow->setStatusBar(statusbar);

        retranslateUi(UserWindow);

        QMetaObject::connectSlotsByName(UserWindow);
    } // setupUi

    void retranslateUi(QMainWindow *UserWindow)
    {
        UserWindow->setWindowTitle(QApplication::translate("UserWindow", "Steganogram", 0));
        LogoLabel->setText(QApplication::translate("UserWindow", "TextLabel", 0));
        onlineUserGroup->setTitle(QApplication::translate("UserWindow", "Online Users ", 0));
        LogoutButton->setText(QApplication::translate("UserWindow", "Logout", 0));
        uploadButton->setText(QApplication::translate("UserWindow", "Upload", 0));
        RequestsButton->setText(QApplication::translate("UserWindow", "Requests", 0));
        myImages->setTitle(QApplication::translate("UserWindow", "My Images", 0));
        RefreshButton->setText(QApplication::translate("UserWindow", "Refresh", 0));
        sharedList->setTitle(QApplication::translate("UserWindow", "Shared Images", 0));
    } // retranslateUi

};

namespace Ui {
    class UserWindow: public Ui_UserWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERWINDOW_H
