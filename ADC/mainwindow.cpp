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

#define TIMER_PERIOD            1000                        // msecs
#define RESET_STATUS_TIMER      status_erase_count=5        // 5s
#define RESET_READ_TIMER        sample_timer_count=1        // 1000ms

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
    RESET_READ_TIMER;

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

int MainWindow::PrvSetChannelConfig(int Ch, unsigned int config, unsigned long period)
{
    ChConfigData ChConfig;

    ChConfig.ch = Ch;
    ChConfig.config = config;
    ChConfig.period = period;

    gErr = ioctl(fd_ltc185x, MZIO_LTC185x_CHANNEL_SETUP, &ChConfig);
    if (gErr<0) printf("Can't set Ch%d settings\n", Ch);
    else printf("Ch%d setup 0x%x period=%ld\n", Ch, config, period);

    return gErr;
}

void MainWindow::on_Start_clicked()
{
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
            tempStr = ui->ch0_samrate->text();
            tempULong = tempStr.toULong();
            err = PrvSetChannelConfig(Chn01, LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain, tempULong);

            err = PrvSetChannelConfig(Chn0, 0, 0);
            err = PrvSetChannelConfig(Chn1, 0, 0);
        }
        else
        {
            err = PrvSetChannelConfig(Chn01, 0, 0);

            if (ui->Ch0->isChecked())
            {
                startSampling++;
                tempStr = ui->ch0_samrate->text();
                tempULong = tempStr.toULong();
                err = PrvSetChannelConfig(Chn0, LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain, tempULong);
            }
            else
            {
                err = PrvSetChannelConfig(Chn0, 0 , 0);
            }

            if (ui->Ch1->isChecked())
            {
                startSampling++;
                tempStr = ui->ch1_samrate->text();
                tempULong = tempStr.toULong();
                err = PrvSetChannelConfig(Chn1, LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain, tempULong);
            }
            else
            {
                err = PrvSetChannelConfig(Chn1, 0 , 0);
            }
        }


        if (ui->Ch23->isChecked())
        {
            startSampling++;
            tempStr = ui->ch2_samrate->text();
            tempULong = tempStr.toULong();
            err = PrvSetChannelConfig(Chn23, LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain, tempULong);

            err = PrvSetChannelConfig(Chn2, 0, 0);
            err = PrvSetChannelConfig(Chn3, 0, 0);
        }
        else
        {
            err = PrvSetChannelConfig(Chn23, 0, 0);

            if (ui->Ch2->isChecked())
            {
                startSampling++;
                tempStr = ui->ch2_samrate->text();
                tempULong = tempStr.toULong();
                err = PrvSetChannelConfig(Chn2, LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain, tempULong);
            }
            else
            {
                err = PrvSetChannelConfig(Chn2, 0 , 0);
            }

            if (ui->Ch3->isChecked())
            {
                startSampling++;
                tempStr = ui->ch3_samrate->text();
                tempULong = tempStr.toULong();
                err = PrvSetChannelConfig(Chn3, LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain, tempULong);
            }
            else
            {
                err = PrvSetChannelConfig(Chn3, 0 , 0);
            }
        }

        if (ui->Ch45->isChecked())
        {
            startSampling++;
            tempStr = ui->ch4_samrate->text();
            tempULong = tempStr.toULong();
            err = PrvSetChannelConfig(Chn45, LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain, tempULong);

            err = PrvSetChannelConfig(Chn4, 0, 0);
            err = PrvSetChannelConfig(Chn5, 0, 0);
        }
        else
        {
            err = PrvSetChannelConfig(Chn45, 0, 0);

            if (ui->Ch4->isChecked())
            {
                startSampling++;
                tempStr = ui->ch4_samrate->text();
                tempULong = tempStr.toULong();
                err = PrvSetChannelConfig(Chn4, LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain, tempULong);
            }
            else
            {
                err = PrvSetChannelConfig(Chn4, 0 , 0);
            }


            if (ui->Ch5->isChecked())
            {
                startSampling++;
                tempStr = ui->ch5_samrate->text();
                tempULong = tempStr.toULong();
                err = PrvSetChannelConfig(Chn5, LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain, tempULong);
            }
            else
            {
                err = PrvSetChannelConfig(Chn5, 0 , 0);
            }
        }




        if (ui->Ch67->isChecked())
        {
            startSampling++;
            tempStr = ui->ch6_samrate->text();
            tempULong = tempStr.toULong();
            err = PrvSetChannelConfig(Chn67, LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain, tempULong);

            err = PrvSetChannelConfig(Chn6, 0, 0);
            err = PrvSetChannelConfig(Chn7, 0, 0);
        }
        else
        {
            err = PrvSetChannelConfig(Chn67, 0, 0);

            if (ui->Ch6->isChecked())
            {
                startSampling++;
                tempStr = ui->ch6_samrate->text();
                tempULong = tempStr.toULong();
                err = PrvSetChannelConfig(Chn6, LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain, tempULong);
            }
            else
            {
                err = PrvSetChannelConfig(Chn6, 0 , 0);
            }

            if (ui->Ch7->isChecked())
            {
                startSampling++;
                tempStr = ui->ch7_samrate->text();
                tempULong = tempStr.toULong();
                err = PrvSetChannelConfig(Chn7, LTC185x_ChSetup_Enabled|LTC185x_ChSetup_Gain, tempULong);
            }
            else
            {
                err = PrvSetChannelConfig(Chn7, 0 , 0);
            }
        }


        // Start sampling
        if (startSampling)
        {
            err = ioctl(fd_ltc185x, MZIO_LTC185x_START, 0);
            if (err<0) printf("Can't start ADC\n");

            isSampling = 1;
        }
    }
    else
    {
        printf("LTC185x library failure\n");
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
    if (ui->Ch01->checkState()) ui->Ch0->setChecked(0);
    else
    {
        strBuf.sprintf("Ch0 %s", (ui->Ch0->checkState()) ? "selected":"deselected");
        ui->status->setText(strBuf);
        RESET_STATUS_TIMER;
    }
}

