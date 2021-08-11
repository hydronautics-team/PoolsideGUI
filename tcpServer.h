#ifndef POOLSIDEGUI_TCPSERVER_H
#define POOLSIDEGUI_TCPSERVER_H

#include <QObject>
#include <QByteArray>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class tcpServer : public QObject{
    Q_OBJECT
private:
    tcp::acceptor acceptor_;
    tcp::socket socket_;
signals:
    void readyUpdatePixmap(const QByteArray& array);
public:
    explicit tcpServer(boost::asio::io_service &io_service);
    void GetMessage();
public slots:
    void Accept();
};

#endif //POOLSIDEGUI_TCPSERVER_H