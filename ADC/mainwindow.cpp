#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <QTimer>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "/opt/MEZ1500Rev2dLinux/Sources/linux-2.6.32.2/drivers/char/MEZ1500_mzio.h"
#include "/opt/MEZ1500Rev2dLinux/Sources/linux-2.6.32.2/drivers/char/MEZ1500_mzio_ltc185x.h"
#include <sys/time.h>
#include "adc1.h"
#include "keyboard/keyboard.h"

#define RESET_STATUS_TIMER  status_erase_count=5

// --------------------------------------------------------------------
// Internal Functions
// --------------------------------------------------------------------
// --------------------------------------------------------------------


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    int i;
    system("rmmod MEZ1500_mzio_ltc185x");
    system("modprobe MEZ1500_mzio_ltc185x");

    ui->setupUi(this);

    lineEditkeyboard = new Keyboard();
    connect(ui->ch0_samrate,SIGNAL(selectionChanged()),this,SLOT(run_keyboard_lineEdit()));

    count   = 0;
    fd_ltc185x = 0;
    fd_ltc185x = open("/dev/ltc185x", O_RDWR);
    if (fd_ltc185x < 0)
        printf("Failed to open MZIO LTC185x module\n");
    else
        printf("Openned MZIO LTC185x module\n");

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_timer_event()));
    timer->start(1000);

    RESET_STATUS_TIMER;

    // For now init all the sampling rate values to 1000us
    for (i=0; i<12; i++)
    {
        samrate_vals[i] = 1000000;
    }

    strBuf.sprintf("%lu", samrate_vals[0]);
    ui->ch0_samrate->setText(strBuf);
    strBuf.sprintf("%lu", samrate_vals[1]);
    ui->ch1_samrate->setText(strBuf);
    strBuf.sprintf("%lu", samrate_vals[2]);
    ui->ch2_samrate->setText(strBuf);
    strBuf.sprintf("%lu", samrate_vals[3]);
    ui->ch3_samrate->setText(strBuf);
    strBuf.sprintf("%lu", samrate_vals[4]);
    ui->ch4_samrate->setText(strBuf);
    strBuf.sprintf("%lu", samrate_vals[5]);
    ui->ch5_samrate->setText(strBuf);
    strBuf.sprintf("%lu", samrate_vals[6]);
    ui->ch6_samrate->setText(strBuf);
    strBuf.sprintf("%lu", samrate_vals[7]);
    ui->ch7_samrate->setText(strBuf);

    fflush(stdout);
}

MainWindow::~MainWindow()
{
    delete ui;
    // Unload the MZIO driver
    system("rmmod MEZ1500_mzio_ltc185x");

    ::close (fd_ltc185x);
}

void MainWindow::run_keyboard_lineEdit()
{
    QLineEdit *line = (QLineEdit *)sender();
    lineEditkeyboard->setLineEdit(line);
    lineEditkeyboard->show();
}


