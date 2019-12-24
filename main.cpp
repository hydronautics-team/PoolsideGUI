#include "operatorwindow.h"
#include "com_server.h"

#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    QThread *uv_communication_thread = new QThread();
    COM_Server* server = new COM_Server();
    server->moveToThread(uv_communication_thread);
    uv_communication_thread->start();

    QApplication a(argc, argv);
    OperatorWindow w;
    w.show();
    return a.exec();
}
