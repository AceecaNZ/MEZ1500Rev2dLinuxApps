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

#define TIMER_PERIOD            100                         // msecs
#define RESET_STATUS_TIMER      statusEraseCount=50       // 5s
#define RESET_READ_TIMER        sample_timer_count=5        // 500ms
#define RESET_STATUS_CYCLER     statusCycler=4
// --------------------------------------------------------------------
// Internal Functions
// --------------------------------------------------------------------
// --------------------------------------------------------------------


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    int i;
    int err;

    showFullScreen();

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
    system("rmmod MEZ1500_mzio");

    system("modprobe MEZ1500_mzio_ltc185x");
    system("modprobe MEZ1500_mzio");

    ui->setupUi(this);

    // Pop up keyboard
    lineEditkeyboard = new Keyboard();
    connect(ui->samrate_ch_0,SIGNAL(selectionChanged()),this,SLOT(run_keyboard_lineEdit()));
    connect(ui->samrate_ch_1,SIGNAL(selectionChanged()),this,SLOT(run_keyboard_lineEdit()));
    connect(ui->samrate_ch_2,SIGNAL(selectionChanged()),this,SLOT(run_keyboard_lineEdit()));
    connect(ui->samrate_ch_3,SIGNAL(selectionChanged()),this,SLOT(run_keyboard_lineEdit()));
    connect(ui->samrate_ch_4,SIGNAL(selectionChanged()),this,SLOT(run_keyboard_lineEdit()));
    connect(ui->samrate_ch_5,SIGNAL(selectionChanged()),this,SLOT(run_keyboard_lineEdit()));
    connect(ui->samrate_ch_6,SIGNAL(selectionChanged()),this,SLOT(run_keyboard_lineEdit()));
    connect(ui->samrate_ch_7,SIGNAL(selectionChanged()),this,SLOT(run_keyboard_lineEdit()));

    count       = 0;
    isSampling  = 0;
    fd_ltc185x  = 0;
    fd_mzio     = 0;
    fd_ltc185x  = open("/dev/ltc185x", O_RDWR);
    if (fd_ltc185x < 0)
        printf("Failed to open MZIO LTC185x module\n");
    else
        printf("Openned MZIO LTC185x module\n");

    fd_mzio  = open("/dev/mzio", O_RDWR);
    if (fd_ltc185x < 0)
        printf("Failed to open MZIO module\n");
    else
        printf("Openned MZIO module\n");

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_timer_event()));
    timer->start(TIMER_PERIOD);

    connect(ui->samrate_ch_0, SIGNAL(editingFinished()), this, SLOT(on_samrate_editingFinished()));
    connect(ui->samrate_ch_1, SIGNAL(editingFinished()), this, SLOT(on_samrate_editingFinished()));
    connect(ui->samrate_ch_2, SIGNAL(editingFinished()), this, SLOT(on_samrate_editingFinished()));
    connect(ui->samrate_ch_3, SIGNAL(editingFinished()), this, SLOT(on_samrate_editingFinished()));
    connect(ui->samrate_ch_4, SIGNAL(editingFinished()), this, SLOT(on_samrate_editingFinished()));
    connect(ui->samrate_ch_5, SIGNAL(editingFinished()), this, SLOT(on_samrate_editingFinished()));
    connect(ui->samrate_ch_6, SIGNAL(editingFinished()), this, SLOT(on_samrate_editingFinished()));
    connect(ui->samrate_ch_7, SIGNAL(editingFinished()), this, SLOT(on_samrate_editingFinished()));


    connect(ui->periodBox_ch_0, SIGNAL(activated(int)), this, SLOT(on_periodBox_activated(int)));
    connect(ui->periodBox_ch_1, SIGNAL(activated(int)), this, SLOT(on_periodBox_activated(int)));
    connect(ui->periodBox_ch_2, SIGNAL(activated(int)), this, SLOT(on_periodBox_activated(int)));
    connect(ui->periodBox_ch_3, SIGNAL(activated(int)), this, SLOT(on_periodBox_activated(int)));
    connect(ui->periodBox_ch_4, SIGNAL(activated(int)), this, SLOT(on_periodBox_activated(int)));
    connect(ui->periodBox_ch_5, SIGNAL(activated(int)), this, SLOT(on_periodBox_activated(int)));
    connect(ui->periodBox_ch_6, SIGNAL(activated(int)), this, SLOT(on_periodBox_activated(int)));
    connect(ui->periodBox_ch_7, SIGNAL(activated(int)), this, SLOT(on_periodBox_activated(int)));

    connect(ui->log_Ch_0, SIGNAL(clicked()), this, SLOT(on_logcheckBox_clicked()));
    connect(ui->log_Ch_1, SIGNAL(clicked()), this, SLOT(on_logcheckBox_clicked()));
    connect(ui->log_Ch_2, SIGNAL(clicked()), this, SLOT(on_logcheckBox_clicked()));
    connect(ui->log_Ch_3, SIGNAL(clicked()), this, SLOT(on_logcheckBox_clicked()));
    connect(ui->log_Ch_4, SIGNAL(clicked()), this, SLOT(on_logcheckBox_clicked()));
    connect(ui->log_Ch_5, SIGNAL(clicked()), this, SLOT(on_logcheckBox_clicked()));
    connect(ui->log_Ch_6, SIGNAL(clicked()), this, SLOT(on_logcheckBox_clicked()));
    connect(ui->log_Ch_7, SIGNAL(clicked()), this, SLOT(on_logcheckBox_clicked()));

    // Load prefs
    err = PrvLoadPreferences();
    if (err)
    {
        printf("Failed to load preferences, setting to defaults ... \n");

        // Set all channels to be enabled
        ChConfig[0].enabled = 1;
        ChConfig[1].enabled = 1;
        ChConfig[2].enabled = 1;
        ChConfig[3].enabled = 1;
        ChConfig[4].enabled = 1;
        ChConfig[5].enabled = 1;
        ChConfig[6].enabled = 1;
        ChConfig[7].enabled = 1;

        // Init all the sampling rate values to 1s
        i = 1;
        ui->samrate_ch_0->setText(strBuf.sprintf("%u", 1));
        ui->samrate_ch_1->setText(strBuf.sprintf("%u", 1));
        ui->samrate_ch_2->setText(strBuf.sprintf("%u", 1));
        ui->samrate_ch_3->setText(strBuf.sprintf("%u", 1));
        ui->samrate_ch_4->setText(strBuf.sprintf("%u", 1));
        ui->samrate_ch_5->setText(strBuf.sprintf("%u", 1));
        ui->samrate_ch_6->setText(strBuf.sprintf("%u", 1));
        ui->samrate_ch_7->setText(strBuf.sprintf("%u", 1));

        ChConfig[0].samplePeriodValue = 1;
        ChConfig[1].samplePeriodValue = 1;
        ChConfig[2].samplePeriodValue = 1;
        ChConfig[3].samplePeriodValue = 1;
        ChConfig[4].samplePeriodValue = 1;
        ChConfig[5].samplePeriodValue = 1;
        ChConfig[6].samplePeriodValue = 1;
        ChConfig[7].samplePeriodValue = 1;

        // Init the units to second
        ui->periodBox_ch_0->setCurrentIndex(indexSeconds);
        ui->periodBox_ch_1->setCurrentIndex(indexSeconds);
        ui->periodBox_ch_2->setCurrentIndex(indexSeconds);
        ui->periodBox_ch_3->setCurrentIndex(indexSeconds);
        ui->periodBox_ch_4->setCurrentIndex(indexSeconds);
        ui->periodBox_ch_5->setCurrentIndex(indexSeconds);
        ui->periodBox_ch_6->setCurrentIndex(indexSeconds);
        ui->periodBox_ch_7->setCurrentIndex(indexSeconds);

        ChConfig[0].samplePeriodUnitIndex = indexSeconds;
        ChConfig[1].samplePeriodUnitIndex = indexSeconds;
        ChConfig[2].samplePeriodUnitIndex = indexSeconds;
        ChConfig[3].samplePeriodUnitIndex = indexSeconds;
        ChConfig[4].samplePeriodUnitIndex = indexSeconds;
        ChConfig[5].samplePeriodUnitIndex = indexSeconds;
        ChConfig[6].samplePeriodUnitIndex = indexSeconds;
        ChConfig[7].samplePeriodUnitIndex = indexSeconds;

        // Init all channels to log
        ui->log_Ch_0->setChecked(1);
        ui->log_Ch_1->setChecked(1);
        ui->log_Ch_2->setChecked(1);
        ui->log_Ch_3->setChecked(1);
        ui->log_Ch_4->setChecked(1);
        ui->log_Ch_5->setChecked(1);
        ui->log_Ch_6->setChecked(1);
        ui->log_Ch_7->setChecked(1);

        ChConfig[0].doLog = 1;
        ChConfig[1].doLog = 1;
        ChConfig[2].doLog = 1;
        ChConfig[3].doLog = 1;
        ChConfig[4].doLog = 1;
        ChConfig[5].doLog = 1;
        ChConfig[6].doLog = 1;
        ChConfig[7].doLog = 1;

        // Set all channels to bipolar
        ChConfig[0].unipolar = 0;
        ChConfig[1].unipolar = 0;
        ChConfig[2].unipolar = 0;
        ChConfig[3].unipolar = 0;
        ChConfig[4].unipolar = 0;
        ChConfig[5].unipolar = 0;
        ChConfig[6].unipolar = 0;
        ChConfig[7].unipolar = 0;

        // Set all channels to gain 10V
        ChConfig[0].gain = 1;
        ChConfig[1].gain = 1;
        ChConfig[2].gain = 1;
        ChConfig[3].gain = 1;
        ChConfig[4].gain = 1;
        ChConfig[5].gain = 1;
        ChConfig[6].gain = 1;
        ChConfig[7].gain = 1;
    }
    else
    {
        // Init the enable checkboxes
        ui->select_ch_0->setChecked(ChConfig[0].enabled);
        ui->select_ch_1->setChecked(ChConfig[1].enabled);
        ui->select_ch_2->setChecked(ChConfig[2].enabled);
        ui->select_ch_3->setChecked(ChConfig[3].enabled);
        ui->select_ch_4->setChecked(ChConfig[4].enabled);
        ui->select_ch_5->setChecked(ChConfig[5].enabled);
        ui->select_ch_6->setChecked(ChConfig[6].enabled);
        ui->select_ch_7->setChecked(ChConfig[7].enabled);

        // Init all the sampling rate values to saved ones
        ui->samrate_ch_0->setText(strBuf.sprintf("%u", ChConfig[0].samplePeriodValue));
        ui->samrate_ch_1->setText(strBuf.sprintf("%u", ChConfig[1].samplePeriodValue));
        ui->samrate_ch_2->setText(strBuf.sprintf("%u", ChConfig[2].samplePeriodValue));
        ui->samrate_ch_3->setText(strBuf.sprintf("%u", ChConfig[3].samplePeriodValue));
        ui->samrate_ch_4->setText(strBuf.sprintf("%u", ChConfig[4].samplePeriodValue));
        ui->samrate_ch_5->setText(strBuf.sprintf("%u", ChConfig[5].samplePeriodValue));
        ui->samrate_ch_6->setText(strBuf.sprintf("%u", ChConfig[6].samplePeriodValue));
        ui->samrate_ch_7->setText(strBuf.sprintf("%u", ChConfig[7].samplePeriodValue));

        // Init the units
        ui->periodBox_ch_0->setCurrentIndex(ChConfig[0].samplePeriodUnitIndex);
        ui->periodBox_ch_1->setCurrentIndex(ChConfig[1].samplePeriodUnitIndex);
        ui->periodBox_ch_2->setCurrentIndex(ChConfig[2].samplePeriodUnitIndex);
        ui->periodBox_ch_3->setCurrentIndex(ChConfig[3].samplePeriodUnitIndex);
        ui->periodBox_ch_4->setCurrentIndex(ChConfig[4].samplePeriodUnitIndex);
        ui->periodBox_ch_5->setCurrentIndex(ChConfig[5].samplePeriodUnitIndex);
        ui->periodBox_ch_6->setCurrentIndex(ChConfig[6].samplePeriodUnitIndex);
        ui->periodBox_ch_7->setCurrentIndex(ChConfig[7].samplePeriodUnitIndex);

        // Init the logs
        ui->log_Ch_0->setChecked(ChConfig[0].doLog);
        ui->log_Ch_1->setChecked(ChConfig[1].doLog);
        ui->log_Ch_2->setChecked(ChConfig[2].doLog);
        ui->log_Ch_3->setChecked(ChConfig[3].doLog);
        ui->log_Ch_4->setChecked(ChConfig[4].doLog);
        ui->log_Ch_5->setChecked(ChConfig[5].doLog);
        ui->log_Ch_6->setChecked(ChConfig[6].doLog);
        ui->log_Ch_7->setChecked(ChConfig[7].doLog);
    }

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    minutes=QTime::currentTime().minute();

    fflush(stdout);

    MainWindow::on_Stop_clicked();

    ui->status->setText(strBuf.sprintf("ADC Application %s", versionString));
    RESET_STATUS_TIMER;
    RESET_READ_TIMER;
}

