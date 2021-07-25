#include "mainwindow.h"
#include "serial_client.h"
#include "UI_Tests/serverdata_test.h"

#include "Logger/LoggingCategories.h"

#include <QApplication>
#include <QThread>
#include <QTest>

int main(int argc, char *argv[])
{
    initLogger("D:/Hydro");

    freopen("testing.log", "w", stdout);
    QApplication a(argc, argv);
    QTest::qExec(new Serverdata_Test, argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return a.exec();
}
