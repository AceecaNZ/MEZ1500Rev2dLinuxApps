#include "mainwindow.h"
#include <QApplication>
#include <sys/ioctl.h>
#include <stdio.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    printf("ADC test application\n");
    fflush(stdout);

    return a.exec();
}
