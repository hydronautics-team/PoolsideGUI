#include "UdpClient.h"

UdpClient::UdpClient() {
    uv_interface = new IServerData();

    receiveSocket = new QUdpSocket(this);
    sendSocket = new QUdpSocket(this);

    receiveSocket->bind(QHostAddress(uv_interface->getUdpRemoteAddress()), uv_interface->getUdpRemotePort());
    connect(receiveSocket, &QUdpSocket::readyRead, this, &UdpClient::readPendingDatagrams);
    qDebug() << "[UDP_CLIENT] Listening to "  << uv_interface->getUdpRemoteAddress() << ":" << uv_interface->getUdpRemotePort();
    
    run();
}

UdpClient::~UdpClient() {
    receiveSocket->close();
    sendSocket->close();
    delete receiveSocket;
    delete sendSocket;
    delete uv_interface;
    delete timeoutTimer;
}

void UdpClient::run() {
    try {
        connectSend();
    }
    catch (const std::invalid_argument& error) {
        qDebug() << "[UDP_CLIENT_ERROR] " << error.what();
    }
    send_loop();
}

int UdpClient::send_loop() {
    while (1) {
        QByteArray msg;
        msg = uv_interface->generateMessage();
        qDebug() << "[UDP_CLIENT] Sending message size "  << "||" << msg.size();

        QNetworkDatagram datagram;
        datagram.setData(msg);
        sendSocket->writeDatagram(datagram);
        msleep(1000);
    }
}

void UdpClient::readPendingDatagrams() {
    qDebug() << "[UDP_CLIENT] Good";
    while (receiveSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = receiveSocket->receiveDatagram();
        QByteArray msg = datagram.data();
        bool exception_caught = false;
        try {
            uv_interface->parseMessage(msg);
        }
        catch (const std::invalid_argument& error) {
             qDebug() << "[UDP_CLIENT_ERROR] " << error.what();
            exception_caught = true;
        }
        if (!exception_caught) {
             qDebug() << "[UDP_CLIENT] Message parced "  << msg.size();
            emit dataUpdated();
        }
    }
}

void UdpClient::connectSend() {
    QHostAddress udpQHostAddress;
    if (!udpQHostAddress.setAddress(uv_interface->getUdpHostAddress())) {
        std::stringstream errorStream;
        errorStream << "Parsing UDP Host Address error. Address: [" <<
            uv_interface->getUdpHostAddress().toStdString() << "]";
        throw std::invalid_argument(errorStream.str());
        return;
    }

    sendSocket->connectToHost(udpQHostAddress, uv_interface->getUdpHostPort());
    qDebug() << "[UDP_CLIENT] Send socket connected to "  << uv_interface->getUdpHostAddress() << ":" << uv_interface->getUdpHostPort();

    if (!sendSocket->waitForConnected(1)) {
        throw std::invalid_argument("Can't connect to host, connection timeout");
    }
    qDebug() << "[UDP_CLIENT] Connected";
}