void MainWindow::on_Ch1_clicked()
{
    if (ui->Ch01->checkState()) ui->Ch1->setChecked(0);
    else
    {
        strBuf.sprintf("Ch1 %s", (ui->Ch1->checkState()) ? "selected":"deselected");
        ui->status->setText(strBuf);
        RESET_STATUS_TIMER;
    }
}

void MainWindow::on_Ch2_clicked()
{
    if (ui->Ch23->checkState()) ui->Ch2->setChecked(0);
    else
    {
        strBuf.sprintf("Ch2 %s", (ui->Ch2->checkState()) ? "selected":"deselected");
        ui->status->setText(strBuf);
        RESET_STATUS_TIMER;
    }
}

void MainWindow::on_Ch3_clicked()
{
    if (ui->Ch23->checkState()) ui->Ch3->setChecked(0);
    else
    {
        strBuf.sprintf("Ch3 %s", (ui->Ch3->checkState()) ? "selected":"deselected");
        ui->status->setText(strBuf);
        RESET_STATUS_TIMER;

    }
}

void MainWindow::on_Ch4_clicked()
{
    if (ui->Ch45->checkState()) ui->Ch4->setChecked(0);
    else
    {
        strBuf.sprintf("Ch4 %s", (ui->Ch4->checkState()) ? "selected":"deselected");
        ui->status->setText(strBuf);
        RESET_STATUS_TIMER;
    }
}

void MainWindow::on_Ch5_clicked()
{
    if (ui->Ch45->checkState()) ui->Ch5->setChecked(0);
    else
    {
        strBuf.sprintf("Ch0 %s", (ui->Ch0->checkState()) ? "selected":"deselected");
        ui->status->setText(strBuf);
        RESET_STATUS_TIMER;
    }
}

void MainWindow::on_Ch6_clicked()
{
    if (ui->Ch67->checkState()) ui->Ch6->setChecked(0);
    else
    {
        strBuf.sprintf("Ch6 %s", (ui->Ch6->checkState()) ? "selected":"deselected");
        ui->status->setText(strBuf);
        RESET_STATUS_TIMER;
    }
}

void MainWindow::on_Ch7_clicked()
{
    if (ui->Ch67->checkState()) ui->Ch7->setChecked(0);
    else
    {
        strBuf.sprintf("Ch7 %s", (ui->Ch7->checkState()) ? "selected":"deselected");
        ui->status->setText(strBuf);
        RESET_STATUS_TIMER;
    }
}