MainWindow::~MainWindow()
{
    delete  ui;
    int     err;

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

    // Unload the MZIO driver
    system("rmmod MEZ1500_mzio_ltc185x");
    system("rmmod MEZ1500_mzio");

    if (RdBuf) free(RdBuf);

    ::close (fd_ltc185x);
}

int MainWindow::PrvLoadPreferences()
{
    QFile               file(strBuf.sprintf("%s/%s", StoreDir, AppPrefsFile));
    QXmlStreamReader    rxml;
    int                 ch;

    printf("PrvLoadPreferences\n");

    rxml.setDevice((&file));
    rxml.readNext();

    if (file.open(QIODevice::ReadOnly))
    {
        qDebug() << ">> >> 1 << <<";

        while(!rxml.atEnd())
        {
            if(rxml.isStartElement())
            {
                if(rxml.name() == "ADCAppPrefs")
                {
                    qDebug() << rxml.name();
                    rxml.readNext();
                }
                else if (rxml.isCharacters())
                {
                    qDebug() << rxml.name();
                    rxml.readNext();
                }
                else if (rxml.isEndElement())
                {
                    rxml.readNext();
                }
                else if (rxml.isStartElement())
                {
                    while (!rxml.atEnd())
                    {
                        if (rxml.isEndElement())
                        {
                            rxml.readNext();
                            break;
                        }
                        else if (rxml.isCharacters())
                        {
                            rxml.readNext();
                        }
                        else if (rxml.isStartElement())
                        {
                            while (!rxml.atEnd())
                            {
                                if (rxml.isEndElement())
                                {
                                    rxml.readNext();
                                    break;
                                }
                                else if (rxml.isCharacters())
                                {
                                    rxml.readNext();
                                }
                                else if (rxml.name() == "ch")
                                {
                                    ch=rxml.readElementText().toInt();
                                    qDebug() << "ch=" << ch;
                                    rxml.readNext();
                                }
                                else if (rxml.name() == "enabled")
                                {
                                    ChConfig[ch].enabled=rxml.readElementText().toInt();
                                    qDebug() << "enabled=" << ChConfig[ch].enabled;
                                    rxml.readNext();
                                }
                                else if (rxml.name() == "periodUnit")
                                {
                                    ChConfig[ch].samplePeriodUnitIndex=rxml.readElementText().toInt();
                                    qDebug() << "samplePeriodUnitIndex=" << ChConfig[ch].samplePeriodUnitIndex;
                                    rxml.readNext();
                                }
                                else if (rxml.name() == "periodValue")
                                {
                                    ChConfig[ch].samplePeriodValue=rxml.readElementText().toInt();
                                    qDebug() << "samplePeriodValue=" << ChConfig[ch].samplePeriodValue;
                                    rxml.readNext();
                                }
                                else if (rxml.name() == "doLog")
                                {
                                    ChConfig[ch].doLog=rxml.readElementText().toInt();
                                    qDebug() << "doLog=" << ChConfig[ch].doLog;
                                    rxml.readNext();
                                }
                                else if (rxml.name() == "unipolar")
                                {
                                    ChConfig[ch].unipolar=rxml.readElementText().toInt();
                                    qDebug() << "unipolar=" << ChConfig[ch].unipolar;
                                    rxml.readNext();
                                }
                                else if (rxml.name() == "gain")
                                {
                                    ChConfig[ch].gain=rxml.readElementText().toInt();
                                    qDebug() << "gain=" << ChConfig[ch].gain;
                                    rxml.readNext();
                                }
                                else
                                {
                                    rxml.readNext();
                                }
                            }
                        }
                    }
                } else
                {
                    rxml.readNext();
                }
            }
            else
            {
                rxml.readNext();
            }

            if (rxml.hasError())
            {
                qDebug() << "Read XML error" <<  rxml.errorString();

            }
        }
        return 0;
    }
    else
    {
        return -1;
    }
}

