#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <QTimer>
#include <QObject>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "/opt/MEZ1500Rev2dLinux/Sources/linux-2.6.32.2/drivers/char/MEZ1500_mzio.h"
#include "/opt/MEZ1500Rev2dLinux/Sources/linux-2.6.32.2/drivers/char/MEZ1500_mzio_ltc185x.h"
#include <sys/time.h>
#include "adc1.h"
#include "keyboard/keyboard.h"

QTextStream cout(stdout);
QTextStream cerr(stderr);

#define TIMER_PERIOD            100                        // msecs
#define RESET_STATUS_TIMER      status_erase_count=50        // 5s
#define RESET_READ_TIMER        sample_timer_count=5       // 500ms

// --------------------------------------------------------------------
// Internal Functions
// --------------------------------------------------------------------
// --------------------------------------------------------------------


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    int i;

    printf("char=%d, short=%d, int=%d, long=%d, long long=%d\n",
        sizeof(char),
        sizeof(short),
        sizeof(int),
        sizeof(long),
        sizeof(long long));


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

    // Pop up keyboard
    lineEditkeyboard = new Keyboard();
    connect(ui->ch0_samrate,SIGNAL(selectionChanged()),this,SLOT(run_keyboard_lineEdit()));
    connect(ui->ch1_samrate,SIGNAL(selectionChanged()),this,SLOT(run_keyboard_lineEdit()));
    connect(ui->ch2_samrate,SIGNAL(selectionChanged()),this,SLOT(run_keyboard_lineEdit()));
    connect(ui->ch3_samrate,SIGNAL(selectionChanged()),this,SLOT(run_keyboard_lineEdit()));
    connect(ui->ch4_samrate,SIGNAL(selectionChanged()),this,SLOT(run_keyboard_lineEdit()));
    connect(ui->ch5_samrate,SIGNAL(selectionChanged()),this,SLOT(run_keyboard_lineEdit()));
    connect(ui->ch6_samrate,SIGNAL(selectionChanged()),this,SLOT(run_keyboard_lineEdit()));
    connect(ui->ch7_samrate,SIGNAL(selectionChanged()),this,SLOT(run_keyboard_lineEdit()));

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


    // Signal slot mapping
    connect(ui->checkBox_5V_Ch_0, SIGNAL(clicked()), this, SLOT(on_checkBox_5V10V_clicked()));
    connect(ui->checkBox_5V_Ch_1, SIGNAL(clicked()), this, SLOT(on_checkBox_5V10V_clicked()));
    connect(ui->checkBox_5V_Ch_2, SIGNAL(clicked()), this, SLOT(on_checkBox_5V10V_clicked()));
    connect(ui->checkBox_5V_Ch_3, SIGNAL(clicked()), this, SLOT(on_checkBox_5V10V_clicked()));
    connect(ui->checkBox_5V_Ch_4, SIGNAL(clicked()), this, SLOT(on_checkBox_5V10V_clicked()));
    connect(ui->checkBox_5V_Ch_5, SIGNAL(clicked()), this, SLOT(on_checkBox_5V10V_clicked()));
    connect(ui->checkBox_5V_Ch_6, SIGNAL(clicked()), this, SLOT(on_checkBox_5V10V_clicked()));
    connect(ui->checkBox_5V_Ch_7, SIGNAL(clicked()), this, SLOT(on_checkBox_5V10V_clicked()));
    connect(ui->checkBox_10V_Ch_0, SIGNAL(clicked()), this, SLOT(on_checkBox_5V10V_clicked()));
    connect(ui->checkBox_10V_Ch_1, SIGNAL(clicked()), this, SLOT(on_checkBox_5V10V_clicked()));
    connect(ui->checkBox_10V_Ch_2, SIGNAL(clicked()), this, SLOT(on_checkBox_5V10V_clicked()));
    connect(ui->checkBox_10V_Ch_3, SIGNAL(clicked()), this, SLOT(on_checkBox_5V10V_clicked()));
    connect(ui->checkBox_10V_Ch_4, SIGNAL(clicked()), this, SLOT(on_checkBox_5V10V_clicked()));
    connect(ui->checkBox_10V_Ch_5, SIGNAL(clicked()), this, SLOT(on_checkBox_5V10V_clicked()));
    connect(ui->checkBox_10V_Ch_6, SIGNAL(clicked()), this, SLOT(on_checkBox_5V10V_clicked()));
    connect(ui->checkBox_10V_Ch_7, SIGNAL(clicked()), this, SLOT(on_checkBox_5V10V_clicked()));

    connect(ui->ch0_samrate, SIGNAL(editingFinished()), this, SLOT(on_samrate_editingFinished()));
    connect(ui->ch1_samrate, SIGNAL(editingFinished()), this, SLOT(on_samrate_editingFinished()));
    connect(ui->ch2_samrate, SIGNAL(editingFinished()), this, SLOT(on_samrate_editingFinished()));
    connect(ui->ch3_samrate, SIGNAL(editingFinished()), this, SLOT(on_samrate_editingFinished()));
    connect(ui->ch4_samrate, SIGNAL(editingFinished()), this, SLOT(on_samrate_editingFinished()));
    connect(ui->ch5_samrate, SIGNAL(editingFinished()), this, SLOT(on_samrate_editingFinished()));
    connect(ui->ch6_samrate, SIGNAL(editingFinished()), this, SLOT(on_samrate_editingFinished()));
    connect(ui->ch7_samrate, SIGNAL(editingFinished()), this, SLOT(on_samrate_editingFinished()));

    RESET_STATUS_TIMER;
    RESET_READ_TIMER;

    // For now init all the sampling rate values to 1000us
    i = 1;
    ui->ch0_samrate->setText(strBuf.sprintf("%u", i));
    ui->ch1_samrate->setText(strBuf.sprintf("%u", i));
    ui->ch2_samrate->setText(strBuf.sprintf("%u", i));
    ui->ch3_samrate->setText(strBuf.sprintf("%u", i));
    ui->ch4_samrate->setText(strBuf.sprintf("%u", i));
    ui->ch5_samrate->setText(strBuf.sprintf("%u", i));
    ui->ch6_samrate->setText(strBuf.sprintf("%u", i));
    ui->ch7_samrate->setText(strBuf.sprintf("%u", i));

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    minutes=QTime::currentTime().minute();

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


