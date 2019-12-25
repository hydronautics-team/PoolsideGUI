#ifndef SERVERDATA_TEST_H
#define SERVERDATA_TEST_H

#include <QThread>
#include <QSerialPort>
#include <QTimer>

#include "UV/iserverdata.h"

class Serverdata_Test : public QObject
{
    Q_OBJECT

public:
    explicit Serverdata_Test(QObject *parent = 0);

//private slots:
//    void normalRequest();

};

#endif // SERVERDATA_TEST_H
