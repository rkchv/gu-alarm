/****************************************************************************
** Meta object code from reading C++ file 'draw.h'
**
** Created: Tue 11. Jun 12:14:21 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../source/draw.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'draw.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_signal_plot_t[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   15,   14,   14, 0x05,
      39,   15,   14,   14, 0x05,
      65,   14,   14,   14, 0x05,
      80,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     105,   97,   14,   14, 0x0a,
     132,  126,   14,   14, 0x0a,
     161,  155,   14,   14, 0x0a,
     181,   15,   14,   14, 0x0a,
     212,  206,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_signal_plot_t[] = {
    "signal_plot_t\0\0s\0sig_set_freq(QString)\0"
    "sig_show_message(QString)\0sig_get_data()\0"
    "sig_log(QString)\0row,col\0sl_draw_sig(int,int)\0"
    "index\0sl_set_y_scale(double)\0scale\0"
    "sl_set_x_scale(int)\0sl_set_filename(QString)\0"
    "value\0scrollBotAxis(int)\0"
};

void signal_plot_t::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        signal_plot_t *_t = static_cast<signal_plot_t *>(_o);
        switch (_id) {
        case 0: _t->sig_set_freq((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sig_show_message((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->sig_get_data(); break;
        case 3: _t->sig_log((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->sl_draw_sig((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->sl_set_y_scale((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->sl_set_x_scale((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->sl_set_filename((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->scrollBotAxis((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData signal_plot_t::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject signal_plot_t::staticMetaObject = {
    { &QwtPlot::staticMetaObject, qt_meta_stringdata_signal_plot_t,
      qt_meta_data_signal_plot_t, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &signal_plot_t::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *signal_plot_t::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *signal_plot_t::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_signal_plot_t))
        return static_cast<void*>(const_cast< signal_plot_t*>(this));
    return QwtPlot::qt_metacast(_clname);
}

int signal_plot_t::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtPlot::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void signal_plot_t::sig_set_freq(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void signal_plot_t::sig_show_message(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void signal_plot_t::sig_get_data()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void signal_plot_t::sig_log(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
static const uint qt_meta_data_event_plot_t[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   14,   13,   13, 0x05,
      50,   48,   13,   13, 0x05,
      76,   13,   13,   13, 0x05,
     105,   48,   13,   13, 0x05,
     134,  132,   13,   13, 0x05,
     151,  132,   13,   13, 0x05,
     168,   48,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
     198,  185,   13,   13, 0x0a,
     230,  225,   13,   13, 0x0a,
     245,   13,   13,   13, 0x0a,
     268,  260,   13,   13, 0x0a,
     290,   48,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_event_plot_t[] = {
    "event_plot_t\0\0event_data\0"
    "sig_test(event_data_t)\0s\0"
    "sig_show_message(QString)\0"
    "sig_send_event(event_data_t)\0"
    "sig_send_filename(QString)\0n\0"
    "sig_set_lcd(int)\0sig_set_dig(int)\0"
    "sig_log(QString)\0p_event_data\0"
    "sl_add_event(event_data_t)\0time\0"
    "sl_move(QTime)\0sl_open_file()\0checked\0"
    "sl_load_session(bool)\0sl_set_filename(QString)\0"
};

void event_plot_t::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        event_plot_t *_t = static_cast<event_plot_t *>(_o);
        switch (_id) {
        case 0: _t->sig_test((*reinterpret_cast< event_data_t(*)>(_a[1]))); break;
        case 1: _t->sig_show_message((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->sig_send_event((*reinterpret_cast< event_data_t(*)>(_a[1]))); break;
        case 3: _t->sig_send_filename((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->sig_set_lcd((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->sig_set_dig((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->sig_log((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->sl_add_event((*reinterpret_cast< event_data_t(*)>(_a[1]))); break;
        case 8: _t->sl_move((*reinterpret_cast< const QTime(*)>(_a[1]))); break;
        case 9: _t->sl_open_file(); break;
        case 10: _t->sl_load_session((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->sl_set_filename((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData event_plot_t::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject event_plot_t::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_event_plot_t,
      qt_meta_data_event_plot_t, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &event_plot_t::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *event_plot_t::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *event_plot_t::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_event_plot_t))
        return static_cast<void*>(const_cast< event_plot_t*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int event_plot_t::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void event_plot_t::sig_test(event_data_t _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void event_plot_t::sig_show_message(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void event_plot_t::sig_send_event(event_data_t _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void event_plot_t::sig_send_filename(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void event_plot_t::sig_set_lcd(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void event_plot_t::sig_set_dig(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void event_plot_t::sig_log(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
