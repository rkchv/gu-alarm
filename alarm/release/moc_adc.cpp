/****************************************************************************
** Meta object code from reading C++ file 'adc.h'
**
** Created: Tue 11. Jun 12:14:42 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../source/adc.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'adc.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_qmbox_t[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,    9,    8,    8, 0x05,
      55,    8,    8,    8, 0x05,
      83,   81,    8,    8, 0x05,
     110,   81,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
     127,    8,    8,    8, 0x0a,
     144,    8,    8,    8, 0x0a,
     165,    8,    8,    8, 0x0a,
     181,    8,    8,    8, 0x0a,
     197,    8,    8,    8, 0x0a,
     240,  211,    8,    8, 0x0a,
     278,    8,    8,    8, 0x0a,
     293,  285,    8,    8, 0x0a,
     310,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_qmbox_t[] = {
    "qmbox_t\0\0data_signal\0"
    "sig_send_type_event(event_data_t)\0"
    "sig_show_message(QString)\0s\0"
    "sig_send_filename(QString)\0sig_log(QString)\0"
    "sl_choice_mode()\0sl_imit_input_data()\0"
    "sl_input_data()\0sl_processing()\0"
    "sl_analisis()\0time,number_event,number,max\0"
    "sl_event(QTime,quint32,quint8,double)\0"
    "quit()\0checked\0sl_send_fn(bool)\0"
    "sl_establish_smooth(int)\0"
};

void qmbox_t::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        qmbox_t *_t = static_cast<qmbox_t *>(_o);
        switch (_id) {
        case 0: _t->sig_send_type_event((*reinterpret_cast< event_data_t(*)>(_a[1]))); break;
        case 1: _t->sig_show_message((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->sig_send_filename((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->sig_log((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->sl_choice_mode(); break;
        case 5: _t->sl_imit_input_data(); break;
        case 6: _t->sl_input_data(); break;
        case 7: _t->sl_processing(); break;
        case 8: _t->sl_analisis(); break;
        case 9: _t->sl_event((*reinterpret_cast< QTime(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 10: _t->quit(); break;
        case 11: _t->sl_send_fn((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->sl_establish_smooth((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData qmbox_t::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject qmbox_t::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_qmbox_t,
      qt_meta_data_qmbox_t, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &qmbox_t::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *qmbox_t::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *qmbox_t::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_qmbox_t))
        return static_cast<void*>(const_cast< qmbox_t*>(this));
    return QThread::qt_metacast(_clname);
}

int qmbox_t::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void qmbox_t::sig_send_type_event(event_data_t _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void qmbox_t::sig_show_message(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void qmbox_t::sig_send_filename(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void qmbox_t::sig_log(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
