#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <sys/ioctl.h>
#include "keyboard/keyboard.h"
#include "/opt/MEZ1500Rev2dLinux/Sources/linux-2.6.32.2/drivers/char/MEZ1500_mzio_ltc185x.h"

#define ChMaxReadSamples 500
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

// Period Combobox index definition
#define indexDays       0
#define indexHours      1
#define indexMinutes    2
#define indexSeconds    3
#define indexMSeconds   4
#define indexUSeconds   5

const unsigned long long periodMicroSecondsMultiplier[6] =
{
    86400000000,  // days
    3600000000,   // hours
    60000000,     // minutes
    1000000,      // seconds
    1000,         // milliseconds
    1             // microseconds
};

typedef struct {
  char                  filename[10];
  char                  chNameStr[10];
  unsigned short        *RdBufPtr;
  unsigned long long    periodMicroSecs;
  unsigned long long    periodCounter;
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
    void on_Start_clicked();

    void on_Stop_clicked();

    void on_Ch0_clicked();

    void on_Ch1_clicked();

    void on_Ch2_clicked();

    void on_Ch3_clicked();

    void on_Ch4_clicked();

    void on_Ch5_clicked();

    void on_Ch6_clicked();

    void on_Ch7_clicked();

    void on_Ch01_clicked();

    void on_Ch23_clicked();

    void on_Ch45_clicked();

    void on_Ch67_clicked();

    void on_timer_event();

    void run_keyboard_lineEdit();

    int PrvGetSamples(int Ch, unsigned short* buf, unsigned int *overun);

    int PrvSetChannelConfig(int Ch, unsigned int config, unsigned long long period);

    int PrvWriteSamplesToFile(int ch, QString file, unsigned short* buf, int numSamples, int overun);

    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_checkBox_5V10V_clicked();

private:
    Ui::MainWindow *ui;

    int                 gErr;
    QString             strBuf;
    int                 fd_ltc185x;
    int                 status_erase_count;
    int                 minutes;
    char                isSampling;
    Keyboard            *lineEditkeyboard;
    int                 count;

    int                 sample_timer_count;     // for reading samples
    BufData             *RdBuf;
    ChConfigType        ChConfig[ChnMax+1];
};

#endif // MAINWINDOW_H
