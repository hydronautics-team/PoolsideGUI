#include "kx_protocol.h"



unsigned int x_protocol::c_checksum(unsigned char *buffer,int len)
{
    unsigned int result=0;
    for (int i=0;i<len;i++)
    result+=buffer[i];
    return ~(result+1);
}

x_protocol::~x_protocol()
{
   delete ReceiveFromKXnotebook;
   delete TransmitDataKXnotebook;
   delete timer;

}
  x_protocol::x_protocol(const QString & config, const QString & name, double (*_x)[2],  QObject *parent) : QObject(parent)    //(char *in_ip, int in_port, int out_port, float (*_x)[2], int _x_count, QObject *parent) : QObject(parent)
{
    QPIConfig conf(config, QIODevice::ReadOnly);
    QPIConfig::Entry & e(conf.getValue(name));

    ip_Pult = QHostAddress(e.getValue("sender.ip").value());
    //ip_k = e.getValue("sender.ip").value();
    port_Pult = e.getValue("sender.port", 0).value().toInt();
    port_ROV = e.getValue("receiver.port", 0).value().toInt();

    qDebug() << "ip Pult" << ip_Pult;
    qDebug() << "port_Pult" << port_Pult;
    qDebug() << "port_ROV" << port_ROV;

    x_vnutri  = _x;

    x_count   = e.getValue("count",0).value().toInt();                         //_x_count);
    qDebug()  << "count" << x_count;
    packets_received = 0;
    packets_lost = 0;
    packets_sent = 0;

    frequency_Pult = e.getValue("sender.frequency",0).value().toFloat();    //20. Hz

    for (int i=0; i<X_NUM; i++)
         x_index.x_num[i] = -1;

    ReceiveFromKXnotebook = new QUdpSocket(this);

    TransmitDataKXnotebook = new QUdpSocket(this);

    timer = new QTimer(this);

    ReceiveFromKXnotebook -> bind(port_ROV);            //биндится номер порта (на борту ТНПА), с которого будем читать

    connect(timer, &QTimer::timeout, this, &x_protocol::send_data);

    connect(ReceiveFromKXnotebook, &QUdpSocket::readyRead,this, &x_protocol::readdata);

    x_value.type = e.getValue("type");                 //MSG_X
    x_value.addr_to = e.getValue("addr_pult");         // X_FROM_BORT;

    addr_from = e.getValue("addr_x", 0x0A);

    qDebug() <<"x_value.type" << x_value.type;
    qDebug() <<"x_value.addr_to" << x_value.addr_to;
    qDebug() <<"addr_from" << addr_from;
    timer -> start(1000./frequency_Pult);

    qDebug()<<"x_protocol created\n";

}

void x_protocol:: readdata()
{
    QByteArray baDatagram;
    NumbersX tmp;

    do
    {
        baDatagram.resize(ReceiveFromKXnotebook->pendingDatagramSize());
        ReceiveFromKXnotebook->readDatagram(baDatagram.data(), baDatagram.size());
    }
    while(ReceiveFromKXnotebook->hasPendingDatagrams());


    memcpy(&tmp,baDatagram.data(),sizeof(tmp));

    //qDebug() << "from readdata(): tmp.type == " << tmp.type << "tmp.addr_to == " << tmp.addr_to << endl;

    if ((tmp.type == x_value.type) && (tmp.addr_to== addr_from)) {
        if (tmp.checksum == c_checksum(reinterpret_cast<unsigned char*>(&tmp),sizeof(tmp) - sizeof(unsigned int))) {
            x_index = tmp;
            //             for (int i = 0; i < X_NUM; i++)
            //                  qDebug() << " x_index.x_num["<< i << "] == " <<  x_index.x_num[i] << endl;
            packets_received++;
        }
        else {
            packets_lost++;
        }
    }
}

void x_protocol::send_data() {
     //forming x protocol

    for (int i=0; i<X_NUM; i++) {
          x_value.x_num[i] = x_index.x_num[i];

          if((x_value.x_num[i] > 0) && (x_value.x_num[i] < x_count))
                   x_value.x_data[i] =  x_vnutri[ x_value.x_num[i] ][0];
               else
                   x_value.x_data[i]=0.0f;
//          qDebug() << " x_value.x_data["<< i << "] == " <<  x_value.x_data[i] << endl;
         }
         x_value.checksum = c_checksum(reinterpret_cast<unsigned char*>(&x_value),sizeof(x_value)-sizeof(unsigned int));
//        qDebug()<< "real size: " << sizeof(x_value);

         TransmitDataKXnotebook-> writeDatagram(reinterpret_cast<char*>(&x_value), sizeof(x_value), ip_Pult, port_Pult);
//        qDebug()<< "bytes sent: " << "Data Send Complete" << endl;

   }
