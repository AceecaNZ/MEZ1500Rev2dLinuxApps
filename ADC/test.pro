#-------------------------------------------------
#
# Project created by QtCreator 2014-03-11T15:17:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ADC

target.files = test
target.path = /root
INSTALLS += target

TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
    keyboard/keyboard.cpp

HEADERS  += mainwindow.h\
        adc1.h\
        /opt/MEZ1500Rev2dLinux/Sources/linux-2.6.32.2/drivers/char/MEZ1500_mzio_ltc185x.h\
    keyboard/keyboard.h \
    keyboard/ui_keyboard.h \
    ui_keyboard.h

FORMS    += mainwindow.ui \
    keyboard/keyboard.ui
