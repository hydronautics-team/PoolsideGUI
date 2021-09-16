#include "serial_client.h"
#include "UV/iserverdata.h"
#include "SettingsWindow/ThrusterSettings/thrustersettings.h"

#include <QString>
#include <QDebug>

const int MAX_COM_ID = 20;

Serial_Client::Serial_Client()
{
    timeoutTimer = new QTimer();
    connect(timeoutTimer, SIGNAL(timeout()), this, SLOT(timerTick()));

    interface = new IServerData();
}

bool Serial_Client::portConnect(int port)
{
    QString str;
#ifdef unix
    str = "/dev/ttyUSB"; // небходимо открыть доступ к порту не из под sudo (sudo chmod a+rwx /dev/ttyUSBx)
#else
    str = "COM";
#endif

    str.append(QString::number(port));

//    qDebug () << "COM_SERVER: Trying to open port " << str;

    serialPort = new QSerialPort(str);
    serialPort->setBaudRate(QSerialPort::BaudRate::Baud57600, QSerialPort::AllDirections);
    serialPort->setDataBits(QSerialPort::DataBits::Data8);
    serialPort->setParity(QSerialPort::Parity::NoParity);
    serialPort->setStopBits(QSerialPort::StopBits::OneStop);
    serialPort->setFlowControl(QSerialPort::FlowControl::NoFlowControl);

    if(serialPort->open(QIODevice::ReadWrite)) {
        qDebug() << "COM_SERVER: port" << str << "successfully opened!";
    }
    else {
//        qDebug() << " serial port openning error";
//        qDebug() << serialPort->error();
        delete serialPort;
        return false;
    }
    return true;
}

void Serial_Client::run()
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

int Serial_Client::exec()
{
    while(1)
    {
        int messageType = MESSAGE_NORMAL;

        QByteArray msg;
        msg = interface->generateMessage(messageType);

//        qDebug() << "[SERIAL_CLIENT] Sending message type " << messageType << "||" << msg.size();
//        qDebug() << msg;

        serialPort->clear();
        serialPort->write(msg, msg.size());
        serialPort->flush();

        serialPort->waitForReadyRead(100); //из-за этой строчки у Гриши появляется
        // ASSERT: "bytesTransferred == writeChunkBuffer.size()" in file qserialport_win.cpp, line 503
        // !!!!!!!!!!!!!это было из-за включенного Bluethuse на ноуте!!!!!!!!!!!___________

        long long bytesAvailiable = serialPort->bytesAvailable();
        if (bytesAvailiable > 0) {
            msg.clear();
            msg.push_back(serialPort->readAll());

//            qDebug() << "[SERIAL_CLIENT] Message received. Bytes: " << msg.size();

            bool exception_caught = false;
            try {
                interface->parseMessage(msg, messageType);
            }
            catch(const std::invalid_argument& error) {
//                qDebug() << "[SERIAL_CLIENT] Parsing error: " << error.what();
                exception_caught = true;
            }
            if(!exception_caught) {
                //emit dataUpdated();
            }
        }
        else {
//            qDebug() << "[SERIAL_CLIENT] Didn't receive answer for message " << messageType;
//            qDebug() << "[SERIAL_CLIENT] Bytes available:" << bytesAvailiable;
            serialPort->readAll();
        }

        emit dataUpdated();
    }
}

void Serial_Client::changeSelectedThruster(unsigned int slot)
{
    interface->changeCurrentThruster(slot);
}