QString* MainWindow::PrvGetChStr(int Ch, QString* chStr)
{

    if      (Ch==Chn01)  chStr->sprintf("01");
    else if (Ch==Chn23)  chStr->sprintf("23");
    else if (Ch==Chn45)  chStr->sprintf("45");
    else if (Ch==Chn67)  chStr->sprintf("67");
    else                 chStr->sprintf("%d",Ch);

    return chStr;
}

int MainWindow::PrvCalculateMultiplier(int V5, int unipolar)
{
		// The multiplier result is in uV
    // V5=1 5V is selected, otherwise assume 10V is selected
    if (V5  && unipolar)    return 	(1000000 * 5) 	/ 65535;
    if (V5  && !unipolar)   return 	(1000000 * 10)	/ 65535;
    if (!V5 && unipolar)    return 	(1000000 * 10)	/ 65535;
    if (!V5 && !unipolar)   return	(1000000 * 20)	/ 65535;
    return 0;
}

int MainWindow::PrvCalculate_mV(int Ch, int data)
{
    int retVal;
    double d;

    if (ChConfig[Ch].unipolar)
    {
        retVal = ((unsigned short) data) * ChConfig[Ch].multiplier / 1000;
        strBuf.sprintf("Ch%s=%dmV uni 0x%x",
                       PrvGetChStr(Ch, &strBuf)->toStdString().c_str(),
                       retVal,
                       data);
    }
    else
    {
        retVal = ((short) data) * ChConfig[Ch].multiplier / 1000;
        d = (double)((data * 5) / 65535);
        strBuf.sprintf("Ch%s=%dmV bi 0x%x %0.3fVolts",
                       PrvGetChStr(Ch, &strBuf)->toStdString().c_str(),
                       retVal,
                       data,
                       d);
    }

    qDebug() << strBuf;
    return retVal;
}


