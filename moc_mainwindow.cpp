/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata0[281];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 15), // "on_send_clicked"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 18), // "on_connect_clicked"
QT_MOC_LITERAL(4, 47, 12), // "slotCloseTab"
QT_MOC_LITERAL(5, 60, 29), // "on_messageInput_returnPressed"
QT_MOC_LITERAL(6, 90, 22), // "on_credentials_clicked"
QT_MOC_LITERAL(7, 113, 25), // "on_password_returnPressed"
QT_MOC_LITERAL(8, 139, 18), // "displayMessageSlot"
QT_MOC_LITERAL(9, 158, 7), // "message"
QT_MOC_LITERAL(10, 166, 3), // "tab"
QT_MOC_LITERAL(11, 170, 5), // "focus"
QT_MOC_LITERAL(12, 176, 20), // "connectionFailedSlot"
QT_MOC_LITERAL(13, 197, 4), // "Qmsg"
QT_MOC_LITERAL(14, 202, 16), // "updateStatusSlot"
QT_MOC_LITERAL(15, 219, 6), // "status"
QT_MOC_LITERAL(16, 226, 18), // "updateUsernameSlot"
QT_MOC_LITERAL(17, 245, 8), // "username"
QT_MOC_LITERAL(18, 254, 18), // "closeTabByNameSlot"
QT_MOC_LITERAL(19, 273, 7) // "tabName"

    },
    "MainWindow\0on_send_clicked\0\0"
    "on_connect_clicked\0slotCloseTab\0"
    "on_messageInput_returnPressed\0"
    "on_credentials_clicked\0on_password_returnPressed\0"
    "displayMessageSlot\0message\0tab\0focus\0"
    "connectionFailedSlot\0Qmsg\0updateStatusSlot\0"
    "status\0updateUsernameSlot\0username\0"
    "closeTabByNameSlot\0tabName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    1,   76,    2, 0x08 /* Private */,
       5,    0,   79,    2, 0x08 /* Private */,
       6,    0,   80,    2, 0x08 /* Private */,
       7,    0,   81,    2, 0x08 /* Private */,
       8,    3,   82,    2, 0x08 /* Private */,
       8,    2,   89,    2, 0x28 /* Private | MethodCloned */,
      12,    1,   94,    2, 0x08 /* Private */,
      14,    1,   97,    2, 0x08 /* Private */,
      16,    1,  100,    2, 0x08 /* Private */,
      18,    1,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,    9,   10,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    9,   10,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::QString,   19,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_send_clicked(); break;
        case 1: _t->on_connect_clicked(); break;
        case 2: _t->slotCloseTab((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_messageInput_returnPressed(); break;
        case 4: _t->on_credentials_clicked(); break;
        case 5: _t->on_password_returnPressed(); break;
        case 6: _t->displayMessageSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 7: _t->displayMessageSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->connectionFailedSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->updateStatusSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->updateUsernameSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->closeTabByNameSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
