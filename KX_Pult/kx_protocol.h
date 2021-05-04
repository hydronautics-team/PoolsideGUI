#ifndef KX_PROTOCOL_H
#define KX_PROTOCOL_H

#include <QUdpSocket>
#include <iostream>
#include <fstream>
#include <QFile>
#include <QBitArray>
#include <QString>
#include <QThread>
#include <QTimer>
#include <QDebug>
#include <QString>
#include <QObject>
#include <QBasicTimer>
#include <QtCore>

#include "configdata.h"
#include "qpiconfig.h"

#define X_NUM 20

//X and ki protocols
#define MSG_X 0xAA
#define MSG_KI 0xBB
#define X_FROM_PULT 0x0A
#define X_FROM_BORT 0x0B

#define CHISLO_MAX_X   2000

;

#pragma pack(push, 1)
struct Header {
    quint8 type;
    quint8 addr_to;
};

struct NumbersX: Header {
    int x_num[X_NUM];
    unsigned int checksum;
};

struct DataX: Header {
    int x_num[X_NUM];
    double x_data[X_NUM];
    unsigned int checksum;
};
#pragma pack(pop)

class x_protocol: public QObject {
    Q_OBJECT

private:

    QHostAddress ip_Pult;

    quint16 port_Pult;

    quint16 port_ROV;

    qint32 frequency_Pult;

    QTimer       *timer;

    unsigned int c_checksum(unsigned char *buffer,int len);

    quint8 addr_from;

public:

    x_protocol(const QString & config, const QString & name, double (*_x)[2], QObject *parent = 0);                  //(char *in_ip, int in_port, int out_port, float (*_x)[2], int _x_count, QObject *parent = 0);
      ~x_protocol();

    long int packets_received;

    int packets_lost;

    int packets_sent;

    double (*x_vnutri)[2];

    int x_count;

    NumbersX x_index; //received indexes of X

    DataX x_value;

    QUdpSocket* ReceiveFromKXnotebook;

    QUdpSocket* TransmitDataKXnotebook;

private slots:

    void readdata();

    void send_data();

};



#endif