void MainWindow::on_Start_clicked()
{
    unsigned long   control;
    unsigned long   tempULong;
    QString         tempStr;
    int             err;

    if (fd_ltc185x)
    {
        // Init the ADC
        err = ioctl(fd_ltc185x, MZIO_LTC185x_INIT, 0);
        if (err<0) printf("Can't init the ADC\n");

        // Setup the channels
        if (ui->Ch0->isChecked())
        {
            control = LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain;
            printf("Ch0 setup 0x%lx", control);
            err = ioctl(fd_ltc185x, MZIO_LTC185x_CH0SE_SETUP, control);
            if (err<0) printf("Can't set Ch0 settings\n");

            tempStr = ui->ch0_samrate->text();
            tempULong = tempStr.toULong();
            err = ioctl(fd_ltc185x, MZIO_LTC185x_CH0SE_SET_PERIOD, tempULong);
            if (err<0) printf("Can't set Ch0 period\n");

        }

        if (ui->Ch1->isChecked())
        {
            control = LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain;
            printf("Ch1 setup 0x%lx", control);
            err = ioctl(fd_ltc185x, MZIO_LTC185x_CH1SE_SETUP, control);
            if (err<0) printf("Can't set Ch1 settings\n");

            tempStr = ui->ch1_samrate->text();
            tempULong = tempStr.toULong();
            err = ioctl(fd_ltc185x, MZIO_LTC185x_CH1SE_SET_PERIOD, tempULong);
            if (err<0) printf("Can't set Ch1 period\n");

        }

        if (ui->Ch2->isChecked())
        {
            control = LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain;
            printf("Ch2 setup 0x%lx", control);
            err = ioctl(fd_ltc185x, MZIO_LTC185x_CH2SE_SETUP, control);
            if (err<0) printf("Can't set Ch2 settings\n");

            tempStr = ui->ch2_samrate->text();
            tempULong = tempStr.toULong();
            err = ioctl(fd_ltc185x, MZIO_LTC185x_CH2SE_SET_PERIOD, tempULong);
            if (err<0) printf("Can't set Ch2 period\n");

        }

        if (ui->Ch3->isChecked())
        {
            control = LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain;
            printf("Ch3 setup 0x%lx", control);
            err = ioctl(fd_ltc185x, MZIO_LTC185x_CH3SE_SETUP, control);
            if (err<0) printf("Can't set Ch3 settings\n");

            tempStr = ui->ch3_samrate->text();
            tempULong = tempStr.toULong();
            err = ioctl(fd_ltc185x, MZIO_LTC185x_CH3SE_SET_PERIOD, tempULong);
            if (err<0) printf("Can't set Ch3 period\n");

        }

        if (ui->Ch4->isChecked())
        {
            control = LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain;
            printf("Ch4 setup 0x%lx", control);
            err = ioctl(fd_ltc185x, MZIO_LTC185x_CH4SE_SETUP, control);
            if (err<0) printf("Can't set Ch4 settings\n");

            tempStr = ui->ch4_samrate->text();
            tempULong = tempStr.toULong();
            err = ioctl(fd_ltc185x, MZIO_LTC185x_CH4SE_SET_PERIOD, tempULong);
            if (err<0) printf("Can't set Ch4 period\n");
        }

        if (ui->Ch5->isChecked())
        {
            control = LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain;
            printf("Ch5 setup 0x%lx", control);
            err = ioctl(fd_ltc185x, MZIO_LTC185x_CH5SE_SETUP, control);
            if (err<0) printf("Can't set Ch2 settings\n");

            tempStr = ui->ch5_samrate->text();
            tempULong = tempStr.toULong();
            err = ioctl(fd_ltc185x, MZIO_LTC185x_CH5SE_SET_PERIOD, tempULong);
            if (err<0) printf("Can't set Ch5 period\n");
        }

        if (ui->Ch6->isChecked())
        {
            control = LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain;
            printf("Ch6 setup 0x%lx", control);
            err = ioctl(fd_ltc185x, MZIO_LTC185x_CH6SE_SETUP, control);
            if (err<0) printf("Can't set Ch6 settings\n");

            tempStr = ui->ch6_samrate->text();
            tempULong = tempStr.toULong();
            err = ioctl(fd_ltc185x, MZIO_LTC185x_CH6SE_SET_PERIOD, tempULong);
            if (err<0) printf("Can't set Ch6 period\n");

        }

        if (ui->Ch7->isChecked())
        {
            control = LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain;
            printf("Ch7 setup 0x%lx", control);
            err = ioctl(fd_ltc185x, MZIO_LTC185x_CH7SE_SETUP, control);
            if (err<0) printf("Can't set Ch7 settings\n");

            tempStr = ui->ch7_samrate->text();
            tempULong = tempStr.toULong();
            err = ioctl(fd_ltc185x, MZIO_LTC185x_CH7SE_SET_PERIOD, tempULong);
            if (err<0) printf("Can't set Ch7 period\n");

        }


        // TODO: Get differentials processed here

        // Start sampling
        err = ioctl(fd_ltc185x, MZIO_LTC185x_START, 0);
        if (err<0) printf("Can't start ADC\n");
    }
    else
    {
        printf("LTC185x library failure");
    }

    fflush(stdout);
}

