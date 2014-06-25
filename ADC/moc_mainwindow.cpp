/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Wed Jun 25 13:58:01 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      31,   11,   11,   11, 0x08,
      49,   11,   11,   11, 0x08,
      66,   11,   11,   11, 0x08,
      83,   11,   11,   11, 0x08,
     100,   11,   11,   11, 0x08,
     117,   11,   11,   11, 0x08,
     134,   11,   11,   11, 0x08,
     151,   11,   11,   11, 0x08,
     168,   11,   11,   11, 0x08,
     185,   11,   11,   11, 0x08,
     203,   11,   11,   11, 0x08,
     221,   11,   11,   11, 0x08,
     239,   11,   11,   11, 0x08,
     257,   11,   11,   11, 0x08,
     274,   11,   11,   11, 0x08,
     316,  302,  298,   11, 0x08,
     374,  357,  298,   11, 0x08,
     453,  423,  298,   11, 0x08,
     521,  512,   11,   11, 0x08,
     564,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_Start_clicked()\0"
    "on_Stop_clicked()\0on_Ch0_clicked()\0"
    "on_Ch1_clicked()\0on_Ch2_clicked()\0"
    "on_Ch3_clicked()\0on_Ch4_clicked()\0"
    "on_Ch5_clicked()\0on_Ch6_clicked()\0"
    "on_Ch7_clicked()\0on_Ch01_clicked()\0"
    "on_Ch23_clicked()\0on_Ch45_clicked()\0"
    "on_Ch67_clicked()\0on_timer_event()\0"
    "run_keyboard_lineEdit()\0int\0Ch,buf,overun\0"
    "PrvGetSamples(int,unsigned short*,uint*)\0"
    "Ch,config,period\0"
    "PrvSetChannelConfig(int,uint,unsigned long long)\0"
    "ch,file,buf,numSamples,overun\0"
    "PrvWriteSamplesToFile(int,QString,unsigned short*,int,int)\0"
    "dateTime\0on_dateTimeEdit_dateTimeChanged(QDateTime)\0"
    "on_checkBox_5V10V_clicked()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_Start_clicked(); break;
        case 1: on_Stop_clicked(); break;
        case 2: on_Ch0_clicked(); break;
        case 3: on_Ch1_clicked(); break;
        case 4: on_Ch2_clicked(); break;
        case 5: on_Ch3_clicked(); break;
        case 6: on_Ch4_clicked(); break;
        case 7: on_Ch5_clicked(); break;
        case 8: on_Ch6_clicked(); break;
        case 9: on_Ch7_clicked(); break;
        case 10: on_Ch01_clicked(); break;
        case 11: on_Ch23_clicked(); break;
        case 12: on_Ch45_clicked(); break;
        case 13: on_Ch67_clicked(); break;
        case 14: on_timer_event(); break;
        case 15: run_keyboard_lineEdit(); break;
        case 16: { int _r = PrvGetSamples((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< unsigned short*(*)>(_a[2])),(*reinterpret_cast< uint*(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 17: { int _r = PrvSetChannelConfig((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< unsigned long long(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 18: { int _r = PrvWriteSamplesToFile((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< unsigned short*(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 19: on_dateTimeEdit_dateTimeChanged((*reinterpret_cast< const QDateTime(*)>(_a[1]))); break;
        case 20: on_checkBox_5V10V_clicked(); break;
        default: ;
        }
        _id -= 21;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