void MainWindow::on_Ch01_clicked()
{
    strBuf.sprintf("Ch01 %s", (ui->Ch01->checkState()) ? "selected":"deselected");
    ui->status->setText(strBuf);

    ui->Ch0->setChecked(0);
    ui->Ch1->setChecked(0);
    RESET_STATUS_TIMER;
}

void MainWindow::on_Ch23_clicked()
{
    strBuf.sprintf("Ch23 %s", (ui->Ch23->checkState()) ? "selected":"deselected");
    ui->status->setText(strBuf);
    RESET_STATUS_TIMER;

    ui->Ch2->setChecked(0);
    ui->Ch3->setChecked(0);

}

void MainWindow::on_Ch45_clicked()
{
    QString strBuf="";
    strBuf.sprintf("Ch45 %s", (ui->Ch45->checkState()) ? "selected":"deselected");
    ui->status->setText(strBuf);
    RESET_STATUS_TIMER;
    ui->Ch4->setChecked(0);
    ui->Ch5->setChecked(0);

}

void MainWindow::on_Ch67_clicked()
{
    QString strBuf="";
    strBuf.sprintf("Ch67 %s", (ui->Ch67->checkState()) ? "selected":"deselected");
    ui->status->setText(strBuf);
    RESET_STATUS_TIMER;

    ui->Ch6->setChecked(0);
    ui->Ch7->setChecked(0);
}


