/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Aug 7 22:31:31 2014
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
    QTabWidget *TabDisplay;
    QWidget *tab_3;
    QDateTimeEdit *dateTimeEdit;
    QLabel *label_2;
    QPushButton *DeleteCSV;
    QWidget *tab_2;
    QLineEdit *Value_ch_0;
    QLineEdit *Value_ch_1;
    QLineEdit *Value_ch_2;
    QLineEdit *Value_ch_3;
    QLineEdit *Value_ch_4;
    QLineEdit *Value_ch_5;
    QLineEdit *Value_ch_6;
    QLineEdit *Value_ch_7;
    QCheckBox *select_ch_0;
    QCheckBox *select_ch_1;
    QCheckBox *select_ch_2;
    QCheckBox *select_ch_3;
    QCheckBox *select_ch_4;
    QCheckBox *select_ch_5;
    QCheckBox *select_ch_6;
    QCheckBox *select_ch_7;
    QLabel *label_12;
    QCheckBox *log_Ch_3;
    QCheckBox *log_Ch_4;
    QCheckBox *log_Ch_0;
    QCheckBox *log_Ch_5;
    QLabel *label;
    QCheckBox *log_Ch_6;
    QCheckBox *log_Ch_2;
    QCheckBox *log_Ch_7;
    QCheckBox *log_Ch_1;
    QWidget *tab;
    QLineEdit *samrate_ch_0;
    QComboBox *periodBox_ch_0;
    QLabel *label_3;
    QLineEdit *samrate_ch_1;
    QLineEdit *samrate_ch_2;
    QLineEdit *samrate_ch_3;
    QLineEdit *samrate_ch_4;
    QLineEdit *samrate_ch_5;
    QLineEdit *samrate_ch_6;
    QLineEdit *samrate_ch_7;
    QComboBox *periodBox_ch_1;
    QComboBox *periodBox_ch_2;
    QComboBox *periodBox_ch_3;
    QComboBox *periodBox_ch_4;
    QComboBox *periodBox_ch_5;
    QComboBox *periodBox_ch_6;
    QComboBox *periodBox_ch_7;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QPushButton *Start;
    QPushButton *Stop;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->resize(243, 321);
        MainWindow->setCursor(QCursor(Qt::ArrowCursor));
        MainWindow->setAutoFillBackground(false);
        actionSave_Preferences = new QAction(MainWindow);
        actionSave_Preferences->setObjectName(QString::fromUtf8("actionSave_Preferences"));
        actionOpen_Preferences = new QAction(MainWindow);
        actionOpen_Preferences->setObjectName(QString::fromUtf8("actionOpen_Preferences"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        status = new QLineEdit(centralWidget);
        status->setObjectName(QString::fromUtf8("status"));
        status->setGeometry(QRect(10, 10, 221, 23));
        TabDisplay = new QTabWidget(centralWidget);
        TabDisplay->setObjectName(QString::fromUtf8("TabDisplay"));
        TabDisplay->setGeometry(QRect(1, 40, 240, 231));
        TabDisplay->setTabShape(QTabWidget::Rounded);
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        dateTimeEdit = new QDateTimeEdit(tab_3);
        dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));
        dateTimeEdit->setGeometry(QRect(10, 30, 211, 21));
        label_2 = new QLabel(tab_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 10, 181, 16));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        DeleteCSV = new QPushButton(tab_3);
        DeleteCSV->setObjectName(QString::fromUtf8("DeleteCSV"));
        DeleteCSV->setGeometry(QRect(10, 60, 161, 23));
        TabDisplay->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        Value_ch_0 = new QLineEdit(tab_2);
        Value_ch_0->setObjectName(QString::fromUtf8("Value_ch_0"));
        Value_ch_0->setGeometry(QRect(80, 30, 101, 21));
        Value_ch_0->setReadOnly(true);
        Value_ch_1 = new QLineEdit(tab_2);
        Value_ch_1->setObjectName(QString::fromUtf8("Value_ch_1"));
        Value_ch_1->setGeometry(QRect(80, 50, 101, 21));
        Value_ch_1->setReadOnly(true);
        Value_ch_2 = new QLineEdit(tab_2);
        Value_ch_2->setObjectName(QString::fromUtf8("Value_ch_2"));
        Value_ch_2->setGeometry(QRect(80, 70, 101, 21));
        Value_ch_2->setReadOnly(true);
        Value_ch_3 = new QLineEdit(tab_2);
        Value_ch_3->setObjectName(QString::fromUtf8("Value_ch_3"));
        Value_ch_3->setGeometry(QRect(80, 90, 101, 21));
        Value_ch_3->setReadOnly(true);
        Value_ch_4 = new QLineEdit(tab_2);
        Value_ch_4->setObjectName(QString::fromUtf8("Value_ch_4"));
        Value_ch_4->setGeometry(QRect(80, 110, 101, 21));
        Value_ch_4->setReadOnly(true);
        Value_ch_5 = new QLineEdit(tab_2);
        Value_ch_5->setObjectName(QString::fromUtf8("Value_ch_5"));
        Value_ch_5->setGeometry(QRect(80, 130, 101, 21));
        Value_ch_5->setReadOnly(true);
        Value_ch_6 = new QLineEdit(tab_2);
        Value_ch_6->setObjectName(QString::fromUtf8("Value_ch_6"));
        Value_ch_6->setGeometry(QRect(80, 150, 101, 21));
        Value_ch_6->setReadOnly(true);
        Value_ch_7 = new QLineEdit(tab_2);
        Value_ch_7->setObjectName(QString::fromUtf8("Value_ch_7"));
        Value_ch_7->setGeometry(QRect(80, 170, 101, 21));
        Value_ch_7->setReadOnly(true);
        select_ch_0 = new QCheckBox(tab_2);
        select_ch_0->setObjectName(QString::fromUtf8("select_ch_0"));
        select_ch_0->setGeometry(QRect(20, 30, 51, 21));
        select_ch_0->setChecked(true);
        select_ch_1 = new QCheckBox(tab_2);
        select_ch_1->setObjectName(QString::fromUtf8("select_ch_1"));
        select_ch_1->setGeometry(QRect(20, 50, 51, 21));
        select_ch_1->setChecked(true);
        select_ch_2 = new QCheckBox(tab_2);
        select_ch_2->setObjectName(QString::fromUtf8("select_ch_2"));
        select_ch_2->setGeometry(QRect(20, 70, 51, 21));
        select_ch_2->setChecked(true);
        select_ch_3 = new QCheckBox(tab_2);
        select_ch_3->setObjectName(QString::fromUtf8("select_ch_3"));
        select_ch_3->setGeometry(QRect(20, 90, 51, 21));
        select_ch_3->setChecked(true);
        select_ch_4 = new QCheckBox(tab_2);
        select_ch_4->setObjectName(QString::fromUtf8("select_ch_4"));
        select_ch_4->setGeometry(QRect(20, 110, 51, 21));
        select_ch_4->setChecked(true);
        select_ch_5 = new QCheckBox(tab_2);
        select_ch_5->setObjectName(QString::fromUtf8("select_ch_5"));
        select_ch_5->setGeometry(QRect(20, 130, 51, 21));
        select_ch_5->setChecked(true);
        select_ch_6 = new QCheckBox(tab_2);
        select_ch_6->setObjectName(QString::fromUtf8("select_ch_6"));
        select_ch_6->setGeometry(QRect(20, 150, 51, 21));
        select_ch_6->setChecked(true);
        select_ch_7 = new QCheckBox(tab_2);
        select_ch_7->setObjectName(QString::fromUtf8("select_ch_7"));
        select_ch_7->setGeometry(QRect(20, 170, 51, 21));
        select_ch_7->setChecked(true);
        label_12 = new QLabel(tab_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(20, 10, 57, 15));
        label_12->setFont(font);
        log_Ch_3 = new QCheckBox(tab_2);
        log_Ch_3->setObjectName(QString::fromUtf8("log_Ch_3"));
        log_Ch_3->setGeometry(QRect(190, 90, 16, 21));
        log_Ch_3->setChecked(true);
        log_Ch_4 = new QCheckBox(tab_2);
        log_Ch_4->setObjectName(QString::fromUtf8("log_Ch_4"));
        log_Ch_4->setGeometry(QRect(190, 110, 16, 21));
        log_Ch_4->setChecked(true);
        log_Ch_0 = new QCheckBox(tab_2);
        log_Ch_0->setObjectName(QString::fromUtf8("log_Ch_0"));
        log_Ch_0->setGeometry(QRect(190, 30, 16, 21));
        log_Ch_0->setChecked(true);
        log_Ch_5 = new QCheckBox(tab_2);
        log_Ch_5->setObjectName(QString::fromUtf8("log_Ch_5"));
        log_Ch_5->setGeometry(QRect(190, 130, 16, 21));
        log_Ch_5->setChecked(true);
        label = new QLabel(tab_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(190, 10, 31, 16));
        label->setFont(font);
        log_Ch_6 = new QCheckBox(tab_2);
        log_Ch_6->setObjectName(QString::fromUtf8("log_Ch_6"));
        log_Ch_6->setGeometry(QRect(190, 150, 16, 21));
        log_Ch_6->setChecked(true);
        log_Ch_2 = new QCheckBox(tab_2);
        log_Ch_2->setObjectName(QString::fromUtf8("log_Ch_2"));
        log_Ch_2->setGeometry(QRect(190, 70, 16, 21));
        log_Ch_2->setChecked(true);
        log_Ch_7 = new QCheckBox(tab_2);
        log_Ch_7->setObjectName(QString::fromUtf8("log_Ch_7"));
        log_Ch_7->setGeometry(QRect(190, 170, 16, 21));
        log_Ch_7->setChecked(true);
        log_Ch_1 = new QCheckBox(tab_2);
        log_Ch_1->setObjectName(QString::fromUtf8("log_Ch_1"));
        log_Ch_1->setGeometry(QRect(190, 50, 16, 21));
        log_Ch_1->setChecked(true);
        TabDisplay->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        samrate_ch_0 = new QLineEdit(tab);
        samrate_ch_0->setObjectName(QString::fromUtf8("samrate_ch_0"));
        samrate_ch_0->setGeometry(QRect(50, 30, 61, 21));
        periodBox_ch_0 = new QComboBox(tab);
        periodBox_ch_0->setObjectName(QString::fromUtf8("periodBox_ch_0"));
        periodBox_ch_0->setGeometry(QRect(110, 30, 111, 21));
        periodBox_ch_0->setFrame(true);
        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 10, 121, 16));
        label_3->setFont(font);
        samrate_ch_1 = new QLineEdit(tab);
        samrate_ch_1->setObjectName(QString::fromUtf8("samrate_ch_1"));
        samrate_ch_1->setGeometry(QRect(50, 50, 61, 21));
        samrate_ch_2 = new QLineEdit(tab);
        samrate_ch_2->setObjectName(QString::fromUtf8("samrate_ch_2"));
        samrate_ch_2->setGeometry(QRect(50, 70, 61, 21));
        samrate_ch_3 = new QLineEdit(tab);
        samrate_ch_3->setObjectName(QString::fromUtf8("samrate_ch_3"));
        samrate_ch_3->setGeometry(QRect(50, 90, 61, 21));
        samrate_ch_4 = new QLineEdit(tab);
        samrate_ch_4->setObjectName(QString::fromUtf8("samrate_ch_4"));
        samrate_ch_4->setGeometry(QRect(50, 110, 61, 21));
        samrate_ch_5 = new QLineEdit(tab);
        samrate_ch_5->setObjectName(QString::fromUtf8("samrate_ch_5"));
        samrate_ch_5->setGeometry(QRect(50, 130, 61, 21));
        samrate_ch_6 = new QLineEdit(tab);
        samrate_ch_6->setObjectName(QString::fromUtf8("samrate_ch_6"));
        samrate_ch_6->setGeometry(QRect(50, 150, 61, 21));
        samrate_ch_7 = new QLineEdit(tab);
        samrate_ch_7->setObjectName(QString::fromUtf8("samrate_ch_7"));
        samrate_ch_7->setGeometry(QRect(50, 170, 61, 21));
        periodBox_ch_1 = new QComboBox(tab);
        periodBox_ch_1->setObjectName(QString::fromUtf8("periodBox_ch_1"));
        periodBox_ch_1->setGeometry(QRect(110, 50, 111, 21));
        periodBox_ch_1->setFrame(true);
        periodBox_ch_2 = new QComboBox(tab);
        periodBox_ch_2->setObjectName(QString::fromUtf8("periodBox_ch_2"));
        periodBox_ch_2->setGeometry(QRect(110, 70, 111, 21));
        periodBox_ch_2->setFrame(true);
        periodBox_ch_3 = new QComboBox(tab);
        periodBox_ch_3->setObjectName(QString::fromUtf8("periodBox_ch_3"));
        periodBox_ch_3->setGeometry(QRect(110, 90, 111, 21));
        periodBox_ch_3->setFrame(true);
        periodBox_ch_4 = new QComboBox(tab);
        periodBox_ch_4->setObjectName(QString::fromUtf8("periodBox_ch_4"));
        periodBox_ch_4->setGeometry(QRect(110, 110, 111, 21));
        periodBox_ch_4->setFrame(true);
        periodBox_ch_5 = new QComboBox(tab);
        periodBox_ch_5->setObjectName(QString::fromUtf8("periodBox_ch_5"));
        periodBox_ch_5->setGeometry(QRect(110, 130, 111, 21));
        periodBox_ch_5->setFrame(true);
        periodBox_ch_6 = new QComboBox(tab);
        periodBox_ch_6->setObjectName(QString::fromUtf8("periodBox_ch_6"));
        periodBox_ch_6->setGeometry(QRect(110, 150, 111, 21));
        periodBox_ch_6->setFrame(true);
        periodBox_ch_7 = new QComboBox(tab);
        periodBox_ch_7->setObjectName(QString::fromUtf8("periodBox_ch_7"));
        periodBox_ch_7->setGeometry(QRect(110, 170, 111, 21));
        periodBox_ch_7->setFrame(true);
        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 30, 31, 16));
        label_5 = new QLabel(tab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 50, 31, 16));
        label_6 = new QLabel(tab);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 70, 31, 16));
        label_7 = new QLabel(tab);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 90, 31, 16));
        label_8 = new QLabel(tab);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 110, 31, 16));
        label_9 = new QLabel(tab);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 130, 31, 16));
        label_10 = new QLabel(tab);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(20, 150, 31, 16));
        label_11 = new QLabel(tab);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(20, 170, 31, 16));
        TabDisplay->addTab(tab, QString());
        Start = new QPushButton(centralWidget);
        Start->setObjectName(QString::fromUtf8("Start"));
        Start->setGeometry(QRect(0, 270, 121, 21));
        QPalette palette;
        QBrush brush(QColor(0, 170, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        QBrush brush2(QColor(190, 190, 190, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        QBrush brush3(QColor(239, 235, 231, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        Start->setPalette(palette);
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        Start->setFont(font1);
        Start->setAutoFillBackground(true);
        Stop = new QPushButton(centralWidget);
        Stop->setObjectName(QString::fromUtf8("Stop"));
        Stop->setGeometry(QRect(120, 270, 121, 21));
        QPalette palette1;
        QBrush brush4(QColor(255, 0, 0, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        Stop->setPalette(palette1);
        Stop->setFont(font1);
        Stop->setCheckable(false);
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        TabDisplay->setCurrentIndex(2);
        periodBox_ch_0->setCurrentIndex(3);
        periodBox_ch_1->setCurrentIndex(3);
        periodBox_ch_2->setCurrentIndex(3);
        periodBox_ch_3->setCurrentIndex(3);
        periodBox_ch_4->setCurrentIndex(3);
        periodBox_ch_5->setCurrentIndex(3);
        periodBox_ch_6->setCurrentIndex(3);
        periodBox_ch_7->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Meazura", 0, QApplication::UnicodeUTF8));
        actionSave_Preferences->setText(QApplication::translate("MainWindow", "Save Preferences", 0, QApplication::UnicodeUTF8));
        actionOpen_Preferences->setText(QApplication::translate("MainWindow", "Open Preferences", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Set date and time", 0, QApplication::UnicodeUTF8));
        DeleteCSV->setText(QApplication::translate("MainWindow", "Delete logged data", 0, QApplication::UnicodeUTF8));
        TabDisplay->setTabText(TabDisplay->indexOf(tab_3), QApplication::translate("MainWindow", "Setup", 0, QApplication::UnicodeUTF8));
        select_ch_0->setText(QApplication::translate("MainWindow", "Ch0", 0, QApplication::UnicodeUTF8));
        select_ch_1->setText(QApplication::translate("MainWindow", "Ch1", 0, QApplication::UnicodeUTF8));
        select_ch_2->setText(QApplication::translate("MainWindow", "Ch2", 0, QApplication::UnicodeUTF8));
        select_ch_3->setText(QApplication::translate("MainWindow", "Ch3", 0, QApplication::UnicodeUTF8));
        select_ch_4->setText(QApplication::translate("MainWindow", "Ch4", 0, QApplication::UnicodeUTF8));
        select_ch_5->setText(QApplication::translate("MainWindow", "Ch5", 0, QApplication::UnicodeUTF8));
        select_ch_6->setText(QApplication::translate("MainWindow", "Ch6", 0, QApplication::UnicodeUTF8));
        select_ch_7->setText(QApplication::translate("MainWindow", "Ch7", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "Select", 0, QApplication::UnicodeUTF8));
        log_Ch_3->setText(QString());
        log_Ch_4->setText(QString());
        log_Ch_0->setText(QString());
        log_Ch_5->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Log", 0, QApplication::UnicodeUTF8));
        log_Ch_6->setText(QString());
        log_Ch_2->setText(QString());
        log_Ch_7->setText(QString());
        log_Ch_1->setText(QString());
        TabDisplay->setTabText(TabDisplay->indexOf(tab_2), QApplication::translate("MainWindow", "Channel", 0, QApplication::UnicodeUTF8));
        samrate_ch_0->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        periodBox_ch_0->clear();
        periodBox_ch_0->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "days", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "hours", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "minutes", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "seconds", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "miliseconds", 0, QApplication::UnicodeUTF8)
        );
        label_3->setText(QApplication::translate("MainWindow", "Sampling Period", 0, QApplication::UnicodeUTF8));
        samrate_ch_1->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        samrate_ch_2->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        samrate_ch_3->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        samrate_ch_4->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        samrate_ch_5->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        samrate_ch_6->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        samrate_ch_7->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        periodBox_ch_1->clear();
        periodBox_ch_1->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "days", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "hours", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "minutes", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "seconds", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "miliseconds", 0, QApplication::UnicodeUTF8)
        );
        periodBox_ch_2->clear();
        periodBox_ch_2->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "days", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "hours", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "minutes", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "seconds", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "miliseconds", 0, QApplication::UnicodeUTF8)
        );
        periodBox_ch_3->clear();
        periodBox_ch_3->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "days", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "hours", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "minutes", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "seconds", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "miliseconds", 0, QApplication::UnicodeUTF8)
        );
        periodBox_ch_4->clear();
        periodBox_ch_4->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "days", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "hours", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "minutes", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "seconds", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "miliseconds", 0, QApplication::UnicodeUTF8)
        );
        periodBox_ch_5->clear();
        periodBox_ch_5->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "days", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "hours", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "minutes", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "seconds", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "miliseconds", 0, QApplication::UnicodeUTF8)
        );
        periodBox_ch_6->clear();
        periodBox_ch_6->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "days", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "hours", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "minutes", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "seconds", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "miliseconds", 0, QApplication::UnicodeUTF8)
        );
        periodBox_ch_7->clear();
        periodBox_ch_7->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "days", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "hours", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "minutes", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "seconds", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "miliseconds", 0, QApplication::UnicodeUTF8)
        );
        label_4->setText(QApplication::translate("MainWindow", "Ch0", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Ch1", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Ch2", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Ch3", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Ch4", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Ch5", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "Ch6", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "Ch7", 0, QApplication::UnicodeUTF8));
        TabDisplay->setTabText(TabDisplay->indexOf(tab), QApplication::translate("MainWindow", "Period", 0, QApplication::UnicodeUTF8));
        Start->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        Stop->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
