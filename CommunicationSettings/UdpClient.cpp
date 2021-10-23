#include "UdpClient.h"

#include <QNetworkDatagram>
#include <sstream>

UdpClient::UdpClient() {
    uv_interface = new IServerData();

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::LocalHost, 7755);

    connect(udpSocket, &QUdpSocket::readyRead,
            this, &UdpClient::readPendingDatagrams);

    udpHostAddress = "127.0.0.1";
    udpHostPort = 26782;

    messageType = MESSAGE_NORMAL;
}

UdpClient::~UdpClient() {
    udpSocket->close();
    delete udpSocket;
    delete uv_interface;
    delete timeoutTimer;
}

void UdpClient::run() {
    try {
        connectToHost();
    }
    catch (const std::invalid_argument &error) {
        qDebug() << "[UDP_CLIENT_ERROR] " << error.what();
    }

    exec();
}

int UdpClient::exec() {
    while (1) {
        QByteArray msg;
        msg = uv_interface->generateMessage(messageType);

//        qDebug() << "[UDP_CLIENT] Sending message type " << messageType << "||" << msg.size();

        QNetworkDatagram datagram;
        datagram.setData(msg);
        udpSocket->writeDatagram(datagram);
        msleep(100);
    }
}

void UdpClient::readPendingDatagrams() {
    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        QByteArray msg = datagram.data();
        bool exception_caught = false;
        try {
            uv_interface->parseMessage(msg, messageType);
        }
        catch (const std::invalid_argument &error) {
//            qDebug() << "[UDP_CLIENT_ERROR] " << error.what();
            exception_caught = true;
        }
        if (!exception_caught) {
//            qDebug() << "[UDP_CLIENT] Message parced " << messageType << "||" << msg.size();
            emit dataUpdated();
        }
    }
}

void UdpClient::connectToHost() {
    QHostAddress udpQHostAddress;
    if (!udpQHostAddress.setAddress(udpHostAddress)) {
        std::stringstream stream;
        stream << "Parsing UDP Host Address error. Address: [" <<
               udpHostAddress.toStdString() << "]";
        throw std::invalid_argument(stream.str());
        return;
    }

    udpSocket->connectToHost(udpHostAddress, udpHostPort);

    if (!udpSocket->waitForConnected(1000)) {
        throw std::invalid_argument("Can't connect to host, connection timeout");
    }
}