int MainWindow::PrvSavePreferences()
{
    QFile           file(strBuf.sprintf("%s/%s", StoreDir, AppPrefsFile));
    int             ch;

    printf("PrvSavePreferences");

    if (file.open(QIODevice::WriteOnly))
    {
        // Write contents to file
        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("ADCAppPrefs");

        for (ch=0; ch<=ChnMax; ch++)
        {
            xmlWriter.writeStartElement(strBuf.sprintf("Ch%d", ch));
            xmlWriter.writeTextElement("ch", strBuf.sprintf("%d",ch));
            xmlWriter.writeTextElement("enabled", strBuf.sprintf("%d",ChConfig[ch].enabled));
            xmlWriter.writeTextElement("periodUnit", strBuf.sprintf("%d",ChConfig[ch].samplePeriodUnitIndex));
            xmlWriter.writeTextElement("periodValue", strBuf.sprintf("%d",ChConfig[ch].samplePeriodValue));
            xmlWriter.writeTextElement("doLog", strBuf.sprintf("%d",ChConfig[ch].doLog));
            xmlWriter.writeTextElement("unipolar", strBuf.sprintf("%d",ChConfig[ch].unipolar));
            xmlWriter.writeTextElement("gain", strBuf.sprintf("%d",ChConfig[ch].gain));
            xmlWriter.writeEndElement();
        }

        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
        file.close();
        return 0;
    }
    else
    {
        return -1;
    }
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

int MainWindow::PrvCalculateMultiplier(int gain, int unipolar)
{
		// The multiplier result is in uV
    // Gain=1 10V is selected, otherwise assume 5V is selected
    if (!gain  && unipolar)    return 	(1000000 * 5) 	/ 65535;
    if (!gain  && !unipolar)   return 	(1000000 * 10)	/ 65535;
    if (gain && unipolar)      return 	(1000000 * 10)	/ 65535;
    if (gain && !unipolar)     return	(1000000 * 20)	/ 65535;
    return 0;
}

int MainWindow::PrvCalculate_mV(int Ch, short data)
{
    int retVal;
    double d;

    if (ChConfig[Ch].unipolar)
    {
        retVal = (int) ((unsigned short) data * ChConfig[Ch].multiplier) / 1000;
        //strBuf.sprintf("Ch%s=%dmV uni 0x%x",
        //              PrvGetChStr(Ch, &strBuf)->toStdString().c_str(),
        //              retVal,
        //              data);
    }
    else
    {
        retVal =(int) (data * ChConfig[Ch].multiplier) / 1000;
        d = (double)((data * 5) / 65535);

        //strBuf.sprintf("Ch%s=%dmV bi 0x%x %ld %0.3fVolts",
        //              PrvGetChStr(Ch, &strBuf)->toStdString().c_str(),
        //               retVal,
        //               data,
        //               data*ChConfig[Ch].multiplier/1000,
        //               d);
    }

    // qDebug() << strBuf;
    return retVal;
}


int MainWindow::PrvSetChannelConfig(int Ch, unsigned int config, unsigned long long period)
{
    ChConfigDataType    ChConfigData;

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

    ChConfig[Ch].periodMicroSecs = ChConfigData.periodUSecs;

    switch (Ch)
    {
        case Chn0:
            sprintf(ChConfig[Ch].filename, "%s", CH0File);
            sprintf(ChConfig[Ch].chNameStr, "Ch0");
            ChConfig[Ch].RdBufPtr 	= RdBuf->Ch0Buf;
            ChConfig[Ch].unipolar 	= 0;
            ChConfig[Ch].gain 		= 1;
            ChConfig[Ch].doLog 		= ui->log_Ch_0->isChecked();
            ChConfig[Ch].multiplier	= PrvCalculateMultiplier(ChConfig[Ch].gain, ChConfig[Ch].unipolar);
            break;

        case Chn1:
            sprintf(ChConfig[Ch].filename, "%s", CH1File);
            sprintf(ChConfig[Ch].chNameStr, "Ch1");
            ChConfig[Ch].RdBufPtr   = RdBuf->Ch1Buf;
            ChConfig[Ch].unipolar 	= 0;
            ChConfig[Ch].gain 		= 1;
            ChConfig[Ch].doLog 		= ui->log_Ch_1->isChecked();
            ChConfig[Ch].multiplier	= PrvCalculateMultiplier(ChConfig[Ch].gain, ChConfig[Ch].unipolar);
            break;
        case Chn2:
            sprintf(ChConfig[Ch].filename, "%s", CH2File);
            sprintf(ChConfig[Ch].chNameStr, "Ch2");
            ChConfig[Ch].RdBufPtr   = RdBuf->Ch2Buf;
            ChConfig[Ch].unipolar 	= 0;
            ChConfig[Ch].gain 		= 1;
            ChConfig[Ch].doLog 		= ui->log_Ch_2->isChecked();
            ChConfig[Ch].multiplier	= PrvCalculateMultiplier(ChConfig[Ch].gain, ChConfig[Ch].unipolar);
            break;
        case Chn3:
            sprintf(ChConfig[Ch].filename, "%s", CH3File);
            sprintf(ChConfig[Ch].chNameStr, "Ch3");
            ChConfig[Ch].RdBufPtr   = RdBuf->Ch3Buf;
            ChConfig[Ch].unipolar 	= 0;
            ChConfig[Ch].gain 		= 1;
            ChConfig[Ch].doLog 		= ui->log_Ch_3->isChecked();
            ChConfig[Ch].multiplier	= PrvCalculateMultiplier(ChConfig[Ch].gain, ChConfig[Ch].unipolar);
            break;
        case Chn4:
            sprintf(ChConfig[Ch].filename, "%s", CH4File);
            sprintf(ChConfig[Ch].chNameStr, "Ch4");
            ChConfig[Ch].RdBufPtr = RdBuf->Ch4Buf;
            ChConfig[Ch].unipolar 	= 0;
            ChConfig[Ch].gain 		= 1;
            ChConfig[Ch].doLog 		= ui->log_Ch_4->isChecked();
            ChConfig[Ch].multiplier	= PrvCalculateMultiplier(ChConfig[Ch].gain, ChConfig[Ch].unipolar);
            break;
        case Chn5:
            sprintf(ChConfig[Ch].filename, "%s", CH5File);
            sprintf(ChConfig[Ch].chNameStr, "Ch5");
            ChConfig[Ch].RdBufPtr   = RdBuf->Ch5Buf;
            ChConfig[Ch].unipolar 	= 0;
            ChConfig[Ch].gain 		= 1;
            ChConfig[Ch].doLog 		= ui->log_Ch_5->isChecked();
            ChConfig[Ch].multiplier	= PrvCalculateMultiplier(ChConfig[Ch].gain, ChConfig[Ch].unipolar);
            break;
        case Chn6:
            sprintf(ChConfig[Ch].filename, "%s", CH6File);
            sprintf(ChConfig[Ch].chNameStr, "Ch6");
            ChConfig[Ch].RdBufPtr   = RdBuf->Ch6Buf;
            ChConfig[Ch].unipolar 	= 0;
            ChConfig[Ch].gain 		= 1;
            ChConfig[Ch].doLog 		= ui->log_Ch_6->isChecked();
            ChConfig[Ch].multiplier	= PrvCalculateMultiplier(ChConfig[Ch].gain, ChConfig[Ch].unipolar);
            break;
        case Chn7:
            sprintf(ChConfig[Ch].filename, "%s", CH7File);
            sprintf(ChConfig[Ch].chNameStr, "Ch7");
            ChConfig[Ch].RdBufPtr   = RdBuf->Ch7Buf;
            ChConfig[Ch].unipolar 	= 0;
            ChConfig[Ch].gain 		= 1;
            ChConfig[Ch].doLog 		= ui->log_Ch_7->isChecked();
            ChConfig[Ch].multiplier	= PrvCalculateMultiplier(ChConfig[Ch].gain, ChConfig[Ch].unipolar);
            break;
        case Chn01:
            sprintf(ChConfig[Ch].filename, "%s", CH01File);
            sprintf(ChConfig[Ch].chNameStr, "Ch01");
            ChConfig[Ch].RdBufPtr   = RdBuf->Ch01Buf;
            ChConfig[Ch].unipolar 	= 0;
            ChConfig[Ch].gain 		= 1;
//            ChConfig[Ch].doLog 		= ui->log_Ch_01->isChecked();
            ChConfig[Ch].multiplier	= PrvCalculateMultiplier(ChConfig[Ch].gain, ChConfig[Ch].unipolar);
            break;
        case Chn23:
            sprintf(ChConfig[Ch].filename, "%s", CH23File);
            sprintf(ChConfig[Ch].chNameStr, "Ch23");
            ChConfig[Ch].RdBufPtr   = RdBuf->Ch23Buf;
            ChConfig[Ch].unipolar 	= 0;
            ChConfig[Ch].gain 		= 1;
//            ChConfig[Ch].doLog 		= ui->log_Ch_23->isChecked();
            ChConfig[Ch].multiplier	= PrvCalculateMultiplier(ChConfig[Ch].gain, ChConfig[Ch].unipolar);
            break;
        case Chn45:
            sprintf(ChConfig[Ch].filename, "%s", CH45File);
            sprintf(ChConfig[Ch].chNameStr, "Ch45");
            ChConfig[Ch].RdBufPtr   = RdBuf->Ch45Buf;
            ChConfig[Ch].unipolar 	= 0;
            ChConfig[Ch].gain 		= 1;
//            ChConfig[Ch].doLog 		= ui->log_Ch_45->isChecked();
            ChConfig[Ch].multiplier	= PrvCalculateMultiplier(ChConfig[Ch].gain, ChConfig[Ch].unipolar);
            break;
        case Chn67:
            sprintf(ChConfig[Ch].filename, "%s", CH67File);
            sprintf(ChConfig[Ch].chNameStr, "Ch67");
            ChConfig[Ch].RdBufPtr   = RdBuf->Ch67Buf;
            ChConfig[Ch].unipolar 	= 0;
            ChConfig[Ch].gain 		= 1;
//            ChConfig[Ch].doLog 		= ui->log_Ch_67->isChecked();
            ChConfig[Ch].multiplier	= PrvCalculateMultiplier(ChConfig[Ch].gain, ChConfig[Ch].unipolar);
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


unsigned long long MainWindow::PrvGetSampleRateValue(int Ch)
{
    int index;
    QValidator *validator = new QIntValidator(samRateFieldMin,samRateFieldMax, this);
    QComboBox   *thePeriodBox;
    QLineEdit   *theLineEdit;

    switch (Ch)
    {
        case Chn0:
        case Chn01:
            thePeriodBox = ui->periodBox_ch_0;
            theLineEdit = ui->samrate_ch_0;
            break;
        case Chn1:
            thePeriodBox = ui->periodBox_ch_1;
            theLineEdit = ui->samrate_ch_1;
            break;
        case Chn2:
        case Chn23:
            thePeriodBox = ui->periodBox_ch_2;
            theLineEdit = ui->samrate_ch_2;
            break;
        case Chn3:
            thePeriodBox = ui->periodBox_ch_3;
            theLineEdit = ui->samrate_ch_3;
            break;
        case Chn4:
        case Chn45:
            thePeriodBox = ui->periodBox_ch_4;
            theLineEdit = ui->samrate_ch_4;
            break;
        case Chn5:
            thePeriodBox = ui->periodBox_ch_5;
            theLineEdit = ui->samrate_ch_5;
            break;
        case Chn6:
        case Chn67:
            thePeriodBox = ui->periodBox_ch_6;
            theLineEdit = ui->samrate_ch_6;
            break;
        case Chn7:
            thePeriodBox = ui->periodBox_ch_7;
            theLineEdit = ui->samrate_ch_7;
            break;
    }

    // Set the validator
    theLineEdit->setValidator(validator);
    index = thePeriodBox->currentIndex();

    if (theLineEdit->hasAcceptableInput())
    {
        unsigned long long tempLLong;
        QString str;

        // Need to ensure we limit the uSeconds to min 20us
        tempLLong = theLineEdit->text().toLongLong() * periodMicroSecondsMultiplier[index];

        if (index == indexMSeconds)
        {
            if (tempLLong < (samRateMSecsMin*periodMicroSecondsMultiplier[index]))
            {
                theLineEdit->setText(strBuf.sprintf("%d", samRateMSecsMin));
                QMessageBox::information(this,
                                         "ADC App",
                                         str.sprintf("Ch%s's minimum sampling period is %d milliseconds. Updating to minimum value.",
                                                     PrvGetChStr(Ch,&strBuf)->toStdString().c_str(),
                                                     samRateMSecsMin
                                                     )
                                         );
            }
        }

        // Save these to global prefs
        ChConfig[Ch].samplePeriodUnitIndex = index;
        ChConfig[Ch].samplePeriodValue = theLineEdit->text().toInt();

        return tempLLong;
    }
    else
    {
        if (index == indexMSeconds)
        {
            theLineEdit->setText(strBuf.sprintf("%d", samRateMSecsMin));
        }
        else
        {
            theLineEdit->setText("1");
        }

        // Save these to global prefs
        ChConfig[Ch].samplePeriodUnitIndex = index;
        ChConfig[Ch].samplePeriodValue = theLineEdit->text().toInt();
    }

    return 0;
}

int MainWindow::PrvSetupChannel(int Ch, int enable)
{
    int err;

    if (enable)
    {
        int config = LTC185x_ChSetup_Enabled;

        ChConfig[Ch].enabled    = 1;
        ChConfig[Ch].unipolar 	= 0;
        ChConfig[Ch].gain 		= 1;

        if (ChConfig[Ch].gain)      config |= LTC185x_ChSetup_Gain;
        if (ChConfig[Ch].unipolar)  config |= LTC185x_ChSetup_UniBi;
        err = PrvSetChannelConfig(Ch, config, PrvGetSampleRateValue(Ch));
    }
    else
    {
        ChConfig[Ch].enabled    = 0;
        err = PrvSetChannelConfig(Ch, 0 , 0);
    }

    return err;
}


void MainWindow::on_Start_clicked()
{
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
        err = PrvSetupChannel(Chn0, ui->select_ch_0->isChecked());
        if (err >= 0) startSampling++;

        err = PrvSetupChannel(Chn1, ui->select_ch_1->isChecked());
        if (err >= 0) startSampling++;

        err = PrvSetupChannel(Chn2, ui->select_ch_2->isChecked());
        if (err >= 0) startSampling++;

        err = PrvSetupChannel(Chn3, ui->select_ch_3->isChecked());
        if (err >= 0) startSampling++;

        err = PrvSetupChannel(Chn4, ui->select_ch_4->isChecked());
        if (err >= 0) startSampling++;

        err = PrvSetupChannel(Chn5, ui->select_ch_5->isChecked());
        if (err >= 0) startSampling++;

        err = PrvSetupChannel(Chn6, ui->select_ch_6->isChecked());
        if (err >= 0) startSampling++;

        err = PrvSetupChannel(Chn7, ui->select_ch_7->isChecked());
        if (err >= 0) startSampling++;

        // Start sampling
        if (startSampling)
        {
            int ch;
            for (ch=0;ch<=ChnMax; ch++)
            {
                if (ChConfig[ch].enabled)
                {
                    ChConfig[ch].chStartTime = QDateTime::currentDateTime();
                }
            }

            err = ioctl(fd_ltc185x, MZIO_LTC185x_START, 0);
            if (err<0) printf("Can't start ADC\n");

            isSampling = 1;

            ui->status->setText("Sampling started");
            RESET_STATUS_TIMER;
            RESET_STATUS_CYCLER;
        }
        else
        {
           QMessageBox::information(this, "ADC App", "No channels selected.");
        }

        PrvSavePreferences();
    }
    else
    {
        printf("LTC185x library failure\n");
    }

    statusCycler=0;
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
    ui->status->setText("Sampling stopped");
    RESET_STATUS_TIMER;
}

void MainWindow::on_select_ch_0_clicked()
{
    int Ch = Chn0;
    QCheckBox *ChCheckBox=ui->select_ch_0;

    strBuf.sprintf("%s %s",
                   PrvGetChStr(Ch, &strBuf)->toStdString().c_str(),
                   ChCheckBox->isChecked() ? "selected":"deselected");
    ui->status->setText(strBuf);
    MainWindow::on_Stop_clicked();
    RESET_STATUS_TIMER;
    RESET_STATUS_CYCLER;
}

void MainWindow::on_select_ch_1_clicked()
{
    int Ch = Chn1;
    QCheckBox *ChCheckBox=ui->select_ch_1;

    strBuf.sprintf("%s %s",
                   PrvGetChStr(Ch, &strBuf)->toStdString().c_str(),
                   ChCheckBox->isChecked() ? "selected":"deselected");
    ui->status->setText(strBuf);
    MainWindow::on_Stop_clicked();
    RESET_STATUS_TIMER;
    RESET_STATUS_CYCLER;
}

void MainWindow::on_select_ch_2_clicked()
{
    int Ch = Chn2;
    QCheckBox *ChCheckBox=ui->select_ch_2;

    strBuf.sprintf("%s %s",
                   PrvGetChStr(Ch, &strBuf)->toStdString().c_str(),
                   ChCheckBox->isChecked() ? "selected":"deselected");
    ui->status->setText(strBuf);
    MainWindow::on_Stop_clicked();
    RESET_STATUS_TIMER;
    RESET_STATUS_CYCLER;

}

void MainWindow::on_select_ch_3_clicked()
{
    int Ch = Chn3;
    QCheckBox *ChCheckBox=ui->select_ch_3;

    strBuf.sprintf("%s %s",
                   PrvGetChStr(Ch, &strBuf)->toStdString().c_str(),
                   ChCheckBox->isChecked() ? "selected":"deselected");
    ui->status->setText(strBuf);
    MainWindow::on_Stop_clicked();
    RESET_STATUS_TIMER;
    RESET_STATUS_CYCLER;

}

void MainWindow::on_select_ch_4_clicked()
{
    int Ch = Chn4;
    QCheckBox *ChCheckBox=ui->select_ch_4;

    strBuf.sprintf("%s %s",
                   PrvGetChStr(Ch, &strBuf)->toStdString().c_str(),
                   ChCheckBox->isChecked() ? "selected":"deselected");
    ui->status->setText(strBuf);
    MainWindow::on_Stop_clicked();
    RESET_STATUS_TIMER;
    RESET_STATUS_CYCLER;

}

void MainWindow::on_select_ch_5_clicked()
{
    int Ch = Chn5;
    QCheckBox *ChCheckBox=ui->select_ch_5;

    strBuf.sprintf("%s %s",
                   PrvGetChStr(Ch, &strBuf)->toStdString().c_str(),
                   ChCheckBox->isChecked() ? "selected":"deselected");
    ui->status->setText(strBuf);
    MainWindow::on_Stop_clicked();
    RESET_STATUS_TIMER;
    RESET_STATUS_CYCLER;
}

void MainWindow::on_select_ch_6_clicked()
{
    int Ch = Chn6;
    QCheckBox *ChCheckBox=ui->select_ch_6;

    strBuf.sprintf("%s %s",
                   PrvGetChStr(Ch, &strBuf)->toStdString().c_str(),
                   ChCheckBox->isChecked() ? "selected":"deselected");
    ui->status->setText(strBuf);
    MainWindow::on_Stop_clicked();
    RESET_STATUS_TIMER;
    RESET_STATUS_CYCLER;

}

void MainWindow::on_select_ch_7_clicked()
{
    int Ch = Chn7;
    QCheckBox *ChCheckBox=ui->select_ch_7;

    strBuf.sprintf("%s %s",
                   PrvGetChStr(Ch, &strBuf)->toStdString().c_str(),
                   ChCheckBox->isChecked() ? "selected":"deselected");
    ui->status->setText(strBuf);
    MainWindow::on_Stop_clicked();
    RESET_STATUS_TIMER;
    RESET_STATUS_CYCLER;
}


void MainWindow::on_logcheckBox_clicked()
{
    int Ch = Chn0;
    QString temp;
    int j;
    QCheckBox *ChCheckBox=(QCheckBox*) sender();

    temp = ChCheckBox->objectName();
    j = temp.indexOf("Ch", Qt::CaseSensitive);
    if (j >= 0)
    {
        qDebug() << "on_logcheckBox_clicked" << ChCheckBox->objectName() << j << temp.at(j+3);
    }

    ChConfig[Ch].doLog = ChCheckBox->isChecked();
    strBuf.sprintf("Ch%s %s logging",
                   PrvGetChStr(Ch, &strBuf)->toStdString().c_str(),
                   ChCheckBox->isChecked() ? "is":"is not");
    ui->status->setText(strBuf);
    PrvSavePreferences();
    RESET_STATUS_TIMER;
    RESET_STATUS_CYCLER;
}




int MainWindow::PrvGetSamples(int Ch, short* buf, unsigned int *overun)
{
    ReadBufferData  RdBufDat;
    int             retVal=0;

    RdBufDat.ch = Ch;
    RdBufDat.buf = (unsigned short*) buf;
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
        QMessageBox::information(this,
                                 "ADC App",
                                 strBuf.sprintf("Ch%s's buffer has overun. Please restart sampling.",
                                             PrvGetChStr(Ch,&strBuf)->toStdString().c_str()
                                             )
                                 );

    }

    return retVal;
}


int MainWindow::PrvWriteSamplesToFile(int Ch, QString filename, short* buf, int numSamples, int overun)
{
    QString         dateStr = ChConfig[Ch].chStartTime.toString("yyyy-MM-dd,");
    QString         timeStr;
    int             i;
    QFile           file(filename);

    if (file.open(QIODevice::Append))
    {
        QTextStream str(&strBuf);
        QTextStream out(&file);
        int         inc=ChConfig[Ch].periodMicroSecs/1000;

        for (i=0;i<numSamples; i++)
        {
            ChConfig[Ch].chStartTime = ChConfig[Ch].chStartTime.addMSecs(inc);
            timeStr= ChConfig[Ch].chStartTime.toString("hh:mm:ss.zzz,");
            out << dateStr << timeStr << PrvCalculate_mV(Ch, buf[i]) << "," << overun << endl;
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
    if (statusEraseCount-- <=0)
    {
        ui->status->setText("Ready ...");
        RESET_STATUS_TIMER;
    }

    if (isSampling)
    {
        if (sample_timer_count-- <= 0)
        {
            if (statusCycler == 1)
            {
                ui->status->setText("Sampling");
                statusCycler = 0;
            }
            else if (statusCycler <= 0)
            {
                ui->status->setText("");
                statusCycler = 1;
            } else
            {
                statusCycler--;
            }
            RESET_STATUS_TIMER;



            if (fd_ltc185x)
            {
                QString         filename;
                QString         valueStr;

                unsigned int    overun=0;
                int             numSamples;
                int             Ch;
                short           *dataPtr;
                float            value;
                int             chEnabled=8;

                if (ui->select_ch_0->isChecked())
                {
                    Ch = Chn0;
                    dataPtr = ChConfig[Ch].RdBufPtr;
                    numSamples = PrvGetSamples(Ch, dataPtr, &overun);
                    if (numSamples)
                    {
                        value = (float) (PrvCalculate_mV(Ch, dataPtr[0]))/1000;
                        ui->Value_ch_0->setText(valueStr.sprintf("%-.3f V", value));
                        if (ui->log_Ch_0->isChecked())
                        {
                            filename.sprintf("%s/%s", StoreDir, ChConfig[Ch].filename);
                            PrvWriteSamplesToFile(Ch, filename, dataPtr, numSamples, overun);
                        }
                    }
                }
                else
                {
                    ui->Value_ch_0->setText("Disabled");
                    chEnabled--;
                }

                if (ui->select_ch_1->isChecked())
                {
                    Ch = Chn1;
                    dataPtr = ChConfig[Ch].RdBufPtr;
                    numSamples = PrvGetSamples(Ch, dataPtr, &overun);
                    if (numSamples)
                    {
                        value = (float) (PrvCalculate_mV(Ch, dataPtr[0]))/1000;
                        ui->Value_ch_1->setText(valueStr.sprintf("%-.3f V", value));
                        if (ui->log_Ch_1->isChecked())
                        {
                            filename.sprintf("%s/%s", StoreDir, ChConfig[Ch].filename);
                            PrvWriteSamplesToFile(Ch, filename, dataPtr, numSamples, overun);
                        }
                    }
                }
                else
                {
                    ui->Value_ch_1->setText("Disabled");
                    chEnabled--;
                }

                if (ui->select_ch_2->isChecked())
                {
                    Ch = Chn2;
                    dataPtr = ChConfig[Ch].RdBufPtr;
                    numSamples = PrvGetSamples(Ch, dataPtr, &overun);
                    if (numSamples)
                    {
                        value = (float) (PrvCalculate_mV(Ch, dataPtr[0]))/1000;
                        ui->Value_ch_2->setText(valueStr.sprintf("%-.3f V", value));
                        if (ui->log_Ch_2->isChecked())
                        {
                            filename.sprintf("%s/%s", StoreDir, ChConfig[Ch].filename);
                            PrvWriteSamplesToFile(Ch, filename, dataPtr, numSamples, overun);
                        }
                    }
                }
                else
                {
                    ui->Value_ch_2->setText("Disabled");
                    chEnabled--;
                }

                if (ui->select_ch_3->isChecked())
                {
                    Ch = Chn3;
                    dataPtr = ChConfig[Ch].RdBufPtr;
                    numSamples = PrvGetSamples(Ch, dataPtr, &overun);
                    if (numSamples)
                    {
                        value = (float) (PrvCalculate_mV(Ch, dataPtr[0]))/1000;
                        ui->Value_ch_3->setText(valueStr.sprintf("%-.3f V", value));
                        if (ui->log_Ch_3->isChecked())
                        {
                            filename.sprintf("%s/%s", StoreDir, ChConfig[Ch].filename);
                            PrvWriteSamplesToFile(Ch, filename, dataPtr, numSamples, overun);
                        }
                    }
                }
                else
                {
                    ui->Value_ch_3->setText("Disabled");
                    chEnabled--;
                }

                if (ui->select_ch_4->isChecked())
                {
                    Ch = Chn4;
                    dataPtr = ChConfig[Ch].RdBufPtr;
                    numSamples = PrvGetSamples(Ch, dataPtr, &overun);
                    if (numSamples)
                    {
                        value = (float) (PrvCalculate_mV(Ch, dataPtr[0]))/1000;
                        ui->Value_ch_4->setText(valueStr.sprintf("%-.3f V", value));
                        if (ui->log_Ch_4->isChecked())
                        {
                            filename.sprintf("%s/%s", StoreDir, ChConfig[Ch].filename);
                            PrvWriteSamplesToFile(Ch, filename, dataPtr, numSamples, overun);
                        }
                    }
                }
                else
                {
                    ui->Value_ch_4->setText("Disabled");
                    chEnabled--;
                }

                if (ui->select_ch_5->isChecked())
                {
                    Ch = Chn5;
                    dataPtr = ChConfig[Ch].RdBufPtr;
                    numSamples = PrvGetSamples(Ch, dataPtr, &overun);
                    if (numSamples)
                    {
                        value = (float) (PrvCalculate_mV(Ch, dataPtr[0]))/1000;
                        ui->Value_ch_5->setText(valueStr.sprintf("%-.3f V", value));
                        if (ui->log_Ch_5->isChecked())
                        {
                            filename.sprintf("%s/%s", StoreDir, ChConfig[Ch].filename);
                            PrvWriteSamplesToFile(Ch, filename, dataPtr, numSamples, overun);
                        }
                    }
                }
                else
                {
                    ui->Value_ch_5->setText("Disabled");
                    chEnabled--;
                }


                if (ui->select_ch_6->isChecked())
                {
                    Ch = Chn6;
                    dataPtr = ChConfig[Ch].RdBufPtr;
                    numSamples = PrvGetSamples(Ch, dataPtr, &overun);
                    if (numSamples)
                    {
                        value = (float) (PrvCalculate_mV(Ch, dataPtr[0]))/1000;
                        ui->Value_ch_6->setText(valueStr.sprintf("%-.3f V", value));
                        if (ui->log_Ch_6->isChecked())
                        {
                            filename.sprintf("%s/%s", StoreDir, ChConfig[Ch].filename);
                            PrvWriteSamplesToFile(Ch, filename, dataPtr, numSamples, overun);
                        }
                    }
                }
                else
                {
                    ui->Value_ch_6->setText("Disabled");
                    chEnabled--;
                }

                if (ui->select_ch_7->isChecked())
                {
                    Ch = Chn7;
                    dataPtr = ChConfig[Ch].RdBufPtr;
                    numSamples = PrvGetSamples(Ch, dataPtr, &overun);
                    if (numSamples)
                    {
                        value = (float) (PrvCalculate_mV(Ch, dataPtr[0]))/1000;
                        ui->Value_ch_7->setText(valueStr.sprintf("%-.3f V", value));
                        if (ui->log_Ch_7->isChecked())
                        {
                            filename.sprintf("%s/%s", StoreDir, ChConfig[Ch].filename);
                            PrvWriteSamplesToFile(Ch, filename, dataPtr, numSamples, overun);
                        }
                    }
                }
                else
                {
                    ui->Value_ch_7->setText("Disabled");
                    chEnabled--;
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

void MainWindow::on_samrate_editingFinished()
{
    qDebug() << "on_samrate_editingFinished";

    if (isSampling)
    {
        MainWindow::on_Stop_clicked();
    }
    PrvSavePreferences();
}

void MainWindow::on_periodBox_activated(int index)
{
    qDebug() << "on_periodBox_ch_0_activated" << index;
    if (isSampling)
    {
        MainWindow::on_Stop_clicked();
    }
    PrvSavePreferences();
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


void MainWindow::on_DeleteCSV_clicked()
{

    switch( QMessageBox::question(
                    this,
                    tr("ADC App"),
                    tr("This action will erase all logged data from the unit. Are you sure?"),

                    QMessageBox::Yes |
                    QMessageBox::Cancel,

                    QMessageBox::Cancel ) )
        {
          case QMessageBox::Yes:
            QFile::remove(strBuf.sprintf("%s/%s", StoreDir, CH0File));
            QFile::remove(strBuf.sprintf("%s/%s", StoreDir, CH1File));
            QFile::remove(strBuf.sprintf("%s/%s", StoreDir, CH2File));
            QFile::remove(strBuf.sprintf("%s/%s", StoreDir, CH3File));
            QFile::remove(strBuf.sprintf("%s/%s", StoreDir, CH4File));
            QFile::remove(strBuf.sprintf("%s/%s", StoreDir, CH5File));
            QFile::remove(strBuf.sprintf("%s/%s", StoreDir, CH6File));
            QFile::remove(strBuf.sprintf("%s/%s", StoreDir, CH7File));
            QFile::remove(strBuf.sprintf("%s/%s", StoreDir, CH01File));
            QFile::remove(strBuf.sprintf("%s/%s", StoreDir, CH23File));
            QFile::remove(strBuf.sprintf("%s/%s", StoreDir, CH45File));
            QFile::remove(strBuf.sprintf("%s/%s", StoreDir, CH67File));
            break;
          case QMessageBox::Cancel:
            break;
          default:
            break;
        }
}





