/****************************************************************************
** Meta object code from reading C++ file 'editor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DebugED/editor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Editor_t {
    QByteArrayData data[22];
    char stringdata[249];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Editor_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Editor_t qt_meta_stringdata_Editor = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 9),
QT_MOC_LITERAL(2, 17, 0),
QT_MOC_LITERAL(3, 18, 13),
QT_MOC_LITERAL(4, 32, 12),
QT_MOC_LITERAL(5, 45, 18),
QT_MOC_LITERAL(6, 64, 4),
QT_MOC_LITERAL(7, 69, 3),
QT_MOC_LITERAL(8, 73, 11),
QT_MOC_LITERAL(9, 85, 4),
QT_MOC_LITERAL(10, 90, 4),
QT_MOC_LITERAL(11, 95, 12),
QT_MOC_LITERAL(12, 108, 11),
QT_MOC_LITERAL(13, 120, 20),
QT_MOC_LITERAL(14, 141, 20),
QT_MOC_LITERAL(15, 162, 10),
QT_MOC_LITERAL(16, 173, 12),
QT_MOC_LITERAL(17, 186, 12),
QT_MOC_LITERAL(18, 199, 14),
QT_MOC_LITERAL(19, 214, 6),
QT_MOC_LITERAL(20, 221, 16),
QT_MOC_LITERAL(21, 238, 10)
    },
    "Editor\0blockNext\0\0blockPrevious\0"
    "createStruct\0Struct::StructType\0type\0"
    "var\0createArrow\0varA\0varB\0removeStruct\0"
    "removeArrow\0highlightCurrentLine\0"
    "updateLineNumberArea\0passAction\0"
    "CodeED::Pass\0selectSample\0CodeED::Sample\0"
    "sample\0insertCompletion\0completion"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Editor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    2,   71,    2, 0x06 /* Public */,
       8,    2,   76,    2, 0x06 /* Public */,
      11,    2,   81,    2, 0x06 /* Public */,
      12,    2,   86,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,   91,    2, 0x08 /* Private */,
      14,    2,   92,    2, 0x08 /* Private */,
      15,    1,   97,    2, 0x08 /* Private */,
      17,    1,  100,    2, 0x08 /* Private */,
      20,    1,  103,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5, QMetaType::QString,    6,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    9,   10,
    QMetaType::Void, 0x80000000 | 5, QMetaType::QString,    6,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    9,   10,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QRect, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, QMetaType::QString,   21,

       0        // eod
};

void Editor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Editor *_t = static_cast<Editor *>(_o);
        switch (_id) {
        case 0: _t->blockNext(); break;
        case 1: _t->blockPrevious(); break;
        case 2: _t->createStruct((*reinterpret_cast< Struct::StructType(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->createArrow((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->removeStruct((*reinterpret_cast< Struct::StructType(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->removeArrow((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->highlightCurrentLine(); break;
        case 7: _t->updateLineNumberArea((*reinterpret_cast< const QRect(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->passAction((*reinterpret_cast< CodeED::Pass(*)>(_a[1]))); break;
        case 9: _t->selectSample((*reinterpret_cast< CodeED::Sample(*)>(_a[1]))); break;
        case 10: _t->insertCompletion((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Editor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Editor::blockNext)) {
                *result = 0;
            }
        }
        {
            typedef void (Editor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Editor::blockPrevious)) {
                *result = 1;
            }
        }
        {
            typedef void (Editor::*_t)(Struct::StructType , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Editor::createStruct)) {
                *result = 2;
            }
        }
        {
            typedef void (Editor::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Editor::createArrow)) {
                *result = 3;
            }
        }
        {
            typedef void (Editor::*_t)(Struct::StructType , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Editor::removeStruct)) {
                *result = 4;
            }
        }
        {
            typedef void (Editor::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Editor::removeArrow)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject Editor::staticMetaObject = {
    { &QPlainTextEdit::staticMetaObject, qt_meta_stringdata_Editor.data,
      qt_meta_data_Editor,  qt_static_metacall, 0, 0}
};


const QMetaObject *Editor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Editor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Editor.stringdata))
        return static_cast<void*>(const_cast< Editor*>(this));
    return QPlainTextEdit::qt_metacast(_clname);
}

int Editor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPlainTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Editor::blockNext()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Editor::blockPrevious()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Editor::createStruct(Struct::StructType _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Editor::createArrow(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Editor::removeStruct(Struct::StructType _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Editor::removeArrow(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
