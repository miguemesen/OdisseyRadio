#include "mainwindow.h"
#include <QApplication>
#include "memoryusage.h"



int main(int argc, char *argv[])
{
    PrintMemoryUsage();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


