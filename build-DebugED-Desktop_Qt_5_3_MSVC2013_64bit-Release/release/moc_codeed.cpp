/****************************************************************************
** Meta object code from reading C++ file 'codeed.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DebugED/codeed.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'codeed.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CodeED_t {
    QByteArrayData data[18];
    char stringdata[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CodeED_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CodeED_t qt_meta_stringdata_CodeED = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 10),
QT_MOC_LITERAL(2, 18, 0),
QT_MOC_LITERAL(3, 19, 12),
QT_MOC_LITERAL(4, 32, 4),
QT_MOC_LITERAL(5, 37, 12),
QT_MOC_LITERAL(6, 50, 14),
QT_MOC_LITERAL(7, 65, 6),
QT_MOC_LITERAL(8, 72, 4),
QT_MOC_LITERAL(9, 77, 4),
QT_MOC_LITERAL(10, 82, 8),
QT_MOC_LITERAL(11, 91, 4),
QT_MOC_LITERAL(12, 96, 6),
QT_MOC_LITERAL(13, 103, 9),
QT_MOC_LITERAL(14, 113, 13),
QT_MOC_LITERAL(15, 127, 13),
QT_MOC_LITERAL(16, 141, 8),
QT_MOC_LITERAL(17, 150, 6)
    },
    "CodeED\0passAction\0\0CodeED::Pass\0pass\0"
    "selectSample\0CodeED::Sample\0sample\0"
    "play\0next\0previous\0stop\0replay\0blockNext\0"
    "blockPrevious\0triggerSample\0QAction*\0"
    "action"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CodeED[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       5,    1,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    0,   73,    2, 0x08 /* Private */,
      12,    0,   74,    2, 0x08 /* Private */,
      13,    0,   75,    2, 0x08 /* Private */,
      14,    0,   76,    2, 0x08 /* Private */,
      15,    1,   77,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,

       0        // eod
};

void CodeED::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CodeED *_t = static_cast<CodeED *>(_o);
        switch (_id) {
        case 0: _t->passAction((*reinterpret_cast< CodeED::Pass(*)>(_a[1]))); break;
        case 1: _t->selectSample((*reinterpret_cast< CodeED::Sample(*)>(_a[1]))); break;
        case 2: _t->play(); break;
        case 3: _t->next(); break;
        case 4: _t->previous(); break;
        case 5: _t->stop(); break;
        case 6: _t->replay(); break;
        case 7: _t->blockNext(); break;
        case 8: _t->blockPrevious(); break;
        case 9: _t->triggerSample((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CodeED::*_t)(CodeED::Pass );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CodeED::passAction)) {
                *result = 0;
            }
        }
        {
            typedef void (CodeED::*_t)(CodeED::Sample );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CodeED::selectSample)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject CodeED::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CodeED.data,
      qt_meta_data_CodeED,  qt_static_metacall, 0, 0}
};


const QMetaObject *CodeED::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CodeED::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CodeED.stringdata))
        return static_cast<void*>(const_cast< CodeED*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int CodeED::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void CodeED::passAction(CodeED::Pass _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CodeED::selectSample(CodeED::Sample _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
