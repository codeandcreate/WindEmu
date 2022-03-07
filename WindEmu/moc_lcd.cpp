/****************************************************************************
** Meta object code from reading C++ file 'lcd.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "lcd.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lcd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LcdWorkerThread_t {
    QByteArrayData data[1];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LcdWorkerThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LcdWorkerThread_t qt_meta_stringdata_LcdWorkerThread = {
    {
QT_MOC_LITERAL(0, 0, 15) // "LcdWorkerThread"

    },
    "LcdWorkerThread"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LcdWorkerThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void LcdWorkerThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject LcdWorkerThread::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_LcdWorkerThread.data,
    qt_meta_data_LcdWorkerThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LcdWorkerThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LcdWorkerThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LcdWorkerThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int LcdWorkerThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_Lcd_t {
    QByteArrayData data[16];
    char stringdata0[168];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Lcd_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Lcd_t qt_meta_stringdata_Lcd = {
    {
QT_MOC_LITERAL(0, 0, 3), // "Lcd"
QT_MOC_LITERAL(1, 4, 9), // "execTimer"
QT_MOC_LITERAL(2, 14, 0), // ""
QT_MOC_LITERAL(3, 15, 14), // "execPaintTimer"
QT_MOC_LITERAL(4, 30, 17), // "saveButtonPressed"
QT_MOC_LITERAL(5, 48, 13), // "digitizerDown"
QT_MOC_LITERAL(6, 62, 3), // "pos"
QT_MOC_LITERAL(7, 66, 11), // "digitizerUp"
QT_MOC_LITERAL(8, 78, 12), // "digitizerPos"
QT_MOC_LITERAL(9, 91, 10), // "fingerDown"
QT_MOC_LITERAL(10, 102, 8), // "fingerUp"
QT_MOC_LITERAL(11, 111, 9), // "fingerPos"
QT_MOC_LITERAL(12, 121, 13), // "keyPressEvent"
QT_MOC_LITERAL(13, 135, 10), // "QKeyEvent*"
QT_MOC_LITERAL(14, 146, 5), // "event"
QT_MOC_LITERAL(15, 152, 15) // "keyReleaseEvent"

    },
    "Lcd\0execTimer\0\0execPaintTimer\0"
    "saveButtonPressed\0digitizerDown\0pos\0"
    "digitizerUp\0digitizerPos\0fingerDown\0"
    "fingerUp\0fingerPos\0keyPressEvent\0"
    "QKeyEvent*\0event\0keyReleaseEvent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Lcd[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a /* Public */,
       3,    0,   70,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
       4,    0,   71,    2, 0x02 /* Public */,
       5,    1,   72,    2, 0x02 /* Public */,
       7,    1,   75,    2, 0x02 /* Public */,
       8,    1,   78,    2, 0x02 /* Public */,
       9,    1,   81,    2, 0x02 /* Public */,
      10,    1,   84,    2, 0x02 /* Public */,
      11,    1,   87,    2, 0x02 /* Public */,
      12,    1,   90,    2, 0x02 /* Public */,
      15,    1,   93,    2, 0x02 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPointF,    6,
    QMetaType::Void, QMetaType::QPointF,    6,
    QMetaType::Void, QMetaType::QPointF,    6,
    QMetaType::Void, QMetaType::QPointF,    6,
    QMetaType::Void, QMetaType::QPointF,    6,
    QMetaType::Void, QMetaType::QPointF,    6,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 13,   14,

       0        // eod
};

void Lcd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Lcd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->execTimer(); break;
        case 1: _t->execPaintTimer(); break;
        case 2: _t->saveButtonPressed(); break;
        case 3: _t->digitizerDown((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 4: _t->digitizerUp((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 5: _t->digitizerPos((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 6: _t->fingerDown((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 7: _t->fingerUp((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 8: _t->fingerPos((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 9: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 10: _t->keyReleaseEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Lcd::staticMetaObject = { {
    QMetaObject::SuperData::link<QQuickPaintedItem::staticMetaObject>(),
    qt_meta_stringdata_Lcd.data,
    qt_meta_data_Lcd,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Lcd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Lcd::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Lcd.stringdata0))
        return static_cast<void*>(this);
    return QQuickPaintedItem::qt_metacast(_clname);
}

int Lcd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQuickPaintedItem::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
