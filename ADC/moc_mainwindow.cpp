/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Thu Aug 7 22:40:13 2014
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
      34,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   11,   12,   11, 0x08,
      37,   11,   12,   11, 0x08,
      58,   11,   11,   11, 0x08,
      77,   11,   11,   11, 0x08,
      95,   11,   11,   11, 0x08,
     120,   11,   11,   11, 0x08,
     145,   11,   11,   11, 0x08,
     170,   11,   11,   11, 0x08,
     195,   11,   11,   11, 0x08,
     220,   11,   11,   11, 0x08,
     245,   11,   11,   11, 0x08,
     270,   11,   11,   11, 0x08,
     295,   11,   11,   11, 0x08,
     312,   11,   11,   11, 0x08,
     354,  345,  336,   11, 0x08,
     402,  399,  380,   11, 0x08,
     443,  429,   12,   11, 0x08,
     492,  475,   12,   11, 0x08,
     571,  541,   12,   11, 0x08,
     635,  621,   12,   11, 0x08,
     675,  667,   12,   11, 0x08,
     712,  702,   12,   11, 0x08,
     746,  737,   11,   11, 0x08,
     789,   11,   11,   11, 0x08,
     824,  818,   11,   11, 0x08,
     853,   11,   11,   11, 0x08,
     876,   11,   11,   11, 0x08,
     898,   11,   11,   11, 0x08,
     920,   11,   11,   11, 0x08,
     942,   11,   11,   11, 0x08,
     964,   11,   11,   11, 0x08,
     986,   11,   11,   11, 0x08,
    1008,   11,   11,   11, 0x08,
    1030,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0int\0PrvLoadPreferences()\0"
    "PrvSavePreferences()\0on_Start_clicked()\0"
    "on_Stop_clicked()\0on_select_ch_0_clicked()\0"
    "on_select_ch_1_clicked()\0"
    "on_select_ch_2_clicked()\0"
    "on_select_ch_3_clicked()\0"
    "on_select_ch_4_clicked()\0"
    "on_select_ch_5_clicked()\0"
    "on_select_ch_6_clicked()\0"
    "on_select_ch_7_clicked()\0on_timer_event()\0"
    "run_keyboard_lineEdit()\0QString*\0"
    "Ch,chStr\0PrvGetChStr(int,QString*)\0"
    "unsigned long long\0Ch\0PrvGetSampleRateValue(int)\0"
    "Ch,buf,overun\0PrvGetSamples(int,short*,uint*)\0"
    "Ch,config,period\0"
    "PrvSetChannelConfig(int,uint,unsigned long long)\0"
    "ch,file,buf,numSamples,overun\0"
    "PrvWriteSamplesToFile(int,QString,short*,int,int)\0"
    "gain,unipolar\0PrvCalculateMultiplier(int,int)\0"
    "Ch,data\0PrvCalculate_mV(int,short)\0"
    "Ch,enable\0PrvSetupChannel(int,int)\0"
    "dateTime\0on_dateTimeEdit_dateTimeChanged(QDateTime)\0"
    "on_samrate_editingFinished()\0index\0"
    "on_Setup_currentChanged(int)\0"
    "on_DeleteCSV_clicked()\0on_log_Ch_0_clicked()\0"
    "on_log_Ch_1_clicked()\0on_log_Ch_2_clicked()\0"
    "on_log_Ch_3_clicked()\0on_log_Ch_4_clicked()\0"
    "on_log_Ch_5_clicked()\0on_log_Ch_6_clicked()\0"
    "on_log_Ch_7_clicked()\0"
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
        case 0: { int _r = PrvLoadPreferences();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: { int _r = PrvSavePreferences();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 2: on_Start_clicked(); break;
        case 3: on_Stop_clicked(); break;
        case 4: on_select_ch_0_clicked(); break;
        case 5: on_select_ch_1_clicked(); break;
        case 6: on_select_ch_2_clicked(); break;
        case 7: on_select_ch_3_clicked(); break;
        case 8: on_select_ch_4_clicked(); break;
        case 9: on_select_ch_5_clicked(); break;
        case 10: on_select_ch_6_clicked(); break;
        case 11: on_select_ch_7_clicked(); break;
        case 12: on_timer_event(); break;
        case 13: run_keyboard_lineEdit(); break;
        case 14: { QString* _r = PrvGetChStr((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString**>(_a[0]) = _r; }  break;
        case 15: { unsigned long long _r = PrvGetSampleRateValue((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< unsigned long long*>(_a[0]) = _r; }  break;
        case 16: { int _r = PrvGetSamples((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< short*(*)>(_a[2])),(*reinterpret_cast< uint*(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 17: { int _r = PrvSetChannelConfig((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< unsigned long long(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 18: { int _r = PrvWriteSamplesToFile((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< short*(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 19: { int _r = PrvCalculateMultiplier((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 20: { int _r = PrvCalculate_mV((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< short(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 21: { int _r = PrvSetupChannel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 22: on_dateTimeEdit_dateTimeChanged((*reinterpret_cast< const QDateTime(*)>(_a[1]))); break;
        case 23: on_samrate_editingFinished(); break;
        case 24: on_Setup_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: on_DeleteCSV_clicked(); break;
        case 26: on_log_Ch_0_clicked(); break;
        case 27: on_log_Ch_1_clicked(); break;
        case 28: on_log_Ch_2_clicked(); break;
        case 29: on_log_Ch_3_clicked(); break;
        case 30: on_log_Ch_4_clicked(); break;
        case 31: on_log_Ch_5_clicked(); break;
        case 32: on_log_Ch_6_clicked(); break;
        case 33: on_log_Ch_7_clicked(); break;
        default: ;
        }
        _id -= 34;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
