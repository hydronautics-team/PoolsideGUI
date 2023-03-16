#include "UdpClient.h"

UdpClient::UdpClient() {
    uv_interface = new IServerData();

    senderSocket = new QUdpSocket(this);
    // senderSocket->bind(QHostAddress("192.168.31.50"), 5000);
    receiverSocket = new QUdpSocket(this);
    receiverSocket->bind(QHostAddress("192.168.31.100"), 5001);

    connect(receiverSocket, &QUdpSocket::readyRead, this, &UdpClient::readPendingDatagrams);
    this->start();
}

UdpClient::~UdpClient() {
    senderSocket->close();
    delete senderSocket;
    delete receiverSocket;
    delete uv_interface;
    delete timeoutTimer;
}

void UdpClient::run() {
    // qDebug() << "run Udp";
    // try {
    //     connectToHost();
    // }
    // catch (const std::invalid_argument& error) {
    //     qDebug() << "[UDP_CLIENT_ERROR] " << error.what();
    // }
    exec();
}

int UdpClient::exec() {
    while (1) {
        QByteArray msg;
        msg = uv_interface->generateMessage();
        // qDebug() << "[UDP_CLIENT] msg size " << "||" << msg.size();

        QNetworkDatagram datagram;
        datagram.setData(msg);
        senderSocket->writeDatagram(msg, sizeof(msg), QHostAddress("192.168.31.50"), 5000);
        msleep(100);
    }
}

void UdpClient::readPendingDatagrams() {
    while (receiverSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = receiverSocket->receiveDatagram();
        QByteArray msg = datagram.data();
        bool exception_caught = false;
        qDebug() << "hasPendingDatagrams";

        for( int i = 0 ; i < 10; i++){
            qDebug() << msg[i];
        }

        try {
            uv_interface->parseMessage(msg);
        }
        catch (const std::invalid_argument& error) {
            // qDebug() << "[UDP_CLIENT_ERROR] " << error.what();
            exception_caught = true;
        }
        if (!exception_caught) {
            // qDebug() << "[UDP_CLIENT] Message parced " << messageType << "||" << msg.size();
            emit dataUpdated();
        }
    }
}

void UdpClient::connectToHost() {
    // QHostAddress udpQHostAddress;
    // // qDebug() << "connectToHost";
    // if (!udpQHostAddress.setAddress(uv_interface->getUdpHostAddress())) {
    //     std::stringstream errorStream;
    //     errorStream << "Parsing UDP Host Address error. Address: [" <<
    //         uv_interface->getUdpHostAddress().toStdString() << "]";
    //     throw std::invalid_argument(errorStream.str());
    //     return;
    // }

    // qDebug() << "before connectToHost";

    // receiverSocket->connectToHost(QHostAddress("192.168.31.100"), 5001);

    // qDebug() << "after connectToHost";

    // if (!receiverSocket->waitForConnected(1000)) {
    //     throw std::invalid_argument("Can't connect to host, connection timeout");
    // }
}
