#ifndef CONFIGDATA_H
#define CONFIGDATA_H


#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QObject>
#include <QDebug>

QT_USE_NAMESPACE

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE

struct Data
{
    QString macadress;
    QString ipadress;
    QString device;
    QString calibration;
    QString sender_ip;
    QString receiver_ip;
    qint32  device_frequency;
    qint32  baudRate;
    qint32  sender_port;
    qint32  receiver_port;
    qint32  sender_frequency;
    qint32  receiver_frequency;
    quint8  type;
    quint8  addr_x;
    quint8  addr_k;
    quint8  addr_pult;
    quint16 count;
    QString ki_file;
} ;

class ConfigData : public QObject
{
   Q_OBJECT

public:

    ConfigData(const QString & configFile, QObject *parent = 0);
    ConfigData(const QString & configFile, const QString &name, QObject *parent = 0);
    ~ConfigData();

    Data data;

    void getValue(const QString & name);


private:
    QTextStream  standardOutput;
    QFile  dataFile;
    QStringList list;
    int jmax;
};

#endif // CONFIGDATA_H
