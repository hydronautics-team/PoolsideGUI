#ifndef SERVERDATA_TEST_H
#define SERVERDATA_TEST_H

#include <QObject>

#include "UV/iserverdata.h"

class Serverdata_Test : public QObject
{
    Q_OBJECT

public:
    explicit Serverdata_Test(QObject *parent = 0);

private slots:
    void directRequest();

private:
    QByteArray ideal_message;
    uint16_t ideal_checksum;
};

#endif // SERVERDATA_TEST_H
