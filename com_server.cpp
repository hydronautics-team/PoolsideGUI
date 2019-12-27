#include "com_server.h"
#include "UV/iserverdata.h"
#include "global.h"

#include <QString>
#include <QDebug>

const int MAX_COM_ID = 20;

COM_Server::COM_Server()
{
    timeoutTimer = new QTimer();
    connect(timeoutTimer, SIGNAL(timeout()), this, SLOT(timerTick()));

    interface = new IServerData(&UVState, &UVMutex);
}

bool COM_Server::portConnect(int port)
{
    QString str;
    if (OS == "unix") {
        str = "/dev/ttyUSB";
    }
    else if (OS == "win32") {
        str = "COM";
    }

    str.append(QString::number(port));

    qDebug () << "COM_SERVER: Trying to open port " << str;

    serialPort = new QSerialPort(str);
    //serialPort->setPortName(str);
    serialPort->setBaudRate(QSerialPort::BaudRate::Baud57600, QSerialPort::AllDirections);
    serialPort->setDataBits(QSerialPort::DataBits::Data8);
    serialPort->setParity(QSerialPort::Parity::NoParity);
    serialPort->setStopBits(QSerialPort::StopBits::OneStop);
    serialPort->setFlowControl(QSerialPort::FlowControl::NoFlowControl);

    if(serialPort->open(QIODevice::ReadWrite)) {
        qDebug() << " successfully opened!";
    }
    else {
        qDebug() << " serial port openning error";
        qDebug() << serialPort->error();
        delete serialPort;
        return false;
    }
    return true;
}

void COM_Server::run()
{
    bool opened = false;
    for(int i=0; i<MAX_COM_ID; i++) {
        opened = portConnect(i);
        if(opened) {
            break;
        }
    }

    if(opened) {
        exec();
    }
}

int COM_Server::exec()
{
    while(1)
    {
        QByteArray msg;
        interface->getData();
        msg = interface->getMessage(interface->internal_state.messageType);

        qDebug() << "Sending message type " << interface->internal_state.messageType << "||" << msg.size();
        qDebug() << msg;

        serialPort->clear();
        serialPort->write(msg, msg.size());
        serialPort->flush();

        serialPort->waitForReadyRead(100);
        long long bytesAvailible = serialPort->bytesAvailable();
        if (bytesAvailible > 0) {
            msg.clear();
            msg.push_back(serialPort->readAll());

            qDebug() << "Message received, type " << interface->internal_state.messageType;
            qDebug() << msg;

            interface->passMessage(msg, interface->internal_state.messageType);
            emit dataUpdated();
        }
        else {
            qDebug() << "Didn't receive answer for message " << interface->internal_state.messageType;
            qDebug() << "Bytes available:" << bytesAvailible;
            serialPort->readAll();
        }
    }
}


