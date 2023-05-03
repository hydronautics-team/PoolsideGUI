#include "mainwindow.h"
#include "StabilizationSettings/StabilizationWindow.h"
#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();
    return a.exec();
}