void MainWindow::on_Stop_clicked()
{
    int             err;

    if (fd_ltc185x)
    {
        // Stop sampling
        err = ioctl(fd_ltc185x, MZIO_LTC185x_STOP, 0);
        if (err<0) printf("Can't stop ADC\n");

        // Deinit the ADC
        err = ioctl(fd_ltc185x, MZIO_LTC185x_DEINIT, 0);
        if (err<0) printf("Can't deinit ADC\n");
    }
    else
    {
        printf("LTC185x library failure");
    }

    fflush(stdout);
}

void MainWindow::on_Ch0_clicked()
{
    strBuf.sprintf("Ch0 %s", (ui->Ch0->checkState()) ? "selected":"deselected");
    ui->status->setText(strBuf);
    RESET_STATUS_TIMER;
}

void MainWindow::on_Ch1_clicked()
{
    strBuf.sprintf("Ch1 %s", (ui->Ch1->checkState()) ? "selected":"deselected");
    ui->status->setText(strBuf);
    RESET_STATUS_TIMER;
}

void MainWindow::on_Ch2_clicked()
{
    strBuf.sprintf("Ch2 %s", (ui->Ch2->checkState()) ? "selected":"deselected");
    ui->status->setText(strBuf);
    RESET_STATUS_TIMER;
}

void MainWindow::on_Ch3_clicked()
{
    strBuf.sprintf("Ch3 %s", (ui->Ch3->checkState()) ? "selected":"deselected");
    ui->status->setText(strBuf);
    RESET_STATUS_TIMER;
}

void MainWindow::on_Ch4_clicked()
{
    strBuf.sprintf("Ch4 %s", (ui->Ch4->checkState()) ? "selected":"deselected");
    ui->status->setText(strBuf);
    RESET_STATUS_TIMER;
}

void MainWindow::on_Ch5_clicked()
{
    QString strBuf="";
    strBuf.sprintf("Ch0 %s", (ui->Ch0->checkState()) ? "selected":"deselected");
    ui->status->setText(strBuf);
    RESET_STATUS_TIMER;
}

void MainWindow::on_Ch6_clicked()
{
    strBuf.sprintf("Ch6 %s", (ui->Ch6->checkState()) ? "selected":"deselected");
    ui->status->setText(strBuf);
    RESET_STATUS_TIMER;
}


void MainWindow::on_Ch7_clicked()
{
    strBuf.sprintf("Ch7 %s", (ui->Ch7->checkState()) ? "selected":"deselected");
    ui->status->setText(strBuf);
    RESET_STATUS_TIMER;
}

void MainWindow::on_Ch01_clicked()
{
    strBuf.sprintf("Ch01 %s", (ui->Ch01->checkState()) ? "selected":"deselected");
    ui->status->setText(strBuf);
    RESET_STATUS_TIMER;
}

void MainWindow::on_Ch23_clicked()
{
    strBuf.sprintf("Ch23 %s", (ui->Ch23->checkState()) ? "selected":"deselected");
    ui->status->setText(strBuf);
    RESET_STATUS_TIMER;
}

void MainWindow::on_Ch45_clicked()
{
    QString strBuf="";
    strBuf.sprintf("Ch45 %s", (ui->Ch45->checkState()) ? "selected":"deselected");
    ui->status->setText(strBuf);
    RESET_STATUS_TIMER;
}

void MainWindow::on_Ch67_clicked()
{
    QString strBuf="";
    strBuf.sprintf("Ch67 %s", (ui->Ch67->checkState()) ? "selected":"deselected");
    ui->status->setText(strBuf);
    RESET_STATUS_TIMER;
}

