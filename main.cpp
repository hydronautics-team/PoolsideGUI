#include "mainwindow.h"
#include "serial_client.h"
#include "UI_Tests/serverdata_test.h"
#include "tcp_server.h"

#include <QApplication>
#include <QThread>
#include <thread>
#include <QTest>

int main(int argc, char *argv[])
{
    freopen("testing.log", "w", stdout);
    QApplication a(argc, argv);
    QTest::qExec(new Serverdata_Test, argc, argv);
    MainWindow mainWindow;
    std::thread th([&]() {
        boost::asio::io_service io_service;
        Server server(io_service, mainWindow);
        io_service.run();
        while (true) {
            server.get_message();
        }
    });
    mainWindow.show();
    th.detach();
    return a.exec();
}
