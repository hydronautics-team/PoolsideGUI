#include "UdpClient.h"

UdpClient::UdpClient() {
    uv_interface = new IServerData();

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::LocalHost, 7755);

    connect(udpSocket, &QUdpSocket::readyRead, this, &UdpClient::readPendingDatagrams);
}

UdpClient::~UdpClient() {
    // udpSocket->close();
    // delete udpSocket;
    // delete uv_interface;
    // delete timeoutTimer;
    // QThread::wait(5000);
    // delete udpSocket;
    // delete uv_interface;
    // delete timeoutTimer;
}

void UdpClient::run() {
    try {
        connectToHost();
    }
    catch (const std::invalid_argument& error) {
        qDebug() << "[UDP_CLIENT_ERROR] " << error.what();
    }
    exec();
}

int UdpClient::exec() {
    while (1) {
        QByteArray msg;
        msg = uv_interface->generateMessage();
        // qDebug() << "[UDP_CLIENT] Sending message type " << messageType << "||" << msg.size();

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
            uv_interface->parseMessage(msg);
        }
        catch (const std::invalid_argument& error) {
            // qDebug() << "[UDP_CLIENT_ERROR] " << error.what();
            exception_caught = true;
        }
        if (!exception_caught) {
            // qDebug() << "[UDP_CLIENT] Message parced " << messageType << "||" << msg.size();
            emit dataUpdatedUdpClient();
        }
    }
}

void UdpClient::connectToHost() {
    QHostAddress udpQHostAddress;
    if (!udpQHostAddress.setAddress(uv_interface->getUdpHostAddress())) {
        std::stringstream errorStream;
        errorStream << "Parsing UDP Host Address error. Address: [" <<
            uv_interface->getUdpHostAddress().toStdString() << "]";
        throw std::invalid_argument(errorStream.str());
        return;
    }

    udpSocket->connectToHost(udpQHostAddress, uv_interface->getUdpHostPort());

    if (!udpSocket->waitForConnected(1000)) {
        throw std::invalid_argument("Can't connect to host, connection timeout");
    }
}
