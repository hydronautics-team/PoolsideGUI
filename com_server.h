#ifndef COM_SERVER_H
#define COM_SERVER_H

#include <QThread>
#include <QSerialPort>

class COM_Server : public QObject
{
    Q_OBJECT

public:
    COM_Server();
    ~COM_Server();

    void process();

signals:
    void error(QString err);

private:
    QSerialPort *serialPort;

    bool connect(int port);
};

#endif // COM_SERVER_H
