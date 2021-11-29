#ifndef SERIALCLIENT_H
#define SERIALCLIENT_H

#include <QThread>
#include <QSerialPort>
#include <QTimer>

#include "UV/iserverdata.h"

class SerialClient : public QThread {
Q_OBJECT

public:
    SerialClient(e_MessageTypes connectionType);

    void run();
    int exec();

    e_MessageTypes messageType;

signals:
    void error(QString err);
    void dataUpdated();

public slots:
    void changeSelectedConnectionType(e_MessageTypes connectionType);
    void changeSelectedThruster(unsigned int slot);

private:
    QSerialPort *serialPort;
    QTimer *timeoutTimer;
    IServerData *interface;

    bool portConnect(int port);
};

#endif // SERIALCLIENT_H
