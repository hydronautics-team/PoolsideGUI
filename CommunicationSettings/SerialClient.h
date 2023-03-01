#ifndef SERIALCLIENT_H
#define SERIALCLIENT_H

#include <QThread>
#include <QSerialPort>
#include <QTimer>

#include "UV/iserverdata.h"
#include "UV/uv_state.h"

class SerialClient: public QThread {
    Q_OBJECT

public:
    SerialClient();
    ~SerialClient();

    void run();
    int exec();

    e_packageMode packageMode = e_packageMode::PACKAGE_NORMAL;

signals:
    void error(QString err);
    void dataUpdatedSerialClient();

private:
    QSerialPort* serialPort;
    QTimer* timeoutTimer;
    IServerData* interface;

    bool portConnect(int port);
};

#endif // SERIALCLIENT_H
