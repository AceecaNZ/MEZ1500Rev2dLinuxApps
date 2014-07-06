/********************************************************************************
** Form generated from reading UI file 'keyboard.ui'
**
** Created: Wed Jun 25 16:08:12 2014
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEYBOARD_H
#define UI_KEYBOARD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Keyboard
{
public:
    QLineEdit *lineEdit;
    QPushButton *backButton;
    QPushButton *Buttonl;
    QPushButton *Buttonn;
    QPushButton *Buttonh;
    QPushButton *Buttonw;
    QPushButton *enterButton;
    QPushButton *char_2;
    QPushButton *Buttonc;
    QPushButton *space;
    QPushButton *Button8;
    QPushButton *Button5;
    QPushButton *Buttonu;
    QPushButton *Buttonx;
    QPushButton *Buttonb;
    QPushButton *Buttone;
    QPushButton *Buttonr;
    QPushButton *Buttonj;
    QPushButton *Buttoni;
    QPushButton *Buttonp;
    QPushButton *Buttonm;
    QPushButton *Buttons;
    QPushButton *Button6;
    QPushButton *Buttont;
    QPushButton *Buttona;
    QPushButton *Buttonv;
    QPushButton *Buttono;
    QPushButton *Button9;
    QPushButton *Button4;
    QPushButton *Buttong;
    QPushButton *Buttonq;
    QPushButton *Button7;
    QPushButton *shift;
    QPushButton *Buttonz;
    QPushButton *Buttonk;
    QPushButton *Buttonf;
    QPushButton *Button1;
    QPushButton *Buttony;
    QPushButton *Buttond;
    QPushButton *Button0;
    QPushButton *Button2;
    QPushButton *Button3;
    QPushButton *clear;

    void setupUi(QWidget *Keyboard)
    {
        if (Keyboard->objectName().isEmpty())
            Keyboard->setObjectName(QString::fromUtf8("Keyboard"));
        Keyboard->setWindowModality(Qt::NonModal);
        Keyboard->resize(210, 160);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Keyboard->sizePolicy().hasHeightForWidth());
        Keyboard->setSizePolicy(sizePolicy);
        Keyboard->setWindowTitle(QString::fromUtf8("Keyboard"));
        Keyboard->setWindowOpacity(1);
        Keyboard->setStyleSheet(QString::fromUtf8(""));
        lineEdit = new QLineEdit(Keyboard);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(0, 10, 151, 23));
        lineEdit->setMaximumSize(QSize(240, 320));
        lineEdit->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        backButton = new QPushButton(Keyboard);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setGeometry(QRect(152, 10, 27, 23));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(backButton->sizePolicy().hasHeightForWidth());
        backButton->setSizePolicy(sizePolicy1);
        Buttonl = new QPushButton(Keyboard);
        Buttonl->setObjectName(QString::fromUtf8("Buttonl"));
        Buttonl->setGeometry(QRect(167, 84, 21, 23));
        sizePolicy1.setHeightForWidth(Buttonl->sizePolicy().hasHeightForWidth());
        Buttonl->setSizePolicy(sizePolicy1);
        Buttonl->setMinimumSize(QSize(20, 0));
        Buttonn = new QPushButton(Keyboard);
        Buttonn->setObjectName(QString::fromUtf8("Buttonn"));
        Buttonn->setGeometry(QRect(99, 106, 21, 23));
        sizePolicy1.setHeightForWidth(Buttonn->sizePolicy().hasHeightForWidth());
        Buttonn->setSizePolicy(sizePolicy1);
        Buttonn->setMinimumSize(QSize(20, 0));
        Buttonh = new QPushButton(Keyboard);
        Buttonh->setObjectName(QString::fromUtf8("Buttonh"));
        Buttonh->setGeometry(QRect(104, 84, 21, 23));
        sizePolicy1.setHeightForWidth(Buttonh->sizePolicy().hasHeightForWidth());
        Buttonh->setSizePolicy(sizePolicy1);
        Buttonh->setMinimumSize(QSize(20, 0));
        Buttonw = new QPushButton(Keyboard);
        Buttonw->setObjectName(QString::fromUtf8("Buttonw"));
        Buttonw->setGeometry(QRect(20, 62, 21, 23));
        sizePolicy1.setHeightForWidth(Buttonw->sizePolicy().hasHeightForWidth());
        Buttonw->setSizePolicy(sizePolicy1);
        Buttonw->setMinimumSize(QSize(20, 0));
        enterButton = new QPushButton(Keyboard);
        enterButton->setObjectName(QString::fromUtf8("enterButton"));
        enterButton->setGeometry(QRect(138, 106, 71, 23));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(enterButton->sizePolicy().hasHeightForWidth());
        enterButton->setSizePolicy(sizePolicy2);
        enterButton->setMinimumSize(QSize(0, 0));
        enterButton->setMaximumSize(QSize(1000, 1000));
        char_2 = new QPushButton(Keyboard);
        char_2->setObjectName(QString::fromUtf8("char_2"));
        char_2->setGeometry(QRect(148, 132, 61, 23));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(char_2->sizePolicy().hasHeightForWidth());
        char_2->setSizePolicy(sizePolicy3);
        char_2->setMinimumSize(QSize(0, 0));
        char_2->setCheckable(true);
        char_2->setChecked(false);
        Buttonc = new QPushButton(Keyboard);
        Buttonc->setObjectName(QString::fromUtf8("Buttonc"));
        Buttonc->setGeometry(QRect(38, 106, 21, 23));
        sizePolicy1.setHeightForWidth(Buttonc->sizePolicy().hasHeightForWidth());
        Buttonc->setSizePolicy(sizePolicy1);
        Buttonc->setMinimumSize(QSize(20, 0));
        space = new QPushButton(Keyboard);
        space->setObjectName(QString::fromUtf8("space"));
        space->setGeometry(QRect(42, 132, 107, 23));
        sizePolicy1.setHeightForWidth(space->sizePolicy().hasHeightForWidth());
        space->setSizePolicy(sizePolicy1);
        space->setMinimumSize(QSize(20, 10));
        Button8 = new QPushButton(Keyboard);
        Button8->setObjectName(QString::fromUtf8("Button8"));
        Button8->setGeometry(QRect(167, 40, 21, 23));
        sizePolicy1.setHeightForWidth(Button8->sizePolicy().hasHeightForWidth());
        Button8->setSizePolicy(sizePolicy1);
        Button8->setMinimumSize(QSize(20, 0));
        Button5 = new QPushButton(Keyboard);
        Button5->setObjectName(QString::fromUtf8("Button5"));
        Button5->setGeometry(QRect(104, 40, 21, 23));
        sizePolicy1.setHeightForWidth(Button5->sizePolicy().hasHeightForWidth());
        Button5->setSizePolicy(sizePolicy1);
        Button5->setMinimumSize(QSize(20, 0));
        Buttonu = new QPushButton(Keyboard);
        Buttonu->setObjectName(QString::fromUtf8("Buttonu"));
        Buttonu->setGeometry(QRect(125, 62, 21, 23));
        sizePolicy1.setHeightForWidth(Buttonu->sizePolicy().hasHeightForWidth());
        Buttonu->setSizePolicy(sizePolicy1);
        Buttonu->setMinimumSize(QSize(20, 0));
        Buttonx = new QPushButton(Keyboard);
        Buttonx->setObjectName(QString::fromUtf8("Buttonx"));
        Buttonx->setGeometry(QRect(19, 106, 21, 23));
        sizePolicy1.setHeightForWidth(Buttonx->sizePolicy().hasHeightForWidth());
        Buttonx->setSizePolicy(sizePolicy1);
        Buttonx->setMinimumSize(QSize(20, 0));
        Buttonb = new QPushButton(Keyboard);
        Buttonb->setObjectName(QString::fromUtf8("Buttonb"));
        Buttonb->setGeometry(QRect(78, 106, 21, 23));
        sizePolicy1.setHeightForWidth(Buttonb->sizePolicy().hasHeightForWidth());
        Buttonb->setSizePolicy(sizePolicy1);
        Buttonb->setMinimumSize(QSize(20, 0));
        Buttone = new QPushButton(Keyboard);
        Buttone->setObjectName(QString::fromUtf8("Buttone"));
        Buttone->setGeometry(QRect(41, 62, 21, 23));
        sizePolicy1.setHeightForWidth(Buttone->sizePolicy().hasHeightForWidth());
        Buttone->setSizePolicy(sizePolicy1);
        Buttone->setMinimumSize(QSize(20, 0));
        Buttonr = new QPushButton(Keyboard);
        Buttonr->setObjectName(QString::fromUtf8("Buttonr"));
        Buttonr->setGeometry(QRect(62, 62, 21, 23));
        sizePolicy1.setHeightForWidth(Buttonr->sizePolicy().hasHeightForWidth());
        Buttonr->setSizePolicy(sizePolicy1);
        Buttonr->setMinimumSize(QSize(20, 0));
        Buttonj = new QPushButton(Keyboard);
        Buttonj->setObjectName(QString::fromUtf8("Buttonj"));
        Buttonj->setGeometry(QRect(125, 84, 21, 23));
        sizePolicy1.setHeightForWidth(Buttonj->sizePolicy().hasHeightForWidth());
        Buttonj->setSizePolicy(sizePolicy1);
        Buttonj->setMinimumSize(QSize(20, 0));
        Buttoni = new QPushButton(Keyboard);
        Buttoni->setObjectName(QString::fromUtf8("Buttoni"));
        Buttoni->setGeometry(QRect(146, 62, 21, 23));
        sizePolicy1.setHeightForWidth(Buttoni->sizePolicy().hasHeightForWidth());
        Buttoni->setSizePolicy(sizePolicy1);
        Buttoni->setMinimumSize(QSize(20, 0));
        Buttonp = new QPushButton(Keyboard);
        Buttonp->setObjectName(QString::fromUtf8("Buttonp"));
        Buttonp->setGeometry(QRect(188, 62, 21, 23));
        sizePolicy1.setHeightForWidth(Buttonp->sizePolicy().hasHeightForWidth());
        Buttonp->setSizePolicy(sizePolicy1);
        Buttonp->setMinimumSize(QSize(20, 0));
        Buttonm = new QPushButton(Keyboard);
        Buttonm->setObjectName(QString::fromUtf8("Buttonm"));
        Buttonm->setGeometry(QRect(118, 106, 21, 23));
        sizePolicy1.setHeightForWidth(Buttonm->sizePolicy().hasHeightForWidth());
        Buttonm->setSizePolicy(sizePolicy1);
        Buttonm->setMinimumSize(QSize(20, 0));
        Buttons = new QPushButton(Keyboard);
        Buttons->setObjectName(QString::fromUtf8("Buttons"));
        Buttons->setGeometry(QRect(20, 84, 21, 23));
        sizePolicy1.setHeightForWidth(Buttons->sizePolicy().hasHeightForWidth());
        Buttons->setSizePolicy(sizePolicy1);
        Buttons->setMinimumSize(QSize(20, 0));
        Button6 = new QPushButton(Keyboard);
        Button6->setObjectName(QString::fromUtf8("Button6"));
        Button6->setGeometry(QRect(125, 40, 21, 23));
        sizePolicy1.setHeightForWidth(Button6->sizePolicy().hasHeightForWidth());
        Button6->setSizePolicy(sizePolicy1);
        Button6->setMinimumSize(QSize(20, 0));
        Buttont = new QPushButton(Keyboard);
        Buttont->setObjectName(QString::fromUtf8("Buttont"));
        Buttont->setGeometry(QRect(83, 62, 21, 23));
        sizePolicy1.setHeightForWidth(Buttont->sizePolicy().hasHeightForWidth());
        Buttont->setSizePolicy(sizePolicy1);
        Buttont->setMinimumSize(QSize(20, 0));
        Buttona = new QPushButton(Keyboard);
        Buttona->setObjectName(QString::fromUtf8("Buttona"));
        Buttona->setGeometry(QRect(0, 84, 21, 23));
        sizePolicy1.setHeightForWidth(Buttona->sizePolicy().hasHeightForWidth());
        Buttona->setSizePolicy(sizePolicy1);
        Buttona->setMinimumSize(QSize(20, 0));
        Buttonv = new QPushButton(Keyboard);
        Buttonv->setObjectName(QString::fromUtf8("Buttonv"));
        Buttonv->setGeometry(QRect(58, 106, 21, 23));
        sizePolicy1.setHeightForWidth(Buttonv->sizePolicy().hasHeightForWidth());
        Buttonv->setSizePolicy(sizePolicy1);
        Buttonv->setMinimumSize(QSize(20, 0));
        Buttono = new QPushButton(Keyboard);
        Buttono->setObjectName(QString::fromUtf8("Buttono"));
        Buttono->setGeometry(QRect(167, 62, 21, 23));
        sizePolicy1.setHeightForWidth(Buttono->sizePolicy().hasHeightForWidth());
        Buttono->setSizePolicy(sizePolicy1);
        Buttono->setMinimumSize(QSize(20, 0));
        Button9 = new QPushButton(Keyboard);
        Button9->setObjectName(QString::fromUtf8("Button9"));
        Button9->setGeometry(QRect(188, 40, 21, 23));
        sizePolicy1.setHeightForWidth(Button9->sizePolicy().hasHeightForWidth());
        Button9->setSizePolicy(sizePolicy1);
        Button9->setMinimumSize(QSize(10, 0));
        Button4 = new QPushButton(Keyboard);
        Button4->setObjectName(QString::fromUtf8("Button4"));
        Button4->setGeometry(QRect(83, 40, 21, 23));
        sizePolicy1.setHeightForWidth(Button4->sizePolicy().hasHeightForWidth());
        Button4->setSizePolicy(sizePolicy1);
        Button4->setMinimumSize(QSize(20, 0));
        Buttong = new QPushButton(Keyboard);
        Buttong->setObjectName(QString::fromUtf8("Buttong"));
        Buttong->setGeometry(QRect(83, 84, 21, 23));
        sizePolicy1.setHeightForWidth(Buttong->sizePolicy().hasHeightForWidth());
        Buttong->setSizePolicy(sizePolicy1);
        Buttong->setMinimumSize(QSize(20, 0));
        Buttonq = new QPushButton(Keyboard);
        Buttonq->setObjectName(QString::fromUtf8("Buttonq"));
        Buttonq->setGeometry(QRect(0, 62, 21, 23));
        sizePolicy1.setHeightForWidth(Buttonq->sizePolicy().hasHeightForWidth());
        Buttonq->setSizePolicy(sizePolicy1);
        Buttonq->setMinimumSize(QSize(20, 0));
        Button7 = new QPushButton(Keyboard);
        Button7->setObjectName(QString::fromUtf8("Button7"));
        Button7->setGeometry(QRect(146, 40, 21, 23));
        sizePolicy1.setHeightForWidth(Button7->sizePolicy().hasHeightForWidth());
        Button7->setSizePolicy(sizePolicy1);
        Button7->setMinimumSize(QSize(20, 0));
        shift = new QPushButton(Keyboard);
        shift->setObjectName(QString::fromUtf8("shift"));
        shift->setGeometry(QRect(0, 132, 43, 23));
        sizePolicy3.setHeightForWidth(shift->sizePolicy().hasHeightForWidth());
        shift->setSizePolicy(sizePolicy3);
        shift->setMinimumSize(QSize(20, 0));
        shift->setStyleSheet(QString::fromUtf8(""));
        shift->setCheckable(false);
        Buttonz = new QPushButton(Keyboard);
        Buttonz->setObjectName(QString::fromUtf8("Buttonz"));
        Buttonz->setGeometry(QRect(0, 106, 21, 23));
        sizePolicy1.setHeightForWidth(Buttonz->sizePolicy().hasHeightForWidth());
        Buttonz->setSizePolicy(sizePolicy1);
        Buttonz->setMinimumSize(QSize(20, 0));
        Buttonk = new QPushButton(Keyboard);
        Buttonk->setObjectName(QString::fromUtf8("Buttonk"));
        Buttonk->setGeometry(QRect(146, 84, 21, 23));
        sizePolicy1.setHeightForWidth(Buttonk->sizePolicy().hasHeightForWidth());
        Buttonk->setSizePolicy(sizePolicy1);
        Buttonk->setMinimumSize(QSize(20, 0));
        Buttonf = new QPushButton(Keyboard);
        Buttonf->setObjectName(QString::fromUtf8("Buttonf"));
        Buttonf->setGeometry(QRect(62, 84, 21, 23));
        sizePolicy1.setHeightForWidth(Buttonf->sizePolicy().hasHeightForWidth());
        Buttonf->setSizePolicy(sizePolicy1);
        Buttonf->setMinimumSize(QSize(20, 0));
        Button1 = new QPushButton(Keyboard);
        Button1->setObjectName(QString::fromUtf8("Button1"));
        Button1->setGeometry(QRect(20, 40, 21, 23));
        sizePolicy1.setHeightForWidth(Button1->sizePolicy().hasHeightForWidth());
        Button1->setSizePolicy(sizePolicy1);
        Button1->setMinimumSize(QSize(20, 0));
        Buttony = new QPushButton(Keyboard);
        Buttony->setObjectName(QString::fromUtf8("Buttony"));
        Buttony->setGeometry(QRect(104, 62, 21, 23));
        sizePolicy1.setHeightForWidth(Buttony->sizePolicy().hasHeightForWidth());
        Buttony->setSizePolicy(sizePolicy1);
        Buttony->setMinimumSize(QSize(20, 0));
        Buttond = new QPushButton(Keyboard);
        Buttond->setObjectName(QString::fromUtf8("Buttond"));
        Buttond->setGeometry(QRect(41, 84, 21, 23));
        sizePolicy1.setHeightForWidth(Buttond->sizePolicy().hasHeightForWidth());
        Buttond->setSizePolicy(sizePolicy1);
        Buttond->setMinimumSize(QSize(20, 0));
        Button0 = new QPushButton(Keyboard);
        Button0->setObjectName(QString::fromUtf8("Button0"));
        Button0->setEnabled(true);
        Button0->setGeometry(QRect(0, 40, 21, 23));
        sizePolicy1.setHeightForWidth(Button0->sizePolicy().hasHeightForWidth());
        Button0->setSizePolicy(sizePolicy1);
        Button0->setMinimumSize(QSize(10, 0));
        Button0->setMaximumSize(QSize(1000, 1000));
        Button0->setIconSize(QSize(10, 10));
        Button2 = new QPushButton(Keyboard);
        Button2->setObjectName(QString::fromUtf8("Button2"));
        Button2->setGeometry(QRect(41, 40, 21, 23));
        sizePolicy1.setHeightForWidth(Button2->sizePolicy().hasHeightForWidth());
        Button2->setSizePolicy(sizePolicy1);
        Button2->setMinimumSize(QSize(20, 0));
        Button3 = new QPushButton(Keyboard);
        Button3->setObjectName(QString::fromUtf8("Button3"));
        Button3->setGeometry(QRect(62, 40, 21, 23));
        sizePolicy1.setHeightForWidth(Button3->sizePolicy().hasHeightForWidth());
        Button3->setSizePolicy(sizePolicy1);
        Button3->setMinimumSize(QSize(20, 0));
        clear = new QPushButton(Keyboard);
        clear->setObjectName(QString::fromUtf8("clear"));
        clear->setGeometry(QRect(180, 10, 30, 23));
        sizePolicy1.setHeightForWidth(clear->sizePolicy().hasHeightForWidth());
        clear->setSizePolicy(sizePolicy1);

        retranslateUi(Keyboard);

        QMetaObject::connectSlotsByName(Keyboard);
    } // setupUi

    void retranslateUi(QWidget *Keyboard)
    {
        backButton->setText(QApplication::translate("Keyboard", "<-", 0, QApplication::UnicodeUTF8));
        Buttonl->setText(QApplication::translate("Keyboard", "l", 0, QApplication::UnicodeUTF8));
        Buttonn->setText(QApplication::translate("Keyboard", "n", 0, QApplication::UnicodeUTF8));
        Buttonh->setText(QApplication::translate("Keyboard", "h", 0, QApplication::UnicodeUTF8));
        Buttonw->setText(QApplication::translate("Keyboard", "w", 0, QApplication::UnicodeUTF8));
        enterButton->setText(QApplication::translate("Keyboard", "Enter", 0, QApplication::UnicodeUTF8));
        char_2->setText(QApplication::translate("Keyboard", "Char", 0, QApplication::UnicodeUTF8));
        Buttonc->setText(QApplication::translate("Keyboard", "c", 0, QApplication::UnicodeUTF8));
        space->setText(QApplication::translate("Keyboard", "Space", 0, QApplication::UnicodeUTF8));
        Button8->setText(QApplication::translate("Keyboard", "8", 0, QApplication::UnicodeUTF8));
        Button5->setText(QApplication::translate("Keyboard", "5", 0, QApplication::UnicodeUTF8));
        Buttonu->setText(QApplication::translate("Keyboard", "u", 0, QApplication::UnicodeUTF8));
        Buttonx->setText(QApplication::translate("Keyboard", "x", 0, QApplication::UnicodeUTF8));
        Buttonb->setText(QApplication::translate("Keyboard", "b", 0, QApplication::UnicodeUTF8));
        Buttone->setText(QApplication::translate("Keyboard", "e", 0, QApplication::UnicodeUTF8));
        Buttonr->setText(QApplication::translate("Keyboard", "r", 0, QApplication::UnicodeUTF8));
        Buttonj->setText(QApplication::translate("Keyboard", "j", 0, QApplication::UnicodeUTF8));
        Buttoni->setText(QApplication::translate("Keyboard", "i", 0, QApplication::UnicodeUTF8));
        Buttonp->setText(QApplication::translate("Keyboard", "p", 0, QApplication::UnicodeUTF8));
        Buttonm->setText(QApplication::translate("Keyboard", "m", 0, QApplication::UnicodeUTF8));
        Buttons->setText(QApplication::translate("Keyboard", "s", 0, QApplication::UnicodeUTF8));
        Button6->setText(QApplication::translate("Keyboard", "6", 0, QApplication::UnicodeUTF8));
        Buttont->setText(QApplication::translate("Keyboard", "t", 0, QApplication::UnicodeUTF8));
        Buttona->setText(QApplication::translate("Keyboard", "a", 0, QApplication::UnicodeUTF8));
        Buttonv->setText(QApplication::translate("Keyboard", "v", 0, QApplication::UnicodeUTF8));
        Buttono->setText(QApplication::translate("Keyboard", "o", 0, QApplication::UnicodeUTF8));
        Button9->setText(QApplication::translate("Keyboard", "9", 0, QApplication::UnicodeUTF8));
        Button4->setText(QApplication::translate("Keyboard", "4", 0, QApplication::UnicodeUTF8));
        Buttong->setText(QApplication::translate("Keyboard", "g", 0, QApplication::UnicodeUTF8));
        Buttonq->setText(QApplication::translate("Keyboard", "q", 0, QApplication::UnicodeUTF8));
        Button7->setText(QApplication::translate("Keyboard", "7", 0, QApplication::UnicodeUTF8));
        shift->setText(QApplication::translate("Keyboard", "Shift", 0, QApplication::UnicodeUTF8));
        Buttonz->setText(QApplication::translate("Keyboard", "z", 0, QApplication::UnicodeUTF8));
        Buttonk->setText(QApplication::translate("Keyboard", "k", 0, QApplication::UnicodeUTF8));
        Buttonf->setText(QApplication::translate("Keyboard", "f", 0, QApplication::UnicodeUTF8));
        Button1->setText(QApplication::translate("Keyboard", "1", 0, QApplication::UnicodeUTF8));
        Buttony->setText(QApplication::translate("Keyboard", "y", 0, QApplication::UnicodeUTF8));
        Buttond->setText(QApplication::translate("Keyboard", "d", 0, QApplication::UnicodeUTF8));
        Button0->setText(QApplication::translate("Keyboard", "0", 0, QApplication::UnicodeUTF8));
        Button2->setText(QApplication::translate("Keyboard", "2", 0, QApplication::UnicodeUTF8));
        Button3->setText(QApplication::translate("Keyboard", "3", 0, QApplication::UnicodeUTF8));
        clear->setText(QApplication::translate("Keyboard", "Clr", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(Keyboard);
    } // retranslateUi

};

namespace Ui {
    class Keyboard: public Ui_Keyboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYBOARD_H