int MainWindow::PrvSetChannelConfig(int Ch, unsigned int config, unsigned long long period)
{
    ChConfigDataType ChConfigData;

    if (!period && (config & LTC185x_ChSetup_Enabled))
    {
        QMessageBox::information(this,
                                 "ADC App",
                                 strBuf.sprintf("Ch%s has incorrect period value. Valid range is %d to %d.",
                                                PrvGetChStr(Ch, &strBuf)->toStdString().c_str(),
                                                samRateFieldMin,
                                                samRateFieldMax
                                                )
                                 );
        return -1;
    }
    ChConfigData.ch     = Ch;
    ChConfigData.config = config;
    ChConfig[Ch].periodCounter = 0;

    // If period is greater than 1 hour (in useconds), then we split it up in hours and usecs
    if (period > TimerCount1HrInUs)
    {
        ChConfigData.periodUSecs = (unsigned long) (period % TimerCount1HrInUs);
        ChConfigData.periodHours = (unsigned long) (period / TimerCount1HrInUs);
    } else
    {
        ChConfigData.periodUSecs = period;
        ChConfigData.periodHours = 0;
    }

    switch (Ch)
    {
        case Chn0:
            sprintf(ChConfig[Ch].filename, "%s", CH0File);
            sprintf(ChConfig[Ch].chNameStr, "Ch0");
            ChConfig[Ch].RdBufPtr 	= RdBuf->Ch0Buf;
            ChConfig[Ch].unipolar 	= ui->checkBox_uni_Ch_0->isChecked();
            ChConfig[Ch].v5 		= ui->checkBox_5V_Ch_0->isChecked();
            ChConfig[Ch].multiplier	= PrvCalculateMultiplier(ChConfig[Ch].v5, ChConfig[Ch].unipolar);
            break;

        case Chn1:
            sprintf(ChConfig[Ch].filename, "%s", CH1File);
            sprintf(ChConfig[Ch].chNameStr, "Ch1");
            ChConfig[Ch].RdBufPtr   = RdBuf->Ch1Buf;
            ChConfig[Ch].unipolar 	= ui->checkBox_uni_Ch_1->isChecked();
            ChConfig[Ch].v5 		= ui->checkBox_5V_Ch_1->isChecked();
            ChConfig[Ch].multiplier	= PrvCalculateMultiplier(ChConfig[Ch].v5, ChConfig[Ch].unipolar);
            break;
        case Chn2:
            sprintf(ChConfig[Ch].filename, "%s", CH2File);
            sprintf(ChConfig[Ch].chNameStr, "Ch2");
            ChConfig[Ch].RdBufPtr   = RdBuf->Ch2Buf;
            ChConfig[Ch].unipolar 	= ui->checkBox_uni_Ch_2->isChecked();
            ChConfig[Ch].v5 		= ui->checkBox_5V_Ch_2->isChecked();
            ChConfig[Ch].multiplier	= PrvCalculateMultiplier(ChConfig[Ch].v5, ChConfig[Ch].unipolar);
            break;
        case Chn3:
            sprintf(ChConfig[Ch].filename, "%s", CH3File);
            sprintf(ChConfig[Ch].chNameStr, "Ch3");
            ChConfig[Ch].RdBufPtr   = RdBuf->Ch3Buf;
            ChConfig[Ch].unipolar 	= ui->checkBox_uni_Ch_3->isChecked();
            ChConfig[Ch].v5 		= ui->checkBox_5V_Ch_3->isChecked();
            ChConfig[Ch].multiplier	= PrvCalculateMultiplier(ChConfig[Ch].v5, ChConfig[Ch].unipolar);
            break;
        case Chn4:
            sprintf(ChConfig[Ch].filename, "%s", CH4File);
            sprintf(ChConfig[Ch].chNameStr, "Ch4");
            ChConfig[Ch].RdBufPtr = RdBuf->Ch4Buf;
            ChConfig[Ch].unipolar 	= ui->checkBox_uni_Ch_4->isChecked();
            ChConfig[Ch].v5 				= ui->checkBox_5V_Ch_4->isChecked();
            ChConfig[Ch].multiplier	= PrvCalculateMultiplier(ChConfig[Ch].v5, ChConfig[Ch].unipolar);
            break;
        case Chn5:
            sprintf(ChConfig[Ch].filename, "%s", CH5File);
            sprintf(ChConfig[Ch].chNameStr, "Ch5");
            ChConfig[Ch].RdBufPtr   = RdBuf->Ch5Buf;
            ChConfig[Ch].unipolar 	= ui->checkBox_uni_Ch_5->isChecked();
            ChConfig[Ch].v5 		= ui->checkBox_5V_Ch_5->isChecked();
            ChConfig[Ch].multiplier	= PrvCalculateMultiplier(ChConfig[Ch].v5, ChConfig[Ch].unipolar);
            break;
        case Chn6:
            sprintf(ChConfig[Ch].filename, "%s", CH6File);
            sprintf(ChConfig[Ch].chNameStr, "Ch6");
            ChConfig[Ch].RdBufPtr   = RdBuf->Ch6Buf;
            ChConfig[Ch].unipolar 	= ui->checkBox_uni_Ch_6->isChecked();
            ChConfig[Ch].v5 		= ui->checkBox_5V_Ch_6->isChecked();
            ChConfig[Ch].multiplier	= PrvCalculateMultiplier(ChConfig[Ch].v5, ChConfig[Ch].unipolar);
            break;
        case Chn7:
            sprintf(ChConfig[Ch].filename, "%s", CH7File);
            sprintf(ChConfig[Ch].chNameStr, "Ch7");
            ChConfig[Ch].RdBufPtr   = RdBuf->Ch7Buf;
            ChConfig[Ch].unipolar 	= ui->checkBox_uni_Ch_7->isChecked();
            ChConfig[Ch].v5 		= ui->checkBox_5V_Ch_7->isChecked();
            ChConfig[Ch].multiplier	= PrvCalculateMultiplier(ChConfig[Ch].v5, ChConfig[Ch].unipolar);
            break;
        case Chn01:
            sprintf(ChConfig[Ch].filename, "%s", CH01File);
            sprintf(ChConfig[Ch].chNameStr, "Ch01");
            ChConfig[Ch].RdBufPtr   = RdBuf->Ch01Buf;
            ChConfig[Ch].unipolar 	= ui->checkBox_uni_Ch_0->isChecked();
            ChConfig[Ch].v5 		= ui->checkBox_5V_Ch_0->isChecked();
            ChConfig[Ch].multiplier	= PrvCalculateMultiplier(ChConfig[Ch].v5, ChConfig[Ch].unipolar);
            break;
        case Chn23:
            sprintf(ChConfig[Ch].filename, "%s", CH23File);
            sprintf(ChConfig[Ch].chNameStr, "Ch23");
            ChConfig[Ch].RdBufPtr   = RdBuf->Ch23Buf;
            ChConfig[Ch].unipolar 	= ui->checkBox_uni_Ch_2->isChecked();
            ChConfig[Ch].v5 		= ui->checkBox_5V_Ch_2->isChecked();
            ChConfig[Ch].multiplier	= PrvCalculateMultiplier(ChConfig[Ch].v5, ChConfig[Ch].unipolar);
            break;
        case Chn45:
            sprintf(ChConfig[Ch].filename, "%s", CH45File);
            sprintf(ChConfig[Ch].chNameStr, "Ch45");
            ChConfig[Ch].RdBufPtr   = RdBuf->Ch45Buf;
            ChConfig[Ch].unipolar 	= ui->checkBox_uni_Ch_4->isChecked();
            ChConfig[Ch].v5 		= ui->checkBox_5V_Ch_4->isChecked();
            ChConfig[Ch].multiplier	= PrvCalculateMultiplier(ChConfig[Ch].v5, ChConfig[Ch].unipolar);
            break;
        case Chn67:
            sprintf(ChConfig[Ch].filename, "%s", CH67File);
            sprintf(ChConfig[Ch].chNameStr, "Ch67");
            ChConfig[Ch].RdBufPtr   = RdBuf->Ch67Buf;
            ChConfig[Ch].unipolar 	= ui->checkBox_uni_Ch_6->isChecked();
            ChConfig[Ch].v5 		= ui->checkBox_5V_Ch_6->isChecked();
            ChConfig[Ch].multiplier	= PrvCalculateMultiplier(ChConfig[Ch].v5, ChConfig[Ch].unipolar);
            break;
        default:
            printf("Channel unknown");
            break;
    }


    gErr = ioctl(fd_ltc185x, MZIO_LTC185x_CHANNEL_SETUP, &ChConfigData);
    if (gErr<0) printf("Can't set Ch%d settings\n", Ch);
    else printf("Ch%d setup 0x%x period=%llu, periodUSecs=%lu, periodHours=%lu, multiplier=%d\n",
                Ch,
                config,
                period,
                ChConfigData.periodUSecs,
                ChConfigData.periodHours,
                ChConfig[Ch].multiplier
                );

    return gErr;
}


