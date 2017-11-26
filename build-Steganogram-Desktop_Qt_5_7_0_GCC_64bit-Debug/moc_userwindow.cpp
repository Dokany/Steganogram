/****************************************************************************
** Meta object code from reading C++ file 'userwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Steganogram/userwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'userwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UserWindow_t {
    QByteArrayData data[12];
    char stringdata0[213];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UserWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UserWindow_t qt_meta_stringdata_UserWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "UserWindow"
QT_MOC_LITERAL(1, 11, 10), // "handleMBox"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 12), // "terminateBox"
QT_MOC_LITERAL(4, 36, 23), // "on_uploadButton_clicked"
QT_MOC_LITERAL(5, 60, 26), // "on_imageWidget_itemClicked"
QT_MOC_LITERAL(6, 87, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(7, 104, 4), // "item"
QT_MOC_LITERAL(8, 109, 23), // "on_LogoutButton_clicked"
QT_MOC_LITERAL(9, 133, 24), // "on_RefreshButton_clicked"
QT_MOC_LITERAL(10, 158, 27), // "on_sharedWidget_itemClicked"
QT_MOC_LITERAL(11, 186, 26) // "on_usersWidget_itemClicked"

    },
    "UserWindow\0handleMBox\0\0terminateBox\0"
    "on_uploadButton_clicked\0"
    "on_imageWidget_itemClicked\0QListWidgetItem*\0"
    "item\0on_LogoutButton_clicked\0"
    "on_RefreshButton_clicked\0"
    "on_sharedWidget_itemClicked\0"
    "on_usersWidget_itemClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UserWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    1,   57,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,
      10,    1,   62,    2, 0x08 /* Private */,
      11,    1,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void UserWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UserWindow *_t = static_cast<UserWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->handleMBox(); break;
        case 1: _t->terminateBox(); break;
        case 2: _t->on_uploadButton_clicked(); break;
        case 3: _t->on_imageWidget_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->on_LogoutButton_clicked(); break;
        case 5: _t->on_RefreshButton_clicked(); break;
        case 6: _t->on_sharedWidget_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 7: _t->on_usersWidget_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject UserWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_UserWindow.data,
      qt_meta_data_UserWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UserWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UserWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UserWindow.stringdata0))
        return static_cast<void*>(const_cast< UserWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int UserWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
