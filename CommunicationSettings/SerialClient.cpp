#include "SerialClient.h"
#include "UV/iserverdata.h"
#include "ThrusterSettings/ThrusterWindow.h"

#include <QString>
#include <QDebug>

const int MAX_COM_ID = 20;

SerialClient::SerialClient(e_MessageTypes connectionType) {
    messageType = connectionType;
    qDebug() << connectionType;
//    timeoutTimer = new QTimer();
//    connect(timeoutTimer, SIGNAL(timeout()), this, SLOT(timerTick()));

    interface = new IServerData();
}

bool SerialClient::portConnect(int port) {
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

    if (serialPort->open(QIODevice::ReadWrite)) {
        qDebug() << "COM_SERVER: port" << str << "successfully opened!";
    } else {
//        qDebug() << " serial port openning error";
//        qDebug() << serialPort->error();
        delete serialPort;
        return false;
    }
    return true;
}

void SerialClient::run() {
    bool opened = false;
    for (int i = 0; i < MAX_COM_ID; i++) {
        opened = portConnect(i);
        if (opened) {
            break;
        }
    }

    if (opened) {
        exec();
    }
}

int SerialClient::exec() {
    while (1) {
        QByteArray msg;
        if (messageType == MESSAGE_DIRECT) {
            changeThrusterToNext();
        }
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
            catch (const std::invalid_argument &error) {
//                qDebug() << "[SERIAL_CLIENT] Parsing error: " << error.what();
                exception_caught = true;
            }
            if (!exception_caught) {
                //emit dataUpdated();
            }
        } else {
//            qDebug() << "[SERIAL_CLIENT] Didn't receive answer for message " << messageType;
//            qDebug() << "[SERIAL_CLIENT] Bytes available:" << bytesAvailiable;
            serialPort->readAll();
        }
        emit dataUpdated();
    }
}

void SerialClient::changeSelectedConnectionType(e_MessageTypes connectionType) {
    messageType = connectionType; // проверить, вызывается ли он быстрее чем exec()
    qDebug() << connectionType;
}

void SerialClient::changeThrusterToNext() {
    for (int i = interface->getCurrentThruster(); i < interface->getThrusterAmount() - 1;) {
        interface->changeCurrentThruster(++i);

        if (i == interface->getThrusterAmount()) {
            i = 0;
        }
        break;
    }
}
