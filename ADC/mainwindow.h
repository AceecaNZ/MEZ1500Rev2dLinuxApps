#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <sys/ioctl.h>
#include "keyboard/keyboard.h"

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

    void on_Ch0_samrate_valueChanged(int arg1);

    void on_timer_event();

    void run_keyboard_lineEdit();

    void on_down_clicked();

    void on_up_pressed();

private:
    Ui::MainWindow *ui;

    int count;
    int fd_ltc185x;
    unsigned long status_erase_count;
    QString strBuf;
    Keyboard *lineEditkeyboard;
    unsigned long samrate_vals[12];
};

#endif // MAINWINDOW_H
