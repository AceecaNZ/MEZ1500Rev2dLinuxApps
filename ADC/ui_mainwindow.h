/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon May 19 15:15:29 2014
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
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave_Preferences;
    QAction *actionOpen_Preferences;
    QWidget *centralWidget;
    QLineEdit *status;
    QTabWidget *Setup;
    QWidget *tab;
    QCheckBox *Ch0;
    QCheckBox *Ch7;
    QCheckBox *Ch4;
    QCheckBox *Ch3;
    QCheckBox *Ch5;
    QLabel *label;
    QLineEdit *ch6_samrate;
    QCheckBox *Ch1;
    QCheckBox *Ch45;
    QLineEdit *ch4_samrate;
    QLineEdit *ch2_samrate;
    QCheckBox *Ch67;
    QLineEdit *ch1_samrate;
    QCheckBox *Ch6;
    QCheckBox *Ch2;
    QLineEdit *ch3_samrate;
    QCheckBox *Ch01;
    QLineEdit *ch7_samrate;
    QCheckBox *Ch23;
    QLineEdit *ch5_samrate;
    QLineEdit *ch0_samrate;
    QRadioButton *ch0_radio;
    QRadioButton *ch1_radio;
    QRadioButton *ch2_radio;
    QRadioButton *ch3_radio;
    QRadioButton *ch4_radio;
    QRadioButton *ch5_radio;
    QRadioButton *ch6_radio;
    QRadioButton *ch7_radio;
    QPushButton *up;
    QPushButton *down;
    QWidget *tab_2;
    QPushButton *Start;
    QPushButton *Stop;
    QPushButton *readButton;
    QMenuBar *menuBar;
    QMenu *menuMenu;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(240, 320);
        MainWindow->setCursor(QCursor(Qt::ArrowCursor));
        actionSave_Preferences = new QAction(MainWindow);
        actionSave_Preferences->setObjectName(QString::fromUtf8("actionSave_Preferences"));
        actionOpen_Preferences = new QAction(MainWindow);
        actionOpen_Preferences->setObjectName(QString::fromUtf8("actionOpen_Preferences"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        status = new QLineEdit(centralWidget);
        status->setObjectName(QString::fromUtf8("status"));
        status->setGeometry(QRect(10, 0, 221, 23));
        Setup = new QTabWidget(centralWidget);
        Setup->setObjectName(QString::fromUtf8("Setup"));
        Setup->setGeometry(QRect(0, 30, 241, 251));
        Setup->setTabShape(QTabWidget::Rounded);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        Ch0 = new QCheckBox(tab);
        Ch0->setObjectName(QString::fromUtf8("Ch0"));
        Ch0->setGeometry(QRect(20, 20, 85, 21));
        Ch7 = new QCheckBox(tab);
        Ch7->setObjectName(QString::fromUtf8("Ch7"));
        Ch7->setGeometry(QRect(20, 160, 85, 21));
        Ch4 = new QCheckBox(tab);
        Ch4->setObjectName(QString::fromUtf8("Ch4"));
        Ch4->setGeometry(QRect(20, 100, 85, 21));
        Ch3 = new QCheckBox(tab);
        Ch3->setObjectName(QString::fromUtf8("Ch3"));
        Ch3->setGeometry(QRect(20, 80, 85, 21));
        Ch5 = new QCheckBox(tab);
        Ch5->setObjectName(QString::fromUtf8("Ch5"));
        Ch5->setGeometry(QRect(20, 120, 85, 21));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 0, 151, 16));
        ch6_samrate = new QLineEdit(tab);
        ch6_samrate->setObjectName(QString::fromUtf8("ch6_samrate"));
        ch6_samrate->setGeometry(QRect(70, 140, 81, 21));
        Ch1 = new QCheckBox(tab);
        Ch1->setObjectName(QString::fromUtf8("Ch1"));
        Ch1->setGeometry(QRect(20, 40, 85, 21));
        Ch45 = new QCheckBox(tab);
        Ch45->setObjectName(QString::fromUtf8("Ch45"));
        Ch45->setGeometry(QRect(0, 110, 85, 21));
        ch4_samrate = new QLineEdit(tab);
        ch4_samrate->setObjectName(QString::fromUtf8("ch4_samrate"));
        ch4_samrate->setGeometry(QRect(70, 100, 81, 21));
        ch2_samrate = new QLineEdit(tab);
        ch2_samrate->setObjectName(QString::fromUtf8("ch2_samrate"));
        ch2_samrate->setGeometry(QRect(70, 60, 81, 21));
        Ch67 = new QCheckBox(tab);
        Ch67->setObjectName(QString::fromUtf8("Ch67"));
        Ch67->setGeometry(QRect(0, 150, 85, 21));
        ch1_samrate = new QLineEdit(tab);
        ch1_samrate->setObjectName(QString::fromUtf8("ch1_samrate"));
        ch1_samrate->setGeometry(QRect(70, 40, 81, 21));
        Ch6 = new QCheckBox(tab);
        Ch6->setObjectName(QString::fromUtf8("Ch6"));
        Ch6->setGeometry(QRect(20, 140, 85, 21));
        Ch2 = new QCheckBox(tab);
        Ch2->setObjectName(QString::fromUtf8("Ch2"));
        Ch2->setGeometry(QRect(20, 60, 85, 21));
        ch3_samrate = new QLineEdit(tab);
        ch3_samrate->setObjectName(QString::fromUtf8("ch3_samrate"));
        ch3_samrate->setGeometry(QRect(70, 80, 81, 21));
        Ch01 = new QCheckBox(tab);
        Ch01->setObjectName(QString::fromUtf8("Ch01"));
        Ch01->setGeometry(QRect(0, 30, 85, 21));
        ch7_samrate = new QLineEdit(tab);
        ch7_samrate->setObjectName(QString::fromUtf8("ch7_samrate"));
        ch7_samrate->setGeometry(QRect(70, 160, 81, 21));
        Ch23 = new QCheckBox(tab);
        Ch23->setObjectName(QString::fromUtf8("Ch23"));
        Ch23->setGeometry(QRect(0, 70, 85, 21));
        ch5_samrate = new QLineEdit(tab);
        ch5_samrate->setObjectName(QString::fromUtf8("ch5_samrate"));
        ch5_samrate->setGeometry(QRect(70, 120, 81, 21));
        ch0_samrate = new QLineEdit(tab);
        ch0_samrate->setObjectName(QString::fromUtf8("ch0_samrate"));
        ch0_samrate->setGeometry(QRect(70, 20, 81, 21));
        ch0_radio = new QRadioButton(tab);
        ch0_radio->setObjectName(QString::fromUtf8("ch0_radio"));
        ch0_radio->setGeometry(QRect(160, 20, 21, 21));
        ch0_radio->setChecked(true);
        ch1_radio = new QRadioButton(tab);
        ch1_radio->setObjectName(QString::fromUtf8("ch1_radio"));
        ch1_radio->setGeometry(QRect(160, 40, 21, 21));
        ch1_radio->setChecked(false);
        ch2_radio = new QRadioButton(tab);
        ch2_radio->setObjectName(QString::fromUtf8("ch2_radio"));
        ch2_radio->setGeometry(QRect(160, 60, 21, 21));
        ch2_radio->setChecked(false);
        ch3_radio = new QRadioButton(tab);
        ch3_radio->setObjectName(QString::fromUtf8("ch3_radio"));
        ch3_radio->setGeometry(QRect(160, 80, 21, 21));
        ch3_radio->setChecked(false);
        ch4_radio = new QRadioButton(tab);
        ch4_radio->setObjectName(QString::fromUtf8("ch4_radio"));
        ch4_radio->setGeometry(QRect(160, 100, 21, 21));
        ch4_radio->setChecked(false);
        ch5_radio = new QRadioButton(tab);
        ch5_radio->setObjectName(QString::fromUtf8("ch5_radio"));
        ch5_radio->setGeometry(QRect(160, 120, 21, 21));
        ch5_radio->setChecked(false);
        ch6_radio = new QRadioButton(tab);
        ch6_radio->setObjectName(QString::fromUtf8("ch6_radio"));
        ch6_radio->setGeometry(QRect(160, 140, 21, 21));
        ch6_radio->setChecked(false);
        ch7_radio = new QRadioButton(tab);
        ch7_radio->setObjectName(QString::fromUtf8("ch7_radio"));
        ch7_radio->setGeometry(QRect(160, 160, 21, 21));
        ch7_radio->setChecked(false);
        up = new QPushButton(tab);
        up->setObjectName(QString::fromUtf8("up"));
        up->setGeometry(QRect(180, 20, 51, 71));
        up->setCheckable(false);
        up->setAutoRepeat(true);
        down = new QPushButton(tab);
        down->setObjectName(QString::fromUtf8("down"));
        down->setGeometry(QRect(180, 102, 51, 81));
        down->setAutoRepeat(true);
        Setup->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        Start = new QPushButton(tab_2);
        Start->setObjectName(QString::fromUtf8("Start"));
        Start->setGeometry(QRect(10, 150, 51, 27));
        Stop = new QPushButton(tab_2);
        Stop->setObjectName(QString::fromUtf8("Stop"));
        Stop->setGeometry(QRect(60, 150, 51, 27));
        readButton = new QPushButton(tab_2);
        readButton->setObjectName(QString::fromUtf8("readButton"));
        readButton->setGeometry(QRect(140, 150, 80, 21));
        Setup->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 240, 20));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuMenu->menuAction());
        menuMenu->addAction(actionOpen_Preferences);
        menuMenu->addAction(actionSave_Preferences);

        retranslateUi(MainWindow);

        Setup->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ADC", 0, QApplication::UnicodeUTF8));
        actionSave_Preferences->setText(QApplication::translate("MainWindow", "Save Preferences", 0, QApplication::UnicodeUTF8));
        actionOpen_Preferences->setText(QApplication::translate("MainWindow", "Open Preferences", 0, QApplication::UnicodeUTF8));
        Ch0->setText(QApplication::translate("MainWindow", "Ch0", 0, QApplication::UnicodeUTF8));
        Ch7->setText(QApplication::translate("MainWindow", "Ch7", 0, QApplication::UnicodeUTF8));
        Ch4->setText(QApplication::translate("MainWindow", "Ch4", 0, QApplication::UnicodeUTF8));
        Ch3->setText(QApplication::translate("MainWindow", "Ch3", 0, QApplication::UnicodeUTF8));
        Ch5->setText(QApplication::translate("MainWindow", "Ch5", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Sample Rate (us)", 0, QApplication::UnicodeUTF8));
        Ch1->setText(QApplication::translate("MainWindow", "Ch1", 0, QApplication::UnicodeUTF8));
        Ch45->setText(QString());
        Ch67->setText(QString());
        Ch6->setText(QApplication::translate("MainWindow", "Ch6", 0, QApplication::UnicodeUTF8));
        Ch2->setText(QApplication::translate("MainWindow", "Ch2", 0, QApplication::UnicodeUTF8));
        Ch01->setText(QString());
        Ch23->setText(QString());
        ch0_radio->setText(QString());
        ch1_radio->setText(QString());
        ch2_radio->setText(QString());
        ch3_radio->setText(QString());
        ch4_radio->setText(QString());
        ch5_radio->setText(QString());
        ch6_radio->setText(QString());
        ch7_radio->setText(QString());
        up->setText(QApplication::translate("MainWindow", "Up", 0, QApplication::UnicodeUTF8));
        down->setText(QApplication::translate("MainWindow", "Down", 0, QApplication::UnicodeUTF8));
        Setup->setTabText(Setup->indexOf(tab), QApplication::translate("MainWindow", "Setup", 0, QApplication::UnicodeUTF8));
        Start->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        Stop->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        readButton->setText(QApplication::translate("MainWindow", "Read", 0, QApplication::UnicodeUTF8));
        Setup->setTabText(Setup->indexOf(tab_2), QApplication::translate("MainWindow", "Data", 0, QApplication::UnicodeUTF8));
        menuMenu->setTitle(QApplication::translate("MainWindow", "Menu", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
