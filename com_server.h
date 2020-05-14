#ifndef COM_SERVER_H
#define COM_SERVER_H

#include <QThread>
#include <QSerialPort>
#include <QTimer>

#include "UV/iserverdata.h"

class COM_Server : public QThread
{
    Q_OBJECT

public:
    COM_Server();

    void run();
    int exec();

signals:
    void error(QString err);
    void dataUpdated();

public slots:
    void changeSelectedThruster(unsigned int slot);

private:
    QSerialPort *serialPort;
    QTimer *timeoutTimer;
    IServerData *interface;

    bool portConnect(int port);
};

#endif // COM_SERVER_H