int MainWindow::PrvGetSamples(int Ch, unsigned short* buf, unsigned int *overun)
{
    ReadBufferData  RdBufDat;
//    unsigned short  *datPtr;


    RdBufDat.ch = Ch;
    RdBufDat.buf = buf;
    RdBufDat.numSamples = ChMaxReadSamples;
    RdBufDat.overun = overun;

    gErr = ioctl(fd_ltc185x, MZIO_LTC185x_READ_BUFFER, &RdBufDat);
    if (gErr<0)  printf("Error reading Ch0 buffer %s\n", strerror(gErr));
    else
    {
        Ch0NumSamples=gErr;
        /*
        if (RdBufDat.buf == 0)
        {
            printf("Number of sample to receive %d, overun=%d\n", Ch0NumSamples, *overun);
        }
        else
        {
            datPtr = buf;
            printf("Ch0 { %d %d %d %d %d } %d %d\n", datPtr[0],datPtr[1],datPtr[2],datPtr[3],datPtr[4], Ch0NumSamples, *overun);
        }
        */
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
                char            tempStr[50];

                // Setup the channels
                if (ui->Ch01->isChecked())
                {
                    numSamples = PrvGetSamples(Chn01, RdBuf->Ch01Buf, &overun);
                    sprintf(tempStr, "Ch01=0x%x %dd\n", RdBuf->Ch01Buf[0],RdBuf->Ch01Buf[0]);
                    printf("%s", tempStr);
                    strBuf.sprintf("%s", tempStr);
                    ui->ChVal_0->setText(strBuf);
                    ui->ChVal_1->setText("");
                }
                else
                {
                    if (ui->Ch0->isChecked())
                    {
                        numSamples = PrvGetSamples(Chn0, RdBuf->Ch0Buf, &overun);

                        sprintf(tempStr, "Ch0=0x%x %dd\n", RdBuf->Ch0Buf[0],RdBuf->Ch0Buf[0]);
                        printf("%s", tempStr);
                        strBuf.sprintf("%s", tempStr);
                        ui->ChVal_0->setText(strBuf);
                    }

                    if (ui->Ch1->isChecked())
                    {
                        numSamples = PrvGetSamples(Chn1, RdBuf->Ch1Buf, &overun);
                        sprintf(tempStr, "Ch1=0x%x %dd\n", RdBuf->Ch1Buf[0],RdBuf->Ch1Buf[0]);
                        printf("%s", tempStr);
                        strBuf.sprintf("%s", tempStr);
                        ui->ChVal_1->setText(strBuf);
                    }
                }

                if (ui->Ch23->isChecked())
                {
                    numSamples = PrvGetSamples(Chn23, RdBuf->Ch23Buf, &overun);
                    sprintf(tempStr, "Ch23=0x%x %dd\n", RdBuf->Ch23Buf[0],RdBuf->Ch23Buf[0]);
                    printf("%s", tempStr);
                    strBuf.sprintf("%s", tempStr);
                    ui->ChVal_2->setText(strBuf);
                    ui->ChVal_3->setText("");
                }
                else
                {
                    if (ui->Ch2->isChecked())
                    {
                        numSamples = PrvGetSamples(Chn2, RdBuf->Ch2Buf, &overun);
                        sprintf(tempStr, "Ch2=0x%x %dd\n", RdBuf->Ch2Buf[0],RdBuf->Ch2Buf[0]);
                        printf("%s", tempStr);
                        strBuf.sprintf("%s", tempStr);
                        ui->ChVal_2->setText(strBuf);
                    }

                    if (ui->Ch3->isChecked())
                    {
                        numSamples = PrvGetSamples(Chn3, RdBuf->Ch3Buf, &overun);
                        sprintf(tempStr, "Ch3=0x%x %dd\n", RdBuf->Ch3Buf[0],RdBuf->Ch3Buf[0]);
                        printf("%s", tempStr);
                        strBuf.sprintf("%s", tempStr);
                        ui->ChVal_3->setText(strBuf);
                    }
                }


                if (ui->Ch45->isChecked())
                {
                    numSamples = PrvGetSamples(Chn45, RdBuf->Ch45Buf, &overun);
                    sprintf(tempStr, "Ch45=0x%x %dd\n", RdBuf->Ch45Buf[0],RdBuf->Ch45Buf[0]);
                    printf("%s", tempStr);
                    strBuf.sprintf("%s", tempStr);
                    ui->ChVal_4->setText(strBuf);
                    ui->ChVal_5->setText("");
                }
                else
                {
                    if (ui->Ch4->isChecked())
                    {
                        numSamples = PrvGetSamples(Chn4, RdBuf->Ch4Buf, &overun);
                        sprintf(tempStr, "Ch4=0x%x %dd\n", RdBuf->Ch4Buf[0],RdBuf->Ch4Buf[0]);
                        printf("%s", tempStr);
                        strBuf.sprintf("%s", tempStr);
                        ui->ChVal_4->setText(strBuf);
                    }

                    if (ui->Ch5->isChecked())
                    {
                        numSamples = PrvGetSamples(Chn5, RdBuf->Ch5Buf, &overun);
                        sprintf(tempStr, "Ch5=0x%x %dd\n", RdBuf->Ch5Buf[0],RdBuf->Ch5Buf[0]);
                        printf("%s", tempStr);
                        strBuf.sprintf("%s", tempStr);
                        ui->ChVal_5->setText(strBuf);
                    }
                }


                if (ui->Ch67->isChecked())
                {
                    numSamples = PrvGetSamples(Chn67, RdBuf->Ch67Buf, &overun);
                    sprintf(tempStr, "Ch67=0x%x %dd\n", RdBuf->Ch67Buf[0],RdBuf->Ch67Buf[0]);
                    printf("%s", tempStr);
                    strBuf.sprintf("%s", tempStr);
                    ui->ChVal_6->setText(strBuf);
                    ui->ChVal_7->setText("");
                }
                else
                {
                    if (ui->Ch6->isChecked())
                    {
                        numSamples = PrvGetSamples(Chn6, RdBuf->Ch6Buf, &overun);
                        sprintf(tempStr, "Ch6=0x%x %dd\n", RdBuf->Ch6Buf[0],RdBuf->Ch6Buf[0]);
                        printf("%s", tempStr);
                        strBuf.sprintf("%s", tempStr);
                        ui->ChVal_6->setText(strBuf);
                    }

                    if (ui->Ch7->isChecked())
                    {
                        numSamples = PrvGetSamples(Chn7, RdBuf->Ch7Buf, &overun);
                        sprintf(tempStr, "Ch7=0x%x %dd\n", RdBuf->Ch7Buf[0],RdBuf->Ch7Buf[0]);
                        printf("%s", tempStr);
                        strBuf.sprintf("%s", tempStr);
                        ui->ChVal_7->setText(strBuf);
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

