#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QThread>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QTimer>
#include <sstream>

#include "UV/iserverdata.h"

class UdpClient: public QThread {
    Q_OBJECT

public:
    UdpClient();
    ~UdpClient();

    void run();
    int exec();

signals:
    void dataUpdated();

private:
    QUdpSocket* udpSocket;
    IServerData* uv_interface;
    QTimer* timeoutTimer;

    void connectToHost();

private slots:
    void readPendingDatagrams();
};

#endif // UDPCLIENT_H
