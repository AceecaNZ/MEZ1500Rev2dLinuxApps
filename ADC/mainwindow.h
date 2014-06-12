#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <sys/ioctl.h>
#include "keyboard/keyboard.h"
#include "/opt/MEZ1500Rev2dLinux/Sources/linux-2.6.32.2/drivers/char/MEZ1500_mzio_ltc185x.h"

#define ChMaxReadSamples 50
#define sampleSize sizeof(short)

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

    void on_down_clicked();

    void on_up_pressed();

    int PrvGetSamples(int Ch, unsigned short* buf, unsigned int *overun);

    int PrvSetChannelConfig(int Ch, unsigned int config, unsigned long period);
private:
    Ui::MainWindow *ui;

    int                 gErr;
    QString             strBuf;
    int                 fd_ltc185x;
    int                 status_erase_count;
    char                isSampling;
    Keyboard            *lineEditkeyboard;
    int                 count;
    unsigned long       samrate_vals[12];

    int                 sample_timer_count;     // for reading samples
    BufData             *RdBuf;
    unsigned short      Ch0NumSamples;
};

#endif // MAINWINDOW_H
