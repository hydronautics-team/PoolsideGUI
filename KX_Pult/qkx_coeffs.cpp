#include "qkx_coeffs.h"
#include <QDataStream>
#include <QThread>

QVector<double> K;

Qkx_coeffs::Qkx_coeffs(const QString & config, const QString & name, bool _pult, QObject *parent) : QObject(parent) {
    QPIConfig conf(config, QIODevice::ReadOnly);
    QPIConfig::Entry & e(conf.getValue(name));
    fname = e.getValue("file", "k.dat").value(); //k.dat
    ip_pult = e.getValue("sender.ip").value();
    ip_k = e.getValue("receiver.ip").value();
    port_pult = e.getValue("sender.port", 0);
    port_k = e.getValue("receiver.port", 0);
    to_k.type = from_k.type = e.getValue("type", 0xA);
    to_k.addr_to = e.getValue("addr_k", 0x15);
    from_k.addr_to = e.getValue("addr_pult", 0x75);
    timer = new QTimer(this);
    k_protocol=NULL;
    connect(timer, SIGNAL(timeout()), SLOT(tick()));


    qDebug() << "sender.ip" << ip_pult << "sender.port" << port_pult;
    qDebug() << "receiver.ip" << ip_k << "receiver.port" << port_k;
    qDebug() << "to_k.addr_to" << to_k.addr_to;
    qDebug() << "from_k.addr_to" << from_k.addr_to;

    readCoeffs();
    int ns = piMaxi(conf.getValue(name).getValue("count", 0), K.size());
    if (ns > K.size()) {
        K.resize(ns);
        while (formulas.size() < ns) formulas.append("");
        writeCoeffs();
    }
    config_ = config;
    name_ = name;
    pult_ = _pult;
    renew();
    //startTimer(10);
}

Qkx_coeffs::~Qkx_coeffs(){

}

void Qkx_coeffs::readCoeffs() {
    {
        QPIConfig conf(fname, QIODevice::ReadOnly);
        int cnt = conf.rootEntry().childCount();
        K.resize(cnt);
        while (formulas.size() < cnt)
            formulas.append("");
        QString kn, cf;
        for (int i = 0; i < cnt; i++) {
            kn = "k" + QString::number(i);
            K[i] = conf.getValue(kn, 0.f);
            //qDebug() << K[i];
            cf = conf.getValue(kn + ".formula", "").value();
            if (cf.isEmpty()) cf = QString::number(K[i]);
            formulas[i] = cf;
        }
    }
    QFile file (fname);
    file.open(QIODevice::ReadOnly);
    k_content = file.readAll();
    //qDebug() << k_content.size();
    qDebug() << "Readed" << K.size() << "coefficients in" << k_content.size() << "bytes";
    coeffs_cnt = K.size();
}

void Qkx_coeffs::writeCoeffs() {
    QFile::remove(fname);
    QFile file(fname);
    file.open(QIODevice::ReadWrite);
    QTextStream stream(&file);

    for (int i = 0; i < K.size(); i++) {
        stream << "k" + QString::number(i) << " = " << QString::number(K[i]).replace(",",".") << "\n";
        stream << "k" + QString::number(i) << ".formula = " << formulas[i] << "\n";
    }
    //conf.writeAll();
    k_content = file.readAll();
    //qDebug() << k_content.size();
    qDebug() << "Written" << K.size() << "coefficients in" << k_content.size() << "bytes";
    coeffs_cnt = K.size();
}

void Qkx_coeffs::setKFile(const QString & f) {
    //INFO: этот метод можно использовать для установки нужного файла коэффициентов
    fname = f;
    readCoeffs();
}


void Qkx_coeffs::renew() {
    if (k_protocol) {
        delete k_protocol;
    }
    k_protocol = new QUdpSocket(this);
    k_protocol->bind(QHostAddress(ip_k),port_k);
    qDebug() << k_protocol->errorString();
    qDebug() << "binded to" << k_protocol->state() << ", " <<
             ip_k << ":" << port_k;

    connect(k_protocol, SIGNAL(readyRead()),this, SLOT(received()));

    waitingCommit = false;
}

