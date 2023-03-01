#ifndef SERIALCLIENT_H
#define SERIALCLIENT_H

#include <QThread>
#include <QSerialPort>
#include <QTimer>

#include "UV/iserverdata.h"

class SerialClient : public QThread {
Q_OBJECT

public:
    SerialClient(e_packageMode connectionType);
    ~SerialClient();

    void run();
    int exec();

    e_packageMode messageType;

signals:
    void error(QString err);
    void dataUpdated();

public slots:
    void changeSelectedConnectionType(e_packageMode connectionType);

private:
    QSerialPort *serialPort;
    QTimer *timeoutTimer;
    IServerData *interface;

    void changeThrusterToNext();
    void changeControlContourToNext();

    bool portConnect(int port);
};

#endif // SERIALCLIENT_H