void MainWindow::on_Ch0_samrate_valueChanged(int arg1)
{
//    QString strBuf="";
  //  strBuf.sprintf("Ch0 sample rate %d", arg1);
   // ui->status->setText(strBuf);
    RESET_STATUS_TIMER;
}

void MainWindow::on_timer_event()
{
    if (status_erase_count-- <=0)
    {
        strBuf.sprintf("");
        ui->status->setText(strBuf);
        RESET_STATUS_TIMER;
    }

    printf(".");
    fflush(stdout);
}

//void MainWindow::on_up_clicked()
void MainWindow::on_up_pressed()
{
    int chSelected;

    if (ui->ch0_radio->isChecked())         chSelected=0;
    else if (ui->ch1_radio->isChecked())    chSelected=1;
    else if (ui->ch2_radio->isChecked())    chSelected=2;
    else if (ui->ch3_radio->isChecked())    chSelected=3;
    else if (ui->ch4_radio->isChecked())    chSelected=4;
    else if (ui->ch5_radio->isChecked())    chSelected=5;
    else if (ui->ch6_radio->isChecked())    chSelected=6;
    else if (ui->ch7_radio->isChecked())    chSelected=7;

    samrate_vals[chSelected]+=10;
    strBuf.sprintf("Ch%d sampling %lu usec", chSelected, samrate_vals[chSelected]);
    ui->status->setText(strBuf);

    strBuf.sprintf("%lu", samrate_vals[chSelected]);
    switch (chSelected)
    {
    case 0:
        ui->ch0_samrate->setText(strBuf);
        break;
    case 1:
        ui->ch1_samrate->setText(strBuf);
        break;
    case 2:
        ui->ch2_samrate->setText(strBuf);
        break;
    case 3:
        ui->ch3_samrate->setText(strBuf);
        break;
    case 4:
        ui->ch4_samrate->setText(strBuf);
        break;
    case 5:
        ui->ch5_samrate->setText(strBuf);
        break;
    case 6:
        ui->ch6_samrate->setText(strBuf);
        break;
    case 7:
        ui->ch7_samrate->setText(strBuf);
        break;
    }

    RESET_STATUS_TIMER;
}

void MainWindow::on_down_clicked()
{
    int chSelected;

    if (ui->ch0_radio->isChecked())         chSelected=0;
    else if (ui->ch1_radio->isChecked())    chSelected=1;
    else if (ui->ch2_radio->isChecked())    chSelected=2;
    else if (ui->ch3_radio->isChecked())    chSelected=3;
    else if (ui->ch4_radio->isChecked())    chSelected=4;
    else if (ui->ch5_radio->isChecked())    chSelected=5;
    else if (ui->ch6_radio->isChecked())    chSelected=6;
    else if (ui->ch7_radio->isChecked())    chSelected=7;

    samrate_vals[chSelected]-= 10;
    strBuf.sprintf("Ch%d sampling %lu usec", chSelected, samrate_vals[chSelected]);
    ui->status->setText(strBuf);

    strBuf.sprintf("%lu", samrate_vals[chSelected]);
    switch (chSelected)
    {
    case 0:
        ui->ch0_samrate->setText(strBuf);
        break;
    case 1:
        ui->ch1_samrate->setText(strBuf);
        break;
    case 2:
        ui->ch2_samrate->setText(strBuf);
        break;
    case 3:
        ui->ch3_samrate->setText(strBuf);
        break;
    case 4:
        ui->ch4_samrate->setText(strBuf);
        break;
    case 5:
        ui->ch5_samrate->setText(strBuf);
        break;
    case 6:
        ui->ch6_samrate->setText(strBuf);
        break;
    case 7:
        ui->ch7_samrate->setText(strBuf);
        break;
    }

    RESET_STATUS_TIMER;
}