void Qkx_coeffs::received() {
   while(k_protocol->hasPendingDatagrams()) {
       qDebug() <<"Received SMth";
       KX_K_Sync rec;
        k_protocol->readDatagram((char *)&rec, sizeof(rec));
        if (rec.type != from_k.type || rec.addr_to != from_k.addr_to || !validate(rec)) {
            qDebug() <<"Invalid!";
            qDebug() << "rec.type:" << rec.type << "from_k.type" << from_k.type;
            qDebug() << "rec.addr_to" << rec.addr_to << "from_k.addr_to:" << from_k.addr_to;
            qDebug() << "Checksum validate" << validate(rec);
            continue;
        }
        from_k=rec;
        k_syns = from_k;
        if (waitingCommit) {
            if (k_syns.first_index != -1 ||
               k_syns.full_count != -1 ||
               k_syns.count != -k_content.size()) return;
            //cout << "commit received\n";
            waitingCommit = false;
            timer->stop();
    //        //cout << "send succeed\n";
            emit sendSucceed();
            return;
        } else {
            if (k_syns.first_index == -6 && k_syns.full_count == -6 && k_syns.count == -6) {
                //cout << "request received\n";
                sendCoeffs();
                return;
            };
        }
        if (k_syns.first_index < 0 || k_syns.count < 0) return;
        if (k_syns.first_index == 0) {
            //cout << "first receive\n";
            k_tmp.resize(k_syns.full_count);
            received_cnt = 0;
       }
        //for (int i = 0; i < k_syns.count; i++) K.at(k_syns.first_index + i) = k_syns.coeffs[i];
        //piCout << k_tmp.size() << k_syns.first_index << k_syns.count;
        memcpy(k_tmp.data() + k_syns.first_index, k_syns.coeffs, k_syns.count);
        received_cnt += k_syns.count;
        tm.restart();
    //    //cout << "received " << k_syns.count << " bytes with " << k_syns.first_index << " first\n";
        if (received_cnt < k_syns.full_count) return;
        //cout << "finally received " << received_cnt << " bytes\n";
        timer->stop();
        QFile::remove(fname);
        QFile conf(fname);
        conf.open(QIODevice::ReadWrite);
        conf.write(k_tmp);
        conf.close();
        readCoeffs();
    //    //writeCoeffs();
        to_k.full_count = to_k.first_index = -1;
        to_k.count = -received_cnt;
        aboutSend();
        k_protocol->writeDatagram((char*) &to_k, sizeof(to_k), QHostAddress(ip_pult), port_pult);
    //    k_protocol->send();
        waitingCommit = false;
        emit receiveSucceed();
    //    //cout << "receive succeed\n";
   }
}

void Qkx_coeffs::receiveCoeffs() {
    timer->stop();
    to_k.full_count = to_k.first_index = to_k.count = -6;
    aboutSend();
    k_protocol->writeDatagram((char*) &to_k, sizeof(to_k), QHostAddress(ip_pult), port_pult);
    //cout << "request send\n";
    //cout << "waiting for receive ...\n";
    waitingCommit = false;
    tm.restart();
    timer->start(10);
}


void Qkx_coeffs::sendCoeffs() {

    qDebug() << "Sending";
    timer->stop();
    int curcnt, pcnt = (k_content.size() - 1) / __BYTES_IN_PACKET + 1;
    to_k.full_count = k_content.size();
    for (int i = 0; i < pcnt; i++) {
        to_k.first_index = i * __BYTES_IN_PACKET;
        if (i == pcnt - 1) curcnt = k_content.size() % __BYTES_IN_PACKET;
        else curcnt = __BYTES_IN_PACKET;
//        //cout << "send " << curcnt << " coeffs\n";
        to_k.count = curcnt;
        memcpy(&to_k.coeffs, k_content.data() + to_k.first_index, curcnt);


//        //for (int j = 0; j < curcnt; j++) k_protocol->to_k.coeffs[j] = K.at(k_protocol->to_k.first_index + j);
        aboutSend();
        k_protocol->writeDatagram((char*)&to_k,sizeof(to_k),QHostAddress(ip_pult), port_pult);
//        //piMSleep(5);
        QThread::msleep(5);
    }
//    //cout << "waiting for commit ...\n";
    waitingCommit = true;
    tm.restart();
    timer->start(10);
}

void Qkx_coeffs::tick() {
    //piCout << "timer" << tm.elapsed_s();
    qDebug()<<"tick" <<tm.elapsed();
    if (tm.elapsed() < 10.) return;
    if (waitingCommit) {
        //cout << "commit timeout\n";
        //cout << "send failed\n";
        emit sendFailed();
    } else {
        //cout << "receive timeout\n";
        //cout << "receive failed\n";
        emit receiveFailed();
    }
    waitingCommit = false;
    timer->stop();
}

uint Qkx_coeffs::checksum_i(const void * data, int size) { // function for checksum (uint)
    uint c = 0;
    for (int i = 0; i < size; ++i)
        c += ((const uchar*)data)[i];
    return ~(c + 1);
}