unsigned long long MainWindow::PrvGetLineEditValue(int Ch)
{
    int index;
    QValidator *validator = new QIntValidator(samRateFieldMin,samRateFieldMax, this);
    QComboBox   *thePeriodBox;
    QLineEdit   *theLineEdit;

    switch (Ch)
    {
        case Chn0:
        case Chn01:
            thePeriodBox = ui->periodBox_0;
            theLineEdit = ui->ch0_samrate;
            break;
        case Chn1:
            thePeriodBox = ui->periodBox_1;
            theLineEdit = ui->ch1_samrate;
            break;
        case Chn2:
        case Chn23:
            thePeriodBox = ui->periodBox_2;
            theLineEdit = ui->ch2_samrate;
            break;
        case Chn3:
            thePeriodBox = ui->periodBox_3;
            theLineEdit = ui->ch3_samrate;
            break;
        case Chn4:
        case Chn45:
            thePeriodBox = ui->periodBox_4;
            theLineEdit = ui->ch4_samrate;
            break;
        case Chn5:
            thePeriodBox = ui->periodBox_5;
            theLineEdit = ui->ch5_samrate;
            break;
        case Chn6:
        case Chn67:
            thePeriodBox = ui->periodBox_6;
            theLineEdit = ui->ch6_samrate;
            break;
        case Chn7:
            thePeriodBox = ui->periodBox_7;
            theLineEdit = ui->ch7_samrate;
            break;
    }

    // Set the validator
    theLineEdit->setValidator(validator);
    index = thePeriodBox->currentIndex();

    if (theLineEdit->hasAcceptableInput())
    {
        long long tempLLong;
        QString str;

        // Need to ensure we limit the uSeconds to min 20us
        tempLLong = theLineEdit->text().toLongLong() * periodMicroSecondsMultiplier[index];

        if (index == indexUSeconds)
        {
            if (tempLLong < samRateUSecsMin)
            {
                tempLLong = samRateUSecsMin;
                theLineEdit->setText(strBuf.sprintf("%d", samRateUSecsMin));
                QMessageBox::information(this,
                                         "ADC App",
                                         str.sprintf("Ch%s's minimum sampling period is %d usecs. Updating to minimum value.",
                                                     PrvGetChStr(Ch,&strBuf)->toStdString().c_str(),
                                                     samRateUSecsMin
                                                     )
                                         );
            }
        }

        return tempLLong;
    }
    else
    {
        if (index == indexUSeconds)
        {
            theLineEdit->setText(strBuf.sprintf("%d", samRateUSecsMin));
        }
        else
        {
            theLineEdit->setText("1");
        }
    }

    return 0;
}

