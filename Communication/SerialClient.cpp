#include "SerialClient.h"
#include "UV/iserverdata.h"
#include "ThrusterSettings/ThrusterWindow.h"

#include <QString>
#include <QDebug>

const int MAX_COM_ID = 20;

SerialClient::SerialClient() {
    interface = new IServerData();
}

SerialClient::~SerialClient() {
    // serialPort->close();
    // free(serialPort);
    // delete serialPort;
    // delete interface;
}

bool SerialClient::portConnect(int port) {
    QString str;
#ifdef unix
    str = "/dev/ttyUSB"; // небходимо открыть доступ к порту не из под sudo (sudo chmod a+rwx /dev/ttyUSBx)
#else
    str = "COM";
#endif
    str.append(QString::number(port));

    qDebug() << "COM_SERVER: Trying to open port " << str;

    serialPort = new QSerialPort(str);
    serialPort->setBaudRate(QSerialPort::BaudRate::Baud57600, QSerialPort::AllDirections);
    serialPort->setDataBits(QSerialPort::DataBits::Data8);
    serialPort->setParity(QSerialPort::Parity::NoParity);
    serialPort->setStopBits(QSerialPort::StopBits::OneStop);
    serialPort->setFlowControl(QSerialPort::FlowControl::NoFlowControl);

    if (serialPort->open(QIODeviceBase::ReadWrite)) {
        qDebug() << "COM_SERVER: port" << str << "successfully opened!";
    } else {
        qDebug() << serialPort->error();
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

        msg = interface->generateMessage();

        serialPort->clear();
        serialPort->write(msg, msg.size());
        serialPort->flush();

        serialPort->waitForReadyRead(100); // возможны проблемы с этой строчке при включенном bluetooth

        long long bytesAvailiable = serialPort->bytesAvailable();
        if (bytesAvailiable > 0) {
            msg.clear();
            msg.push_back(serialPort->readAll());
            // qDebug() << "[SERIAL_CLIENT] Message received. Bytes: " << msg.size();
            bool exception_caught = false;
            try {
                interface->parseMessage(msg);
            }
            catch (const std::invalid_argument& error) {
                // qDebug() << "[SERIAL_CLIENT] Parsing error: " << error.what();
                exception_caught = true;
            }
            if (!exception_caught) {
                // emit dataUpdatedSerialClient(); // TODO: попробовать вызывать dataUpdatedSerialClient() отсюда
            }
        } else {
            // qDebug() << "[SERIAL_CLIENT] Didn't receive answer for message " << messageType;
            // qDebug() << "[SERIAL_CLIENT] Bytes available:" << bytesAvailiable;
            serialPort->readAll();
        }
        emit dataUpdatedSerialClient();
    }
}
