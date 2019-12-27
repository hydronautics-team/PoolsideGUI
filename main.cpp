#include "mainwindow.h"
#include "com_server.h"
#include "UI_Tests/serverdata_test.h"

#include <QApplication>
#include <QThread>
#include <QTest>

int main(int argc, char *argv[])
{
//    QThread *uv_communication_thread = new QThread();
//    COM_Server* server = new COM_Server();
//    server->moveToThread(uv_communication_thread);
//    uv_communication_thread->start();

    freopen("testing.log", "w", stdout);
    QApplication a(argc, argv);
    QTest::qExec(new Serverdata_Test, argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return a.exec();
}