void MainWindow::on_Start_clicked()
{
    QString         tempStr;
    int             gain;
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

            gain = LTC185x_ChSetup_Enabled;
            if (ui->checkBox_10V_Ch_0->isChecked())  gain |= LTC185x_ChSetup_Gain;
            if (ui->checkBox_uni_Ch_0->isChecked()) gain |= LTC185x_ChSetup_UniBi;
            err = PrvSetChannelConfig(Chn01, gain, PrvGetLineEditValue(Chn0));
            if (err >= 0) startSampling++;
            err = PrvSetChannelConfig(Chn0, 0, 0);
            err = PrvSetChannelConfig(Chn1, 0, 0);
        }
        else
        {
            err = PrvSetChannelConfig(Chn01, 0, 0);

            if (ui->Ch0->isChecked())
            {
                gain = LTC185x_ChSetup_Enabled;
                if (ui->checkBox_10V_Ch_0->isChecked()) gain |= LTC185x_ChSetup_Gain;
                if (ui->checkBox_uni_Ch_0->isChecked()) gain |= LTC185x_ChSetup_UniBi;
                err = PrvSetChannelConfig(Chn0, LTC185x_ChSetup_Enabled|gain, PrvGetLineEditValue(Chn0));
                if (err >= 0) startSampling++;

            }
            else
            {
                err = PrvSetChannelConfig(Chn0, 0 , 0);
            }

            if (ui->Ch1->isChecked())
            {
                gain = LTC185x_ChSetup_Enabled;
                if (ui->checkBox_10V_Ch_1->isChecked()) gain |= LTC185x_ChSetup_Gain;
                if (ui->checkBox_uni_Ch_1->isChecked()) gain |= LTC185x_ChSetup_UniBi;
                err = PrvSetChannelConfig(Chn1, LTC185x_ChSetup_Enabled|gain, PrvGetLineEditValue(Chn1));
                if (err >= 0) startSampling++;
            }
            else
            {
                err = PrvSetChannelConfig(Chn1, 0 , 0);
            }
        }

        if (ui->Ch23->isChecked())
        {
            gain = LTC185x_ChSetup_Enabled;
            if (ui->checkBox_10V_Ch_2->isChecked()) gain |= LTC185x_ChSetup_Gain;
            if (ui->checkBox_uni_Ch_2->isChecked()) gain |= LTC185x_ChSetup_UniBi;
            err = PrvSetChannelConfig(Chn23, LTC185x_ChSetup_Enabled|gain, PrvGetLineEditValue(Chn2));
            if (err >= 0) startSampling++;

            err = PrvSetChannelConfig(Chn2, 0, 0);
            err = PrvSetChannelConfig(Chn3, 0, 0);
        }
        else
        {
            err = PrvSetChannelConfig(Chn23, 0, 0);

            if (ui->Ch2->isChecked())
            {
                gain = LTC185x_ChSetup_Enabled;
                if (ui->checkBox_10V_Ch_2->isChecked()) gain |= LTC185x_ChSetup_Gain;
                if (ui->checkBox_uni_Ch_2->isChecked()) gain |= LTC185x_ChSetup_UniBi;
                err = PrvSetChannelConfig(Chn2, LTC185x_ChSetup_Enabled|gain, PrvGetLineEditValue(Chn2));
                if (err >= 0) startSampling++;
            }
            else
            {
                err = PrvSetChannelConfig(Chn2, 0 , 0);
            }

            if (ui->Ch3->isChecked())
            {
                gain = LTC185x_ChSetup_Enabled;
                if (ui->checkBox_10V_Ch_3->isChecked()) gain |= LTC185x_ChSetup_Gain;
                if (ui->checkBox_uni_Ch_3->isChecked()) gain |= LTC185x_ChSetup_UniBi;
                err = PrvSetChannelConfig(Chn3, LTC185x_ChSetup_Enabled|gain, PrvGetLineEditValue(Chn3));
                if (err >= 0) startSampling++;
            }
            else
            {
                err = PrvSetChannelConfig(Chn3, 0 , 0);
            }
        }

        if (ui->Ch45->isChecked())
        {
            gain = LTC185x_ChSetup_Enabled;
            if (ui->checkBox_10V_Ch_4->isChecked()) gain |= LTC185x_ChSetup_Gain;
            if (ui->checkBox_uni_Ch_4->isChecked()) gain |= LTC185x_ChSetup_UniBi;
            err = PrvSetChannelConfig(Chn45, LTC185x_ChSetup_Enabled|gain, PrvGetLineEditValue(Chn4));
            if (err >= 0) startSampling++;

            err = PrvSetChannelConfig(Chn4, 0, 0);
            err = PrvSetChannelConfig(Chn5, 0, 0);
        }
        else
        {
            err = PrvSetChannelConfig(Chn45, 0, 0);

            if (ui->Ch4->isChecked())
            {
                gain = LTC185x_ChSetup_Enabled;
                if (ui->checkBox_10V_Ch_4->isChecked()) gain |= LTC185x_ChSetup_Gain;
                if (ui->checkBox_uni_Ch_4->isChecked()) gain |= LTC185x_ChSetup_UniBi;
                err = PrvSetChannelConfig(Chn4, LTC185x_ChSetup_Enabled|gain, PrvGetLineEditValue(Chn4));
                if (err >= 0) startSampling++;
            }
            else
            {
                err = PrvSetChannelConfig(Chn4, 0 , 0);
            }


            if (ui->Ch5->isChecked())
            {
                gain = LTC185x_ChSetup_Enabled;
                if (ui->checkBox_10V_Ch_5->isChecked()) gain |= LTC185x_ChSetup_Gain;
                if (ui->checkBox_uni_Ch_5->isChecked()) gain |= LTC185x_ChSetup_UniBi;
                err = PrvSetChannelConfig(Chn5, LTC185x_ChSetup_Enabled|gain, PrvGetLineEditValue(Chn5));
                if (err >= 0) startSampling++;
            }
            else
            {
                err = PrvSetChannelConfig(Chn5, 0 , 0);
            }
        }

        if (ui->Ch67->isChecked())
        {
            gain = LTC185x_ChSetup_Enabled;
            if (ui->checkBox_10V_Ch_6->isChecked()) gain |= LTC185x_ChSetup_Gain;
            if (ui->checkBox_uni_Ch_6->isChecked()) gain |= LTC185x_ChSetup_UniBi;
            err = PrvSetChannelConfig(Chn67, LTC185x_ChSetup_Enabled|gain, PrvGetLineEditValue(Chn6));
            if (err >= 0) startSampling++;

            err = PrvSetChannelConfig(Chn6, 0, 0);
            err = PrvSetChannelConfig(Chn7, 0, 0);
        }
        else
        {
            err = PrvSetChannelConfig(Chn67, 0, 0);

            if (ui->Ch6->isChecked())
            {
                gain = LTC185x_ChSetup_Enabled;
                if (ui->checkBox_10V_Ch_6->isChecked()) gain |= LTC185x_ChSetup_Gain;
                if (ui->checkBox_uni_Ch_6->isChecked()) gain |= LTC185x_ChSetup_UniBi;
                err = PrvSetChannelConfig(Chn6, LTC185x_ChSetup_Enabled|gain, PrvGetLineEditValue(Chn6));
                if (err >= 0) startSampling++;
            }
            else
            {
                err = PrvSetChannelConfig(Chn6, 0 , 0);
            }

            if (ui->Ch7->isChecked())
            {
                gain = LTC185x_ChSetup_Enabled;
                if (ui->checkBox_10V_Ch_7->isChecked()) gain |= LTC185x_ChSetup_Gain;
                if (ui->checkBox_uni_Ch_7->isChecked()) gain |= LTC185x_ChSetup_UniBi;
                err = PrvSetChannelConfig(Chn7, LTC185x_ChSetup_Enabled|gain, PrvGetLineEditValue(Chn7));
                if (err >= 0) startSampling++;
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
        else
        {
           QMessageBox::information(this, "ADC App", "No channels selected.");
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

    ui->checkBox_5V_Ch_1->setChecked(ui->checkBox_5V_Ch_0->isChecked());
    ui->checkBox_10V_Ch_1->setChecked(ui->checkBox_10V_Ch_0->isChecked());

    RESET_STATUS_TIMER;

//    QPainter painter (ui->TabDisplay);
 //   painter.drawLine(ui->Ch01->x(),ui->Ch01->y(), ui->Ch01->x(), ui->Ch01->y()+10);

}

void MainWindow::on_Ch23_clicked()
{
    strBuf.sprintf("Ch23 %s", (ui->Ch23->checkState()) ? "selected":"deselected");
    ui->status->setText(strBuf);
    RESET_STATUS_TIMER;

    ui->Ch2->setChecked(0);
    ui->Ch3->setChecked(0);

    ui->checkBox_5V_Ch_3->setChecked(ui->checkBox_5V_Ch_2->isChecked());
    ui->checkBox_10V_Ch_3->setChecked(ui->checkBox_10V_Ch_2->isChecked());

}

void MainWindow::on_Ch45_clicked()
{
    QString strBuf="";
    strBuf.sprintf("Ch45 %s", (ui->Ch45->checkState()) ? "selected":"deselected");
    ui->status->setText(strBuf);
    RESET_STATUS_TIMER;
    ui->Ch4->setChecked(0);
    ui->Ch5->setChecked(0);

    ui->checkBox_5V_Ch_5->setChecked(ui->checkBox_5V_Ch_4->isChecked());
    ui->checkBox_10V_Ch_5->setChecked(ui->checkBox_10V_Ch_4->isChecked());

}

void MainWindow::on_Ch67_clicked()
{
    QString strBuf="";
    strBuf.sprintf("Ch67 %s", (ui->Ch67->checkState()) ? "selected":"deselected");
    ui->status->setText(strBuf);
    RESET_STATUS_TIMER;

    ui->Ch6->setChecked(0);
    ui->Ch7->setChecked(0);

    ui->checkBox_5V_Ch_7->setChecked(ui->checkBox_5V_Ch_6->isChecked());
    ui->checkBox_10V_Ch_7->setChecked(ui->checkBox_10V_Ch_6->isChecked());
}


int MainWindow::PrvGetSamples(int Ch, unsigned short* buf, unsigned int *overun)
{
    ReadBufferData  RdBufDat;
    int             retVal=0;


    RdBufDat.ch = Ch;
    RdBufDat.buf = buf;
    RdBufDat.numSamples = ChMaxReadSamples;
    RdBufDat.overun = overun;

    gErr = ioctl(fd_ltc185x, MZIO_LTC185x_READ_BUFFER, &RdBufDat);
    if (gErr<0)  printf("Error reading Ch0 buffer %s\n", strerror(gErr));
    else retVal=gErr;

    if (*overun)
    {
        // If we have an overun situation, we need to restart the sampling
        strBuf.sprintf("!!! Overun !!!");
        ui->status->setText(strBuf);
        RESET_STATUS_TIMER;

        MainWindow::on_Stop_clicked();
//        MainWindow::on_Start_clicked();
        QMessageBox::information(this,
                                 "ADC App",
                                 strBuf.sprintf("Ch%s's buffer has overun. Please restart sampling.",
                                             PrvGetChStr(Ch,&strBuf)->toStdString().c_str()
                                             )
                                 );

    }

    return retVal;
}


int MainWindow::PrvWriteSamplesToFile(int Ch, QString filename, unsigned short* buf, int numSamples, int overun)
{
    QDateTime       dateTime(QDateTime::currentDateTime());
    QString         dateStr = dateTime.toString("yyyy-MM-dd,");
    QString         timeStr = dateTime.toString("hh:mm:ss,");
    int             i;

    QFile           file(filename);
    if (file.open(QIODevice::Append))
    {
        QTextStream str(&strBuf);
        QTextStream out(&file);

        qDebug() << "numSamples=" << numSamples;
        for (i=0;i<numSamples; i++)
        {
            ChConfig[Ch].periodCounter += ChConfig[Ch].periodMicroSecs;
            PrvCalculate_mV(Ch, buf[i]);
    //        str << dateStr << timeStr << ChConfig[Ch].periodCounter << "," << PrvCalculate_mV(Ch, buf[i]) << "," << overun << endl;
           // qDebug() << str.string()->toStdString().c_str();
           // out << str.string()->toStdString().c_str();
        }
        file.close();
        return 0;
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Ch01 failed to write to SD card");
        msgBox.exec();
        return file.error();
    }


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
                QString         filename;
                unsigned int    overun=0;
                int             numSamples;
                int             Ch;
                unsigned short  *dataPtr;

                // Setup the channels
                if (ui->Ch01->isChecked())
                {
                    Ch = Chn01;
                    dataPtr = ChConfig[Ch].RdBufPtr;
                    numSamples = PrvGetSamples(Ch, dataPtr, &overun);
                    if (numSamples)
                    {
//                        ui->ChVal_0->setText(strBuf);
                        ui->ChVal_1->setText("");
                        qDebug() << strBuf;

                        if (ui->log_Ch_0->isChecked() || ui->log_Ch_1->isChecked())
                        {
                            filename.sprintf("%s/%s", StoreDir, ChConfig[Ch].filename);
                            PrvWriteSamplesToFile(Ch, filename, dataPtr, numSamples, overun);
                        }
                    }
                }
                else
                {
                    if (ui->Ch0->isChecked())
                    {
                        Ch = Chn0;
                        dataPtr = ChConfig[Ch].RdBufPtr;
                        numSamples = PrvGetSamples(Ch, dataPtr, &overun);
                        if (numSamples)
                        {
                            if (ui->log_Ch_0->isChecked())
                            {
                                filename.sprintf("%s/%s", StoreDir, ChConfig[Ch].filename);
                                PrvWriteSamplesToFile(Ch, filename, dataPtr, numSamples, overun);
                            }
                        }
                    }

                    if (ui->Ch1->isChecked())
                    {
                        Ch = Chn1;
                        dataPtr = ChConfig[Ch].RdBufPtr;
                        numSamples = PrvGetSamples(Ch, dataPtr, &overun);
                        if (numSamples)
                        {
                            if (ui->log_Ch_1->isChecked())
                            {
                                filename.sprintf("%s/%s", StoreDir, ChConfig[Ch].filename);
                                PrvWriteSamplesToFile(Ch, filename, dataPtr, numSamples, overun);
                            }
                        }
                    }
                }

                if (ui->Ch23->isChecked())
                {
                    Ch = Chn23;
                    dataPtr = ChConfig[Ch].RdBufPtr;
                    numSamples = PrvGetSamples(Ch, dataPtr, &overun);
                    if (numSamples)
                    {
                        if (ui->log_Ch_2->isChecked() || ui->log_Ch_3->isChecked())
                        {
                            filename.sprintf("%s/%s", StoreDir, ChConfig[Ch].filename);
                            PrvWriteSamplesToFile(Ch, filename, dataPtr, numSamples, overun);
                        }
                    }
                }
                else
                {
                    if (ui->Ch2->isChecked())
                    {
                        Ch = Chn2;
                        dataPtr = ChConfig[Ch].RdBufPtr;
                        numSamples = PrvGetSamples(Ch, dataPtr, &overun);
                        if (numSamples)
                        {
                            if (ui->log_Ch_2->isChecked())
                            {
                                filename.sprintf("%s/%s", StoreDir, ChConfig[Ch].filename);
                                PrvWriteSamplesToFile(Ch, filename, dataPtr, numSamples, overun);
                            }
                        }
                    }

                    if (ui->Ch3->isChecked())
                    {
                        Ch = Chn3;
                        dataPtr = ChConfig[Ch].RdBufPtr;
                        numSamples = PrvGetSamples(Ch, dataPtr, &overun);
                        if (numSamples)
                        {
                            if (ui->log_Ch_3->isChecked())
                            {
                                filename.sprintf("%s/%s", StoreDir, ChConfig[Ch].filename);
                                PrvWriteSamplesToFile(Ch, filename, dataPtr, numSamples, overun);
                            }
                        }
                    }
                }


                if (ui->Ch45->isChecked())
                {
                    Ch = Chn45;
                    dataPtr = ChConfig[Ch].RdBufPtr;
                    numSamples = PrvGetSamples(Ch, dataPtr, &overun);
                    if (numSamples)
                    {
                        if (ui->log_Ch_4->isChecked() || ui->log_Ch_5->isChecked())
                        {
                            filename.sprintf("%s/%s", StoreDir, ChConfig[Ch].filename);
                            PrvWriteSamplesToFile(Ch, filename, dataPtr, numSamples, overun);
                        }
                    }
                }
                else
                {
                    if (ui->Ch4->isChecked())
                    {
                        Ch = Chn4;
                        dataPtr = ChConfig[Ch].RdBufPtr;
                        numSamples = PrvGetSamples(Ch, dataPtr, &overun);
                        if (numSamples)
                        {
                            if (ui->log_Ch_4->isChecked())
                            {
                                filename.sprintf("%s/%s", StoreDir, ChConfig[Ch].filename);
                                PrvWriteSamplesToFile(Ch, filename, dataPtr, numSamples, overun);
                            }
                        }
                    }

                    if (ui->Ch5->isChecked())
                    {
                        Ch = Chn5;
                        dataPtr = ChConfig[Ch].RdBufPtr;
                        numSamples = PrvGetSamples(Ch, dataPtr, &overun);
                        if (numSamples)
                        {
                            if (ui->log_Ch_5->isChecked())
                            {
                                filename.sprintf("%s/%s", StoreDir, ChConfig[Ch].filename);
                                PrvWriteSamplesToFile(Ch, filename, dataPtr, numSamples, overun);
                            }
                        }
                    }
                }


                if (ui->Ch67->isChecked())
                {
                    Ch = Chn67;
                    dataPtr = ChConfig[Ch].RdBufPtr;
                    numSamples = PrvGetSamples(Ch, dataPtr, &overun);
                    if (numSamples)
                    {
                        if (ui->log_Ch_6->isChecked() || ui->log_Ch_7->isChecked())
                        {
                            filename.sprintf("%s/%s", StoreDir, ChConfig[Ch].filename);
                            PrvWriteSamplesToFile(Ch, filename, dataPtr, numSamples, overun);
                        }
                    }
                }
                else
                {
                    if (ui->Ch6->isChecked())
                    {
                        Ch = Chn6;
                        dataPtr = ChConfig[Ch].RdBufPtr;
                        numSamples = PrvGetSamples(Ch, dataPtr, &overun);
                        if (numSamples)
                        {
                            if (ui->log_Ch_6->isChecked())
                            {
                                filename.sprintf("%s/%s", StoreDir, ChConfig[Ch].filename);
                                PrvWriteSamplesToFile(Ch, filename, dataPtr, numSamples, overun);
                            }
                        }
                    }

                    if (ui->Ch7->isChecked())
                    {
                        Ch = Chn7;
                        dataPtr = ChConfig[Ch].RdBufPtr;
                        numSamples = PrvGetSamples(Ch, dataPtr, &overun);
                        if (numSamples)
                        {
                            if (ui->log_Ch_7->isChecked())
                            {
                                filename.sprintf("%s/%s", StoreDir, ChConfig[Ch].filename);
                                PrvWriteSamplesToFile(Ch, filename, dataPtr, numSamples, overun);
                            }
                        }
                    }
                }
            }

            RESET_READ_TIMER;
        }
    }
    fflush(stdout);

    // Update the shown time every minute
    if (QTime::currentTime().minute() > minutes)
    {
        ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
        minutes=QTime::currentTime().minute();
    }
}

