#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include <QThread>
#include <QUdpSocket>
#include <QTimer>
#include <QString>

#include "UV/iserverdata.h"

class UDP_Client : public QThread
{
    Q_OBJECT

public:
    UDP_Client();
    ~UDP_Client();

    void run();
    int exec();

signals:
    void dataUpdated();

private:
    QUdpSocket *udpSocket;
    IServerData *uv_interface;
    QTimer *timeoutTimer;

    int messageType;

    QString udpHostAddress;
    quint64 udpHostPort;

    void connectToHost();

private slots:
    void readPendingDatagrams();
};

#endif // UDP_SERVER_H
