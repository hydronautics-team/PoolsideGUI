#include "mainwindow.h"
#include "serial_client.h"
#include "UI_Tests/serverdata_test.h"
#include <QApplication>
#include <QTest>

int main(int argc, char *argv[])
{
    freopen("testing.log", "w", stdout);
    QApplication a(argc, argv);
    QTest::qExec(new Serverdata_Test, argc, argv);
    boost::asio::io_service io;
    MainWindow mainWindow(io);
    io.run();
    mainWindow.show();
    return a.exec();
}
