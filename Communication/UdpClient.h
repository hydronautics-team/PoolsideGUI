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
    int send_loop();

signals:
    void dataUpdated();

private:
    QUdpSocket* receiveSocket;
    QUdpSocket* sendSocket;
    IServerData* uv_interface;
    QTimer* timeoutTimer;

    void connectSend();

private slots:
    void readPendingDatagrams();
};

#endif // UDPCLIENT_H
