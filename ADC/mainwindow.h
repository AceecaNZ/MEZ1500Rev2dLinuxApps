#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <sys/ioctl.h>

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
    void on_modpwron_clicked();

    void on_modpwroff_clicked();

    void on_modrston_clicked();

    void on_modrstoff_clicked();

    void on_initadc_clicked();

    void on_readADC_clicked();

private:
    Ui::MainWindow *ui;

    int count;
    int fd_mzio;
    int fd_spi;
};

#endif // MAINWINDOW_H
