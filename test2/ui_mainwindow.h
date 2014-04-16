/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon Apr 14 16:49:01 2014
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *modpwron;
    QLineEdit *status;
    QPushButton *modpwroff;
    QPushButton *modrstoff;
    QPushButton *modrston;
    QPushButton *initadc;
    QPushButton *readADC;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(240, 320);
        MainWindow->setCursor(QCursor(Qt::ArrowCursor));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        modpwron = new QPushButton(centralWidget);
        modpwron->setObjectName(QString::fromUtf8("modpwron"));
        modpwron->setGeometry(QRect(10, 30, 101, 27));
        status = new QLineEdit(centralWidget);
        status->setObjectName(QString::fromUtf8("status"));
        status->setGeometry(QRect(10, 0, 221, 23));
        modpwroff = new QPushButton(centralWidget);
        modpwroff->setObjectName(QString::fromUtf8("modpwroff"));
        modpwroff->setGeometry(QRect(130, 30, 101, 27));
        modrstoff = new QPushButton(centralWidget);
        modrstoff->setObjectName(QString::fromUtf8("modrstoff"));
        modrstoff->setGeometry(QRect(130, 60, 101, 27));
        modrston = new QPushButton(centralWidget);
        modrston->setObjectName(QString::fromUtf8("modrston"));
        modrston->setGeometry(QRect(10, 60, 101, 27));
        initadc = new QPushButton(centralWidget);
        initadc->setObjectName(QString::fromUtf8("initadc"));
        initadc->setGeometry(QRect(10, 110, 101, 27));
        readADC = new QPushButton(centralWidget);
        readADC->setObjectName(QString::fromUtf8("readADC"));
        readADC->setGeometry(QRect(140, 110, 91, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 240, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        modpwron->setText(QApplication::translate("MainWindow", "MOD_PWR On", 0, QApplication::UnicodeUTF8));
        modpwroff->setText(QApplication::translate("MainWindow", "MOD_PWR Off", 0, QApplication::UnicodeUTF8));
        modrstoff->setText(QApplication::translate("MainWindow", "MOD_RESET Off", 0, QApplication::UnicodeUTF8));
        modrston->setText(QApplication::translate("MainWindow", "MOD_RESET On", 0, QApplication::UnicodeUTF8));
        initadc->setText(QApplication::translate("MainWindow", "Init ADC", 0, QApplication::UnicodeUTF8));
        readADC->setText(QApplication::translate("MainWindow", "Read ADC", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
