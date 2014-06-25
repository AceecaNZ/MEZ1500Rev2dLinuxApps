/****************************************************************************
** Meta object code from reading C++ file 'keyboard.h'
**
** Created: Thu Jun 19 16:09:04 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "keyboard/keyboard.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'keyboard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Keyboard[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      28,    9,    9,    9, 0x08,
      55,   47,    9,    9, 0x08,
      79,    9,    9,    9, 0x08,
      98,    9,    9,    9, 0x08,
     128,  123,    9,    9, 0x08,
     161,    9,    9,    9, 0x08,
     189,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Keyboard[] = {
    "Keyboard\0\0keyboardHandler()\0"
    "on_shift_clicked()\0checked\0"
    "on_char_2_toggled(bool)\0on_clear_clicked()\0"
    "on_enterButton_clicked()\0arg1\0"
    "on_lineEdit_textChanged(QString)\0"
    "on_lineEdit_returnPressed()\0"
    "on_backButton_clicked()\0"
};

const QMetaObject Keyboard::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Keyboard,
      qt_meta_data_Keyboard, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Keyboard::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Keyboard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Keyboard::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Keyboard))
        return static_cast<void*>(const_cast< Keyboard*>(this));
    return QWidget::qt_metacast(_clname);
}

int Keyboard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: keyboardHandler(); break;
        case 1: on_shift_clicked(); break;
        case 2: on_char_2_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: on_clear_clicked(); break;
        case 4: on_enterButton_clicked(); break;
        case 5: on_lineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: on_lineEdit_returnPressed(); break;
        case 7: on_backButton_clicked(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
