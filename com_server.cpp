#include "com_server.h"

#include <QString>
#include <QDebug>

//const int MAX_COM_ID = 20;

COM_Server::COM_Server()
{

}

COM_Server::~COM_Server()
{

}

bool COM_Server::connect(int port)
{
    //int isOpened = false;

    QString str;
    if (OS == "unix") {
        str = "/dev/ttyUSB";
    }
    else if (OS == "win32") {
        str = "COM";
    }

    str.append(QString::number(port));

    qDebug () << "COM_SERVER: Trying to open port " << str;
/*
    serialPort = new QSerialPort(str);
    serialPort->setBaudRate(settings->connection->baudRate, QSerialPort::AllDirections);
    serialPort->setDataBits(settings->connection->dataBits);
    serialPort->setParity(settings->connection->parity);
    serialPort->setStopBits(settings->connection->stopBits);
    serialPort->setFlowControl(settings->connection->flowControl);

    try {
        isOpened = newPort->open(QIODevice::ReadWrite);
    } catch(...) {
        std::cout << " serial port openning error" << std::endl;
        emit info("Serial port openning error");
        delete newPort;
        return false;
    }

    if (isOpened) {
        std::cout << " successfully opened!" << std::endl;
        sendTimer->start(REQUEST_DELAY);
    } else {
        std::cout << ". Unable to open serial port" << std::endl;
        emit info("Unable to open serial port");
        delete newPort;
        return false;
    }
*/
    return true;
}
