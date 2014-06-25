/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Jun 25 14:32:56 2014
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
#include <QtGui/QComboBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
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
    QWidget *tab_3;
    QDateTimeEdit *dateTimeEdit;
    QLabel *label_2;
    QWidget *tab;
    QCheckBox *Ch0;
    QCheckBox *Ch7;
    QCheckBox *Ch4;
    QCheckBox *Ch3;
    QCheckBox *Ch5;
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
    QComboBox *periodBox_0;
    QLabel *label_3;
    QComboBox *periodBox_1;
    QComboBox *periodBox_2;
    QComboBox *periodBox_3;
    QComboBox *periodBox_4;
    QComboBox *periodBox_5;
    QComboBox *periodBox_6;
    QComboBox *periodBox_7;
    QLabel *label_4;
    QLabel *label_5;
    QCheckBox *checkBox_5V_Ch_0;
    QCheckBox *checkBox_10V_Ch_0;
    QCheckBox *checkBox_10V_Ch_1;
    QCheckBox *checkBox_5V_Ch_1;
    QCheckBox *checkBox_10V_Ch_2;
    QCheckBox *checkBox_5V_Ch_2;
    QCheckBox *checkBox_10V_Ch_3;
    QCheckBox *checkBox_5V_Ch_3;
    QCheckBox *checkBox_10V_Ch_4;
    QCheckBox *checkBox_5V_Ch_4;
    QCheckBox *checkBox_10V_Ch_5;
    QCheckBox *checkBox_5V_Ch_5;
    QCheckBox *checkBox_10V_Ch_6;
    QCheckBox *checkBox_5V_Ch_6;
    QCheckBox *checkBox_10V_Ch_7;
    QCheckBox *checkBox_5V_Ch_7;
    QWidget *tab_2;
    QLineEdit *ChVal_0;
    QLineEdit *ChVal_1;
    QLineEdit *ChVal_2;
    QLineEdit *ChVal_3;
    QLineEdit *ChVal_4;
    QLineEdit *ChVal_5;
    QLineEdit *ChVal_6;
    QLineEdit *ChVal_7;
    QCheckBox *log_Ch_0;
    QCheckBox *log_Ch_1;
    QCheckBox *log_Ch_2;
    QCheckBox *log_Ch_3;
    QCheckBox *log_Ch_4;
    QCheckBox *log_Ch_5;
    QCheckBox *log_Ch_6;
    QCheckBox *log_Ch_7;
    QLabel *label;
    QWidget *tab_4;
    QPushButton *Start;
    QPushButton *Stop;
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
        Setup->setGeometry(QRect(0, 40, 241, 221));
        Setup->setTabShape(QTabWidget::Rounded);
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        dateTimeEdit = new QDateTimeEdit(tab_3);
        dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));
        dateTimeEdit->setGeometry(QRect(10, 30, 211, 21));
        label_2 = new QLabel(tab_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 10, 181, 16));
        Setup->addTab(tab_3, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        Ch0 = new QCheckBox(tab);
        Ch0->setObjectName(QString::fromUtf8("Ch0"));
        Ch0->setGeometry(QRect(20, 20, 51, 21));
        Ch7 = new QCheckBox(tab);
        Ch7->setObjectName(QString::fromUtf8("Ch7"));
        Ch7->setGeometry(QRect(20, 160, 51, 21));
        Ch4 = new QCheckBox(tab);
        Ch4->setObjectName(QString::fromUtf8("Ch4"));
        Ch4->setGeometry(QRect(20, 100, 51, 21));
        Ch3 = new QCheckBox(tab);
        Ch3->setObjectName(QString::fromUtf8("Ch3"));
        Ch3->setGeometry(QRect(20, 80, 51, 21));
        Ch5 = new QCheckBox(tab);
        Ch5->setObjectName(QString::fromUtf8("Ch5"));
        Ch5->setGeometry(QRect(20, 120, 51, 21));
        ch6_samrate = new QLineEdit(tab);
        ch6_samrate->setObjectName(QString::fromUtf8("ch6_samrate"));
        ch6_samrate->setGeometry(QRect(50, 140, 51, 21));
        Ch1 = new QCheckBox(tab);
        Ch1->setObjectName(QString::fromUtf8("Ch1"));
        Ch1->setGeometry(QRect(20, 40, 51, 21));
        Ch45 = new QCheckBox(tab);
        Ch45->setObjectName(QString::fromUtf8("Ch45"));
        Ch45->setGeometry(QRect(0, 110, 16, 21));
        ch4_samrate = new QLineEdit(tab);
        ch4_samrate->setObjectName(QString::fromUtf8("ch4_samrate"));
        ch4_samrate->setGeometry(QRect(50, 100, 51, 21));
        ch2_samrate = new QLineEdit(tab);
        ch2_samrate->setObjectName(QString::fromUtf8("ch2_samrate"));
        ch2_samrate->setGeometry(QRect(50, 60, 51, 21));
        Ch67 = new QCheckBox(tab);
        Ch67->setObjectName(QString::fromUtf8("Ch67"));
        Ch67->setGeometry(QRect(0, 150, 16, 21));
        ch1_samrate = new QLineEdit(tab);
        ch1_samrate->setObjectName(QString::fromUtf8("ch1_samrate"));
        ch1_samrate->setGeometry(QRect(50, 40, 51, 21));
        Ch6 = new QCheckBox(tab);
        Ch6->setObjectName(QString::fromUtf8("Ch6"));
        Ch6->setGeometry(QRect(20, 140, 51, 21));
        Ch2 = new QCheckBox(tab);
        Ch2->setObjectName(QString::fromUtf8("Ch2"));
        Ch2->setGeometry(QRect(20, 60, 51, 21));
        ch3_samrate = new QLineEdit(tab);
        ch3_samrate->setObjectName(QString::fromUtf8("ch3_samrate"));
        ch3_samrate->setGeometry(QRect(50, 80, 51, 21));
        Ch01 = new QCheckBox(tab);
        Ch01->setObjectName(QString::fromUtf8("Ch01"));
        Ch01->setGeometry(QRect(0, 30, 16, 21));
        ch7_samrate = new QLineEdit(tab);
        ch7_samrate->setObjectName(QString::fromUtf8("ch7_samrate"));
        ch7_samrate->setGeometry(QRect(50, 160, 51, 21));
        Ch23 = new QCheckBox(tab);
        Ch23->setObjectName(QString::fromUtf8("Ch23"));
        Ch23->setGeometry(QRect(0, 70, 16, 21));
        ch5_samrate = new QLineEdit(tab);
        ch5_samrate->setObjectName(QString::fromUtf8("ch5_samrate"));
        ch5_samrate->setGeometry(QRect(50, 120, 51, 21));
        ch0_samrate = new QLineEdit(tab);
        ch0_samrate->setObjectName(QString::fromUtf8("ch0_samrate"));
        ch0_samrate->setGeometry(QRect(50, 20, 51, 21));
        periodBox_0 = new QComboBox(tab);
        periodBox_0->setObjectName(QString::fromUtf8("periodBox_0"));
        periodBox_0->setGeometry(QRect(100, 20, 81, 21));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 0, 51, 16));
        periodBox_1 = new QComboBox(tab);
        periodBox_1->setObjectName(QString::fromUtf8("periodBox_1"));
        periodBox_1->setGeometry(QRect(100, 40, 81, 21));
        periodBox_2 = new QComboBox(tab);
        periodBox_2->setObjectName(QString::fromUtf8("periodBox_2"));
        periodBox_2->setGeometry(QRect(100, 60, 81, 21));
        periodBox_3 = new QComboBox(tab);
        periodBox_3->setObjectName(QString::fromUtf8("periodBox_3"));
        periodBox_3->setGeometry(QRect(100, 80, 81, 21));
        periodBox_4 = new QComboBox(tab);
        periodBox_4->setObjectName(QString::fromUtf8("periodBox_4"));
        periodBox_4->setGeometry(QRect(100, 100, 81, 21));
        periodBox_5 = new QComboBox(tab);
        periodBox_5->setObjectName(QString::fromUtf8("periodBox_5"));
        periodBox_5->setGeometry(QRect(100, 120, 81, 21));
        periodBox_6 = new QComboBox(tab);
        periodBox_6->setObjectName(QString::fromUtf8("periodBox_6"));
        periodBox_6->setGeometry(QRect(100, 140, 81, 21));
        periodBox_7 = new QComboBox(tab);
        periodBox_7->setObjectName(QString::fromUtf8("periodBox_7"));
        periodBox_7->setGeometry(QRect(100, 160, 81, 21));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 0, 21, 16));
        label_5 = new QLabel(tab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(184, 0, 51, 20));
        checkBox_5V_Ch_0 = new QCheckBox(tab);
        checkBox_5V_Ch_0->setObjectName(QString::fromUtf8("checkBox_5V_Ch_0"));
        checkBox_5V_Ch_0->setGeometry(QRect(190, 20, 16, 21));
        checkBox_5V_Ch_0->setChecked(true);
        checkBox_5V_Ch_0->setAutoExclusive(false);
        checkBox_10V_Ch_0 = new QCheckBox(tab);
        checkBox_10V_Ch_0->setObjectName(QString::fromUtf8("checkBox_10V_Ch_0"));
        checkBox_10V_Ch_0->setGeometry(QRect(210, 20, 16, 21));
        checkBox_10V_Ch_0->setAutoExclusive(false);
        checkBox_10V_Ch_1 = new QCheckBox(tab);
        checkBox_10V_Ch_1->setObjectName(QString::fromUtf8("checkBox_10V_Ch_1"));
        checkBox_10V_Ch_1->setGeometry(QRect(210, 40, 16, 21));
        checkBox_10V_Ch_1->setAutoExclusive(false);
        checkBox_5V_Ch_1 = new QCheckBox(tab);
        checkBox_5V_Ch_1->setObjectName(QString::fromUtf8("checkBox_5V_Ch_1"));
        checkBox_5V_Ch_1->setGeometry(QRect(190, 40, 16, 21));
        checkBox_5V_Ch_1->setChecked(true);
        checkBox_5V_Ch_1->setAutoExclusive(false);
        checkBox_10V_Ch_2 = new QCheckBox(tab);
        checkBox_10V_Ch_2->setObjectName(QString::fromUtf8("checkBox_10V_Ch_2"));
        checkBox_10V_Ch_2->setGeometry(QRect(210, 60, 16, 21));
        checkBox_10V_Ch_2->setAutoExclusive(false);
        checkBox_5V_Ch_2 = new QCheckBox(tab);
        checkBox_5V_Ch_2->setObjectName(QString::fromUtf8("checkBox_5V_Ch_2"));
        checkBox_5V_Ch_2->setGeometry(QRect(190, 60, 16, 21));
        checkBox_5V_Ch_2->setChecked(true);
        checkBox_5V_Ch_2->setAutoExclusive(false);
        checkBox_10V_Ch_3 = new QCheckBox(tab);
        checkBox_10V_Ch_3->setObjectName(QString::fromUtf8("checkBox_10V_Ch_3"));
        checkBox_10V_Ch_3->setGeometry(QRect(210, 80, 16, 21));
        checkBox_10V_Ch_3->setAutoExclusive(false);
        checkBox_5V_Ch_3 = new QCheckBox(tab);
        checkBox_5V_Ch_3->setObjectName(QString::fromUtf8("checkBox_5V_Ch_3"));
        checkBox_5V_Ch_3->setGeometry(QRect(190, 80, 16, 21));
        checkBox_5V_Ch_3->setChecked(true);
        checkBox_5V_Ch_3->setAutoExclusive(false);
        checkBox_10V_Ch_4 = new QCheckBox(tab);
        checkBox_10V_Ch_4->setObjectName(QString::fromUtf8("checkBox_10V_Ch_4"));
        checkBox_10V_Ch_4->setGeometry(QRect(210, 100, 16, 21));
        checkBox_10V_Ch_4->setAutoExclusive(false);
        checkBox_5V_Ch_4 = new QCheckBox(tab);
        checkBox_5V_Ch_4->setObjectName(QString::fromUtf8("checkBox_5V_Ch_4"));
        checkBox_5V_Ch_4->setGeometry(QRect(190, 100, 16, 21));
        checkBox_5V_Ch_4->setChecked(true);
        checkBox_5V_Ch_4->setAutoExclusive(false);
        checkBox_10V_Ch_5 = new QCheckBox(tab);
        checkBox_10V_Ch_5->setObjectName(QString::fromUtf8("checkBox_10V_Ch_5"));
        checkBox_10V_Ch_5->setGeometry(QRect(210, 120, 16, 21));
        checkBox_10V_Ch_5->setAutoExclusive(false);
        checkBox_5V_Ch_5 = new QCheckBox(tab);
        checkBox_5V_Ch_5->setObjectName(QString::fromUtf8("checkBox_5V_Ch_5"));
        checkBox_5V_Ch_5->setGeometry(QRect(190, 120, 16, 21));
        checkBox_5V_Ch_5->setChecked(true);
        checkBox_5V_Ch_5->setAutoExclusive(false);
        checkBox_10V_Ch_6 = new QCheckBox(tab);
        checkBox_10V_Ch_6->setObjectName(QString::fromUtf8("checkBox_10V_Ch_6"));
        checkBox_10V_Ch_6->setGeometry(QRect(210, 140, 16, 21));
        checkBox_10V_Ch_6->setAutoExclusive(false);
        checkBox_5V_Ch_6 = new QCheckBox(tab);
        checkBox_5V_Ch_6->setObjectName(QString::fromUtf8("checkBox_5V_Ch_6"));
        checkBox_5V_Ch_6->setGeometry(QRect(190, 140, 16, 21));
        checkBox_5V_Ch_6->setChecked(true);
        checkBox_5V_Ch_6->setAutoExclusive(false);
        checkBox_10V_Ch_7 = new QCheckBox(tab);
        checkBox_10V_Ch_7->setObjectName(QString::fromUtf8("checkBox_10V_Ch_7"));
        checkBox_10V_Ch_7->setGeometry(QRect(210, 160, 16, 21));
        checkBox_10V_Ch_7->setAutoExclusive(false);
        checkBox_5V_Ch_7 = new QCheckBox(tab);
        checkBox_5V_Ch_7->setObjectName(QString::fromUtf8("checkBox_5V_Ch_7"));
        checkBox_5V_Ch_7->setGeometry(QRect(190, 160, 16, 21));
        checkBox_5V_Ch_7->setChecked(true);
        checkBox_5V_Ch_7->setAutoExclusive(false);
        Setup->addTab(tab, QString());
        ch0_samrate->raise();
        Ch0->raise();
        Ch7->raise();
        Ch4->raise();
        Ch3->raise();
        Ch5->raise();
        ch6_samrate->raise();
        Ch1->raise();
        Ch45->raise();
        ch4_samrate->raise();
        ch2_samrate->raise();
        Ch67->raise();
        ch1_samrate->raise();
        Ch6->raise();
        Ch2->raise();
        ch3_samrate->raise();
        Ch01->raise();
        ch7_samrate->raise();
        Ch23->raise();
        ch5_samrate->raise();
        periodBox_0->raise();
        label_3->raise();
        periodBox_1->raise();
        periodBox_2->raise();
        periodBox_3->raise();
        periodBox_4->raise();
        periodBox_5->raise();
        periodBox_6->raise();
        periodBox_7->raise();
        label_4->raise();
        label_5->raise();
        checkBox_5V_Ch_0->raise();
        checkBox_10V_Ch_0->raise();
        checkBox_10V_Ch_1->raise();
        checkBox_5V_Ch_1->raise();
        checkBox_10V_Ch_2->raise();
        checkBox_5V_Ch_2->raise();
        checkBox_10V_Ch_3->raise();
        checkBox_5V_Ch_3->raise();
        checkBox_10V_Ch_4->raise();
        checkBox_5V_Ch_4->raise();
        checkBox_10V_Ch_5->raise();
        checkBox_5V_Ch_5->raise();
        checkBox_10V_Ch_6->raise();
        checkBox_5V_Ch_6->raise();
        checkBox_10V_Ch_7->raise();
        checkBox_5V_Ch_7->raise();
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        ChVal_0 = new QLineEdit(tab_2);
        ChVal_0->setObjectName(QString::fromUtf8("ChVal_0"));
        ChVal_0->setGeometry(QRect(12, 20, 181, 21));
        ChVal_1 = new QLineEdit(tab_2);
        ChVal_1->setObjectName(QString::fromUtf8("ChVal_1"));
        ChVal_1->setGeometry(QRect(12, 40, 181, 21));
        ChVal_2 = new QLineEdit(tab_2);
        ChVal_2->setObjectName(QString::fromUtf8("ChVal_2"));
        ChVal_2->setGeometry(QRect(12, 60, 181, 21));
        ChVal_3 = new QLineEdit(tab_2);
        ChVal_3->setObjectName(QString::fromUtf8("ChVal_3"));
        ChVal_3->setGeometry(QRect(12, 80, 181, 21));
        ChVal_4 = new QLineEdit(tab_2);
        ChVal_4->setObjectName(QString::fromUtf8("ChVal_4"));
        ChVal_4->setGeometry(QRect(12, 100, 181, 21));
        ChVal_5 = new QLineEdit(tab_2);
        ChVal_5->setObjectName(QString::fromUtf8("ChVal_5"));
        ChVal_5->setGeometry(QRect(12, 120, 181, 21));
        ChVal_6 = new QLineEdit(tab_2);
        ChVal_6->setObjectName(QString::fromUtf8("ChVal_6"));
        ChVal_6->setGeometry(QRect(12, 140, 181, 21));
        ChVal_7 = new QLineEdit(tab_2);
        ChVal_7->setObjectName(QString::fromUtf8("ChVal_7"));
        ChVal_7->setGeometry(QRect(12, 160, 181, 21));
        log_Ch_0 = new QCheckBox(tab_2);
        log_Ch_0->setObjectName(QString::fromUtf8("log_Ch_0"));
        log_Ch_0->setGeometry(QRect(210, 20, 16, 21));
        log_Ch_1 = new QCheckBox(tab_2);
        log_Ch_1->setObjectName(QString::fromUtf8("log_Ch_1"));
        log_Ch_1->setGeometry(QRect(210, 40, 16, 21));
        log_Ch_2 = new QCheckBox(tab_2);
        log_Ch_2->setObjectName(QString::fromUtf8("log_Ch_2"));
        log_Ch_2->setGeometry(QRect(210, 60, 16, 21));
        log_Ch_3 = new QCheckBox(tab_2);
        log_Ch_3->setObjectName(QString::fromUtf8("log_Ch_3"));
        log_Ch_3->setGeometry(QRect(210, 80, 16, 21));
        log_Ch_4 = new QCheckBox(tab_2);
        log_Ch_4->setObjectName(QString::fromUtf8("log_Ch_4"));
        log_Ch_4->setGeometry(QRect(210, 100, 16, 21));
        log_Ch_5 = new QCheckBox(tab_2);
        log_Ch_5->setObjectName(QString::fromUtf8("log_Ch_5"));
        log_Ch_5->setGeometry(QRect(210, 120, 16, 21));
        log_Ch_6 = new QCheckBox(tab_2);
        log_Ch_6->setObjectName(QString::fromUtf8("log_Ch_6"));
        log_Ch_6->setGeometry(QRect(210, 140, 16, 21));
        log_Ch_7 = new QCheckBox(tab_2);
        log_Ch_7->setObjectName(QString::fromUtf8("log_Ch_7"));
        log_Ch_7->setGeometry(QRect(210, 160, 16, 21));
        label = new QLabel(tab_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(210, 0, 31, 16));
        Setup->addTab(tab_2, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        Setup->addTab(tab_4, QString());
        Start = new QPushButton(centralWidget);
        Start->setObjectName(QString::fromUtf8("Start"));
        Start->setGeometry(QRect(0, 20, 121, 21));
        Stop = new QPushButton(centralWidget);
        Stop->setObjectName(QString::fromUtf8("Stop"));
        Stop->setGeometry(QRect(120, 20, 121, 21));
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
        periodBox_0->setCurrentIndex(3);
        periodBox_1->setCurrentIndex(3);
        periodBox_2->setCurrentIndex(3);
        periodBox_3->setCurrentIndex(3);
        periodBox_4->setCurrentIndex(3);
        periodBox_5->setCurrentIndex(3);
        periodBox_6->setCurrentIndex(3);
        periodBox_7->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ADC", 0, QApplication::UnicodeUTF8));
        actionSave_Preferences->setText(QApplication::translate("MainWindow", "Save Preferences", 0, QApplication::UnicodeUTF8));
        actionOpen_Preferences->setText(QApplication::translate("MainWindow", "Open Preferences", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Set date and time", 0, QApplication::UnicodeUTF8));
        Setup->setTabText(Setup->indexOf(tab_3), QApplication::translate("MainWindow", "Time", 0, QApplication::UnicodeUTF8));
        Ch0->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        Ch7->setText(QApplication::translate("MainWindow", "7", 0, QApplication::UnicodeUTF8));
        Ch4->setText(QApplication::translate("MainWindow", "4", 0, QApplication::UnicodeUTF8));
        Ch3->setText(QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8));
        Ch5->setText(QApplication::translate("MainWindow", "5", 0, QApplication::UnicodeUTF8));
        ch6_samrate->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        Ch1->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        Ch45->setText(QString());
        ch4_samrate->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        ch2_samrate->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        Ch67->setText(QString());
        ch1_samrate->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        Ch6->setText(QApplication::translate("MainWindow", "6", 0, QApplication::UnicodeUTF8));
        Ch2->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
        ch3_samrate->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        Ch01->setText(QString());
        ch7_samrate->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        Ch23->setText(QString());
        ch5_samrate->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        ch0_samrate->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        periodBox_0->clear();
        periodBox_0->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "days", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "hours", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "minutes", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "seconds", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "msecs", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "usecs", 0, QApplication::UnicodeUTF8)
        );
        label_3->setText(QApplication::translate("MainWindow", "Period", 0, QApplication::UnicodeUTF8));
        periodBox_1->clear();
        periodBox_1->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "days", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "hours", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "minutes", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "seconds", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "msecs", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "usecs", 0, QApplication::UnicodeUTF8)
        );
        periodBox_2->clear();
        periodBox_2->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "days", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "hours", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "minutes", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "seconds", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "msecs", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "usecs", 0, QApplication::UnicodeUTF8)
        );
        periodBox_3->clear();
        periodBox_3->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "days", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "hours", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "minutes", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "seconds", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "msecs", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "usecs", 0, QApplication::UnicodeUTF8)
        );
        periodBox_4->clear();
        periodBox_4->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "days", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "hours", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "minutes", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "seconds", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "msecs", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "usecs", 0, QApplication::UnicodeUTF8)
        );
        periodBox_5->clear();
        periodBox_5->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "days", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "hours", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "minutes", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "seconds", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "msecs", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "usecs", 0, QApplication::UnicodeUTF8)
        );
        periodBox_6->clear();
        periodBox_6->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "days", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "hours", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "minutes", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "seconds", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "msecs", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "usecs", 0, QApplication::UnicodeUTF8)
        );
        periodBox_7->clear();
        periodBox_7->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "days", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "hours", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "minutes", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "seconds", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "msecs", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "usecs", 0, QApplication::UnicodeUTF8)
        );
        label_4->setText(QApplication::translate("MainWindow", "Ch", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "5V 10V", 0, QApplication::UnicodeUTF8));
        checkBox_5V_Ch_0->setText(QString());
        checkBox_10V_Ch_0->setText(QString());
        checkBox_10V_Ch_1->setText(QString());
        checkBox_5V_Ch_1->setText(QString());
        checkBox_10V_Ch_2->setText(QString());
        checkBox_5V_Ch_2->setText(QString());
        checkBox_10V_Ch_3->setText(QString());
        checkBox_5V_Ch_3->setText(QString());
        checkBox_10V_Ch_4->setText(QString());
        checkBox_5V_Ch_4->setText(QString());
        checkBox_10V_Ch_5->setText(QString());
        checkBox_5V_Ch_5->setText(QString());
        checkBox_10V_Ch_6->setText(QString());
        checkBox_5V_Ch_6->setText(QString());
        checkBox_10V_Ch_7->setText(QString());
        checkBox_5V_Ch_7->setText(QString());
        Setup->setTabText(Setup->indexOf(tab), QApplication::translate("MainWindow", "Channel", 0, QApplication::UnicodeUTF8));
        log_Ch_0->setText(QString());
        log_Ch_1->setText(QString());
        log_Ch_2->setText(QString());
        log_Ch_3->setText(QString());
        log_Ch_4->setText(QString());
        log_Ch_5->setText(QString());
        log_Ch_6->setText(QString());
        log_Ch_7->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Log", 0, QApplication::UnicodeUTF8));
        Setup->setTabText(Setup->indexOf(tab_2), QApplication::translate("MainWindow", "Data", 0, QApplication::UnicodeUTF8));
        Setup->setTabText(Setup->indexOf(tab_4), QApplication::translate("MainWindow", "Graph", 0, QApplication::UnicodeUTF8));
        Start->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        Stop->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        menuMenu->setTitle(QApplication::translate("MainWindow", "Menu", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