void MainWindow::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    QTextStream  str(&strBuf);
    str << "date -s " << dateTime.toString("MMddhhmmyyyy") << endl;
    qDebug() << strBuf.toStdString().c_str();
    system(strBuf.toStdString().c_str());
    system("hwclock -w");
}



void MainWindow::on_checkBox_5V10V_clicked()
{
    QCheckBox *checkBox = (QCheckBox*) sender();
    QCheckBox *H5, *L5, *H10, *L10;
    QString name = checkBox->objectName();

    L5 = ui->checkBox_5V_Ch_0;
    H5 = ui->checkBox_5V_Ch_1;
    L10 = ui->checkBox_10V_Ch_0;
    H10 = ui->checkBox_10V_Ch_1;
    if (name == L5->objectName())   L10->setChecked (!(L5->isChecked()));
    if (name == H5->objectName())   H10->setChecked (!(H5->isChecked()));
    if (name == L10->objectName())  L5->setChecked  (!(L10->isChecked()));
    if (name == H10->objectName())  H5->setChecked  (!(H10->isChecked()));
    if (ui->Ch01->isChecked())
    {
        H5->setChecked(L5->isChecked());
        H10->setChecked(L10->isChecked());
    }

    L5 = ui->checkBox_5V_Ch_0;
    H5 = ui->checkBox_5V_Ch_1;
    L10 = ui->checkBox_10V_Ch_0;
    H10 = ui->checkBox_10V_Ch_1;
    if (name == L5->objectName())   L10->setChecked (!(L5->isChecked()));
    if (name == H5->objectName())   H10->setChecked (!(H5->isChecked()));
    if (name == L10->objectName())  L5->setChecked  (!(L10->isChecked()));
    if (name == H10->objectName())  H5->setChecked  (!(H10->isChecked()));
    if (ui->Ch01->isChecked())
    {
        H5->setChecked(L5->isChecked());
        H10->setChecked(L10->isChecked());
    }

    L5 = ui->checkBox_5V_Ch_2;
    H5 = ui->checkBox_5V_Ch_3;
    L10 = ui->checkBox_10V_Ch_2;
    H10 = ui->checkBox_10V_Ch_3;
    if (name == L5->objectName())   L10->setChecked (!(L5->isChecked()));
    if (name == H5->objectName())   H10->setChecked (!(H5->isChecked()));
    if (name == L10->objectName())  L5->setChecked  (!(L10->isChecked()));
    if (name == H10->objectName())  H5->setChecked  (!(H10->isChecked()));
    if (ui->Ch23->isChecked())
    {
        H5->setChecked(L5->isChecked());
        H10->setChecked(L10->isChecked());
    }

    L5 = ui->checkBox_5V_Ch_4;
    H5 = ui->checkBox_5V_Ch_5;
    L10 = ui->checkBox_10V_Ch_4;
    H10 = ui->checkBox_10V_Ch_5;
    if (name == L5->objectName())   L10->setChecked (!(L5->isChecked()));
    if (name == H5->objectName())   H10->setChecked (!(H5->isChecked()));
    if (name == L10->objectName())  L5->setChecked  (!(L10->isChecked()));
    if (name == H10->objectName())  H5->setChecked  (!(H10->isChecked()));
    if (ui->Ch45->isChecked())
    {
        H5->setChecked(L5->isChecked());
        H10->setChecked(L10->isChecked());
    }

    L5 = ui->checkBox_5V_Ch_6;
    H5 = ui->checkBox_5V_Ch_7;
    L10 = ui->checkBox_10V_Ch_6;
    H10 = ui->checkBox_10V_Ch_7;
    if (name == L5->objectName())   L10->setChecked (!(L5->isChecked()));
    if (name == H5->objectName())   H10->setChecked (!(H5->isChecked()));
    if (name == L10->objectName())  L5->setChecked  (!(L10->isChecked()));
    if (name == H10->objectName())  H5->setChecked  (!(H10->isChecked()));
    if (ui->Ch67->isChecked())
    {
        H5->setChecked(L5->isChecked());
        H10->setChecked(L10->isChecked());
    }

}

