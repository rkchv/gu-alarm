/****************************************************************************
** Meta object code from reading C++ file 'gui_gurza_alarm.h'
**
** Created: Tue 11. Jun 12:14:31 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../source/gui_gurza_alarm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gui_gurza_alarm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gui_gurza_alarm[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      33,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      44,   16,   16,   16, 0x0a,
      63,   55,   16,   16, 0x0a,
      91,   81,   16,   16, 0x0a,
     112,  110,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_gui_gurza_alarm[] = {
    "gui_gurza_alarm\0\0sig_open_file()\0"
    "sig_exit()\0sl_start()\0checked\0"
    "sl_set_mode(bool)\0numDigits\0"
    "setDigitCount(int)\0s\0sl_log(QString)\0"
};

void gui_gurza_alarm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        gui_gurza_alarm *_t = static_cast<gui_gurza_alarm *>(_o);
        switch (_id) {
        case 0: _t->sig_open_file(); break;
        case 1: _t->sig_exit(); break;
        case 2: _t->sl_start(); break;
        case 3: _t->sl_set_mode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->setDigitCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->sl_log((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData gui_gurza_alarm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject gui_gurza_alarm::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_gui_gurza_alarm,
      qt_meta_data_gui_gurza_alarm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gui_gurza_alarm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gui_gurza_alarm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gui_gurza_alarm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gui_gurza_alarm))
        return static_cast<void*>(const_cast< gui_gurza_alarm*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int gui_gurza_alarm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void gui_gurza_alarm::sig_open_file()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void gui_gurza_alarm::sig_exit()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
