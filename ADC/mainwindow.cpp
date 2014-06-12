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

#define TIMER_PERIOD            1                           // msecs
#define RESET_STATUS_TIMER      status_erase_count=5000     // 5s
#define RESET_READ_TIMER        sample_timer_count=100      // 100ms

// --------------------------------------------------------------------
// Internal Functions
// --------------------------------------------------------------------
// --------------------------------------------------------------------


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    int i;

    // Allocate sampling buffers
    RdBuf = (BufData*)malloc(sizeof(BufData));
    if (!RdBuf)
    {
        printf("Error allocating Ch0Buf\n");
        return;
    }
    else
    {
        printf("Allocated RdBuf\n");
        memset(RdBuf, 0, sizeof(BufData));
    }

    system("rmmod MEZ1500_mzio_ltc185x");
    system("modprobe MEZ1500_mzio_ltc185x");

    ui->setupUi(this);

    lineEditkeyboard = new Keyboard();
    connect(ui->ch0_samrate,SIGNAL(selectionChanged()),this,SLOT(run_keyboard_lineEdit()));

    count   = 0;
    isSampling = 0;
    fd_ltc185x = 0;
    fd_ltc185x = open("/dev/ltc185x", O_RDWR);
    if (fd_ltc185x < 0)
        printf("Failed to open MZIO LTC185x module\n");
    else
        printf("Openned MZIO LTC185x module\n");

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_timer_event()));
    timer->start(TIMER_PERIOD);

    RESET_STATUS_TIMER;

    // For now init all the sampling rate values to 1000us
    for (i=0; i<12; i++)
        samrate_vals[i] = 1000000;

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

    if (RdBuf) free(RdBuf);

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
    int             startSampling=0;

    if (fd_ltc185x)
    {
        // Init the ADC
        err = ioctl(fd_ltc185x, MZIO_LTC185x_DEINIT, 0); // incorporates a sampling STOP
        err = ioctl(fd_ltc185x, MZIO_LTC185x_INIT, 0);
        if (err<0) printf("Can't init the ADC\n");

        // Setup the channels
        if (ui->Ch01->isChecked())
        {
            startSampling++;
            control = LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain;
            printf("Ch01 setup 0x%lx", control);
            err = ioctl(fd_ltc185x, MZIO_LTC185x_CH01DE_SETUP, control);
            if (err<0) printf("Can't set Ch7 settings\n");

            tempStr = ui->ch0_samrate->text();
            tempULong = tempStr.toULong();
            err = ioctl(fd_ltc185x, MZIO_LTC185x_CH01DE_SET_PERIOD, tempULong);
            if (err<0) printf("Can't set Ch7 period\n");

            // Uncheck Ch0 and Ch1
            ui->Ch0->setChecked(0);
            ui->Ch1->setChecked(0);
        }
        else
        {
            if (ui->Ch0->isChecked())
            {
                startSampling++;
                control = LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain;
                printf("Ch0 setup 0x%lx\n", control);
                err = ioctl(fd_ltc185x, MZIO_LTC185x_CH0SE_SETUP, control);
                if (err<0) printf("Can't set Ch0 settings\n");

                tempStr = ui->ch0_samrate->text();
                tempULong = tempStr.toULong();
                err = ioctl(fd_ltc185x, MZIO_LTC185x_CH0SE_SET_PERIOD, tempULong);
                if (err<0) printf("Can't set Ch0 period\n");
            }

            if (ui->Ch1->isChecked())
            {
                startSampling++;
                control = LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain;
                printf("Ch1 setup 0x%lx", control);
                err = ioctl(fd_ltc185x, MZIO_LTC185x_CH1SE_SETUP, control);
                if (err<0) printf("Can't set Ch1 settings\n");

                tempStr = ui->ch1_samrate->text();
                tempULong = tempStr.toULong();
                err = ioctl(fd_ltc185x, MZIO_LTC185x_CH1SE_SET_PERIOD, tempULong);
                if (err<0) printf("Can't set Ch1 period\n");

            }
        }


        if (ui->Ch23->isChecked())
        {
            startSampling++;
            control = LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain;
            printf("Ch23 setup 0x%lx", control);
            err = ioctl(fd_ltc185x, MZIO_LTC185x_CH23DE_SETUP, control);
            if (err<0) printf("Can't set Ch23 settings\n");

            tempStr = ui->ch2_samrate->text();
            tempULong = tempStr.toULong();
            err = ioctl(fd_ltc185x, MZIO_LTC185x_CH23DE_SET_PERIOD, tempULong);
            if (err<0) printf("Can't set Ch23 period\n");

            // Uncheck Ch0 and Ch1
            ui->Ch2->setChecked(0);
            ui->Ch3->setChecked(0);
        }
        else
        {
            if (ui->Ch2->isChecked())
            {
                startSampling++;
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
                startSampling++;
                control = LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain;
                printf("Ch3 setup 0x%lx", control);
                err = ioctl(fd_ltc185x, MZIO_LTC185x_CH3SE_SETUP, control);
                if (err<0) printf("Can't set Ch3 settings\n");

                tempStr = ui->ch3_samrate->text();
                tempULong = tempStr.toULong();
                err = ioctl(fd_ltc185x, MZIO_LTC185x_CH3SE_SET_PERIOD, tempULong);
                if (err<0) printf("Can't set Ch3 period\n");

            }
        }

        if (ui->Ch45->isChecked())
        {
            startSampling++;
            control = LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain;
            printf("Ch45 setup 0x%lx", control);
            err = ioctl(fd_ltc185x, MZIO_LTC185x_CH45DE_SETUP, control);
            if (err<0) printf("Can't set Ch45 settings\n");

            tempStr = ui->ch2_samrate->text();
            tempULong = tempStr.toULong();
            err = ioctl(fd_ltc185x, MZIO_LTC185x_CH45DE_SET_PERIOD, tempULong);
            if (err<0) printf("Can't set Ch45 period\n");

            // Uncheck Ch0 and Ch1
            ui->Ch4->setChecked(0);
            ui->Ch5->setChecked(0);
        }
        else
        {
            if (ui->Ch4->isChecked())
            {
                startSampling++;
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
                startSampling++;
                control = LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain;
                printf("Ch5 setup 0x%lx", control);
                err = ioctl(fd_ltc185x, MZIO_LTC185x_CH5SE_SETUP, control);
                if (err<0) printf("Can't set Ch2 settings\n");

                tempStr = ui->ch5_samrate->text();
                tempULong = tempStr.toULong();
                err = ioctl(fd_ltc185x, MZIO_LTC185x_CH5SE_SET_PERIOD, tempULong);
                if (err<0) printf("Can't set Ch5 period\n");
            }
        }




        if (ui->Ch67->isChecked())
        {
            startSampling++;
            control = LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain;
            printf("Ch67 setup 0x%lx", control);
            err = ioctl(fd_ltc185x, MZIO_LTC185x_CH67DE_SETUP, control);
            if (err<0) printf("Can't set Ch67 settings\n");

            tempStr = ui->ch2_samrate->text();
            tempULong = tempStr.toULong();
            err = ioctl(fd_ltc185x, MZIO_LTC185x_CH67DE_SET_PERIOD, tempULong);
            if (err<0) printf("Can't set Ch67 period\n");

            // Uncheck Ch0 and Ch1
            ui->Ch6->setChecked(0);
            ui->Ch7->setChecked(0);
        }
        else
        {
            if (ui->Ch6->isChecked())
            {
                startSampling++;
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
                startSampling++;
                control = LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain;
                printf("Ch7 setup 0x%lx", control);
                err = ioctl(fd_ltc185x, MZIO_LTC185x_CH7SE_SETUP, control);
                if (err<0) printf("Can't set Ch7 settings\n");

                tempStr = ui->ch7_samrate->text();
                tempULong = tempStr.toULong();
                err = ioctl(fd_ltc185x, MZIO_LTC185x_CH7SE_SET_PERIOD, tempULong);
                if (err<0) printf("Can't set Ch7 period\n");

            }
        }


        // Start sampling
        err = ioctl(fd_ltc185x, MZIO_LTC185x_START, 0);
        if (err<0) printf("Can't start ADC\n");

        isSampling = 1;
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

    isSampling = 0;
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

int MainWindow::PrvGetSamples(int Ch, unsigned short* buf, unsigned int *overun)
{
    ReadBufferData  RdBufDat;
    unsigned short  *datPtr;


    RdBufDat.ch = Ch;
    RdBufDat.buf = buf;
    RdBufDat.numSamples = ChMaxReadSamples;
    RdBufDat.overun = overun;

    gErr = ioctl(fd_ltc185x, MZIO_LTC185x_READ_BUFFER, &RdBufDat);
    if (gErr<0)  printf("Error reading Ch0 buffer %s\n", strerror(gErr));
    else
    {
        Ch0NumSamples=gErr;
        if (RdBufDat.buf == 0)
        {
            printf("Number of sample to receive %d, overun=%d\n", Ch0NumSamples, *overun);
        }
        else
        {
            datPtr = buf;
            printf("Ch0 { %d %d %d %d %d } %d %d\n", datPtr[0],datPtr[1],datPtr[2],datPtr[3],datPtr[4], Ch0NumSamples, *overun);
        }
    }

    if (*overun)
    {
        // If we have an overun situation, we need to restart the sampling
        strBuf.sprintf("Restarting sampling");
        ui->status->setText(strBuf);
        RESET_STATUS_TIMER;

        MainWindow::on_Stop_clicked();
        MainWindow::on_Start_clicked();
    }

    return 0;
}

void MainWindow::on_timer_event()
{
    if (status_erase_count-- <=0)
    {
        strBuf.sprintf("");
        ui->status->setText(strBuf);
        RESET_STATUS_TIMER;
    }

    if (isSampling)
    {
        if (sample_timer_count-- <= 0)
        {
            if (fd_ltc185x)
            {
                unsigned int    overun=0;
                int             numSamples;

                // Setup the channels
                if (ui->Ch01->isChecked())
                {
                    numSamples = PrvGetSamples(Chn01, RdBuf->Ch01Buf, &overun);
                }
                else
                {
                    if (ui->Ch0->isChecked())
                    {
                        numSamples = PrvGetSamples(Chn0, RdBuf->Ch0Buf, &overun);
                    }

                    if (ui->Ch1->isChecked())
                    {
                        numSamples = PrvGetSamples(Chn1, RdBuf->Ch1Buf, &overun);
                    }
                }

                if (ui->Ch23->isChecked())
                {
                    numSamples = PrvGetSamples(Chn23, RdBuf->Ch23Buf, &overun);
                }
                else
                {
                    if (ui->Ch2->isChecked())
                    {
                        numSamples = PrvGetSamples(Chn2, RdBuf->Ch2Buf, &overun);
                    }

                    if (ui->Ch3->isChecked())
                    {
                        numSamples = PrvGetSamples(Chn3, RdBuf->Ch3Buf, &overun);
                    }
                }



                if (ui->Ch45->isChecked())
                {
                    numSamples = PrvGetSamples(Chn45, RdBuf->Ch45Buf, &overun);
                }
                else
                {
                    if (ui->Ch4->isChecked())
                    {
                        numSamples = PrvGetSamples(Chn4, RdBuf->Ch4Buf, &overun);
                    }

                    if (ui->Ch5->isChecked())
                    {
                        numSamples = PrvGetSamples(Chn5, RdBuf->Ch5Buf, &overun);
                    }
                }


                if (ui->Ch67->isChecked())
                {
                    numSamples = PrvGetSamples(Chn67, RdBuf->Ch67Buf, &overun);
                }
                else
                {
                    if (ui->Ch6->isChecked())
                    {
                        numSamples = PrvGetSamples(Chn6, RdBuf->Ch6Buf, &overun);
                    }

                    if (ui->Ch7->isChecked())
                    {
                        numSamples = PrvGetSamples(Chn7, RdBuf->Ch7Buf, &overun);
                    }
                }
            }




            RESET_READ_TIMER;
        }
    }
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

void MainWindow::on_readButton_clicked()
{
    int err;

    // Stop sampling
//    err = ioctl(fd_ltc185x, MZIO_LTC185x_READ, bigDataBuffer);
 //   if (err<0) printf("Can't read ADC data\n");
  //  else printf("Reading ADC data to 0x%lx\n %d %d %d %d %d", (unsigned long) bigDataBuffer, bigDataBuffer[0], bigDataBuffer[1],bigDataBuffer[2],bigDataBuffer[3],bigDataBuffer[4]);
   // fflush(stdout);
}