void MainWindow::on_samrate_editingFinished()
{
    QLineEdit *lineEdit = (QLineEdit*) sender();
    QValidator *validator = new QIntValidator(1,10000, this);

    qDebug() << "editingFinished()" << lineEdit->objectName() << lineEdit->text();

    // Set validator for the sample rate line edits
    lineEdit->setValidator(validator);
    if (lineEdit->hasAcceptableInput() == false)
    {
//        QMessageBox::information(this, "ADC App", "Incorrect period value.");
 //       lineEdit->setText("1");
        qDebug() << " invalid";
    }
    else
    {
        qDebug() << "valid " << lineEdit->hasAcceptableInput();
    }


}

void MainWindow::on_Setup_currentChanged(int index)
{
    int width, height, x, y;
    QPoint p1, p2;

    qDebug() << "on_Setup_currentChanged " << index;

    switch (index)
    {
    case 0:
        // Time and settings
        qDebug() << "Time";
        break;

    case 1:
        // Channel setup
        qDebug() << "Channel";
        break;


    case 2:
        // Data
        qDebug() << "Data";
        break;

    case 3:
        // Graph
        QPainter painter(this);

        qDebug() << "Tab Graph";

        width = ui->TabDisplay->size().width();
        height = ui->TabDisplay->size().height();
        x = 1;//ui->TabDisplay->x;
        y = 1;//ui->TabDisplay->y;

        p1.setX(x);
        p1.setY(y);
        p2.setX(x+width);
        p2.setY(y+height);
        painter.drawLine(p1, p2);
        break;
    }
}


