#ifndef QKX_COEFFS_H
#define QKX_COEFFS_H

#include <QObject>
#include <QUdpSocket>
#include <QTime>
#include <QTimer>
#include "qpiconfig.h"



#define __BYTES_IN_PACKET 4000
#define KX_X_COUNT 1000

extern QVector<double> K;

template<typename T> inline T piMax(const T & f, const T & s) {return ((f < s) ? s : f);}
#define piMaxi piMax<int>


//class __KPi
//{

//    Q_OBJECT

//public:
#pragma pack (push, 1)
    struct KX_K_Sync {
        uchar type; //0хА - значит, что передаются коэффициенты
        uchar addr_to; //
        int count;
        int full_count;
        int first_index;
        uchar coeffs[__BYTES_IN_PACKET];
        uint checksum;
    };
#pragma pack (pop)

//    __KPi(const QString & config, const QString & name, bool _pult = false) {
//        QPIConfig conf(config, QIODevice::ReadOnly);
//        QPIConfig::Entry ce = conf.getValue(name);
//        to_k.type = from_k.type = ce.getValue("type", 0xA);
//        to_k.addr_to = ce.getValue("addr_k", 0x15);
//        from_k.addr_to = ce.getValue("addr_pult", 0x75);
//        if (_pult) {uchar n=to_k.addr_to; to_k.addr_to = from_k.addr_to; from_k.addr_to=n;}
//    }
//    KX_K_Sync to_k, from_k;
//private:
//


//    }
//};


class Qkx_coeffs : public QObject {
   Q_OBJECT
public:
    explicit Qkx_coeffs(const QString & config, const QString & name = "k", bool _pult = false, QObject *parent = 0);
    virtual ~Qkx_coeffs();
    void readCoeffs();
    void writeCoeffs();
    void sendCoeffs();
    void receiveCoeffs();
//
    bool isReady() const {return !waitingCommit;}
    const QString & fileName() const {return fname;}
    int coeffsCount() {coeffs_cnt = K.size(); return coeffs_cnt;}
    const QString & formula(int index) const {return formulas[index];}
    void setFormula(int index, const QString & f) {formulas[index] = f;}
    void setKFile(const QString & f);

signals:
    void sendSucceed();
    void sendFailed();
    void receiveSucceed();
    void receiveFailed();



private:
    void renew();
    uint checksum_i(const void *data, int size);
    bool validate(const KX_K_Sync & data) {
        return (data.checksum == checksum_i(&data, sizeof(data) - 4));
    }
    void aboutSend() {
        to_k.checksum = checksum_i(&to_k, sizeof(to_k) - 4);
    }

    QUdpSocket * k_protocol;
    KX_K_Sync to_k, from_k, k_syns;
    bool pult_, waitingCommit;
    int received_cnt, coeffs_cnt;
    QString fname, config_, name_, addr_k, addr_pult;
    QString ip_k, ip_pult;
    int port_k, port_pult;
    QStringList formulas;
    QByteArray k_content, k_tmp;
    QTime tm;
    QTimer *timer;

private slots:
    void received();
    void tick();
};



#endif // QKX_COEFFS_H
