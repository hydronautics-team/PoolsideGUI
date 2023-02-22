#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QThread>
#include <QUdpSocket>
#include <QTimer>
#include <QString>

#include "UV/iserverdata.h"

class UdpClient : public QThread {
Q_OBJECT

public:
    UdpClient();
    ~UdpClient();

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

#endif // UDPCLIENT_H
