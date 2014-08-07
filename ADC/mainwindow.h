#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <sys/ioctl.h>
#include "keyboard/keyboard.h"
#include "/opt/MEZ1500Rev2dLinux/Sources/linux-2.6.32.2/drivers/char/MEZ1500_mzio_ltc185x.h"

#define ChMaxReadSamples 51000
#define sampleSize sizeof(short)

#define StoreDir    "/sdcard"
#define CH0File     "Ch0.csv"
#define CH1File     "Ch1.csv"
#define CH01File    "Ch01.csv"
#define CH2File     "Ch2.csv"
#define CH3File     "Ch3.csv"
#define CH23File    "Ch23.csv"
#define CH4File     "Ch4.csv"
#define CH5File     "Ch5.csv"
#define CH45File    "Ch45.csv"
#define CH6File     "Ch6.csv"
#define CH7File     "Ch7.csv"
#define CH67File    "Ch67.csv"
#define AppPrefsFile "ADC_prefs.xml"


// Sample rate range
#define samRateFieldMin 1
#define samRateFieldMax 10000
//#define samRateUSecsMin 1000
#define samRateMSecsMin 250

// Period Combobox index definition
#define indexDays       0
#define indexHours      1
#define indexMinutes    2
#define indexSeconds    3
#define indexMSeconds   4
//#define indexUSeconds   5

const unsigned long long periodMicroSecondsMultiplier[6] =
{
    86400000000LL,  // days
    3600000000LL,   // hours
    60000000,     // minutes
    1000000,      // seconds
    1000,         // milliseconds
    1             // microseconds
};

typedef struct {
  char                  filename[10];
  char                  chNameStr[10];
  short                 *RdBufPtr;
  unsigned long long    periodMicroSecs;
  unsigned long long    periodCounter;
  unsigned int          multiplier;
  QDateTime             chStartTime;

  // Saved in prefs file
  int                   enabled;
  int                   samplePeriodUnitIndex;
  int                   samplePeriodValue;
  int                   doLog;
  int					unipolar;				// 1=0-X, 0=-X to + X
  int					gain;					// If 0=5V range, 1=10V range
} ChConfigType;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    int PrvLoadPreferences();
    int PrvSavePreferences();

    void on_Start_clicked();

    void on_Stop_clicked();

    void on_select_ch_0_clicked();

    void on_select_ch_1_clicked();

    void on_select_ch_2_clicked();

    void on_select_ch_3_clicked();

    void on_select_ch_4_clicked();

    void on_select_ch_5_clicked();

    void on_select_ch_6_clicked();

    void on_select_ch_7_clicked();


    void on_timer_event();

    void run_keyboard_lineEdit();

    QString* PrvGetChStr(int Ch, QString* chStr);

    unsigned long long PrvGetSampleRateValue(int Ch);

    int PrvGetSamples(int Ch, short *buf, unsigned int *overun);

    int PrvSetChannelConfig(int Ch, unsigned int config, unsigned long long period);

    int PrvWriteSamplesToFile(int ch, QString file, short* buf, int numSamples, int overun);

    int PrvCalculateMultiplier(int gain, int unipolar);

    int PrvCalculate_mV(int Ch, short data);

    int PrvSetupChannel(int Ch, int enable);

    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_samrate_editingFinished();

    void on_Setup_currentChanged(int index);

    void on_DeleteCSV_clicked();

    void on_log_Ch_0_clicked();

    void on_log_Ch_1_clicked();

    void on_log_Ch_2_clicked();

    void on_log_Ch_3_clicked();

    void on_log_Ch_4_clicked();

    void on_log_Ch_5_clicked();

    void on_log_Ch_6_clicked();

    void on_log_Ch_7_clicked();


private:
    Ui::MainWindow *ui;

    int                 gErr;
    QString             strBuf;
    int                 fd_ltc185x;
    int                 fd_mzio;
    int                 statusEraseCount;
    int                 statusCycler;
    int                 minutes;
    char                isSampling;
    Keyboard            *lineEditkeyboard;
    int                 count;
    int                 sample_timer_count;     // for reading samples
    BufData             *RdBuf;


    ChConfigType        ChConfig[ChnMax+1];
};

#endif // MAINWINDOW_H
