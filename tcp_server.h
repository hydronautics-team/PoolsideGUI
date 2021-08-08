#ifndef POOLSIDEGUI_TCP_SERVER_H
#define POOLSIDEGUI_TCP_SERVER_H

#include <boost/asio.hpp>
#include <boost/asio.hpp>
#include "mainwindow.h"

using boost::asio::ip::tcp;

class Server {
private:
    tcp::acceptor acceptor_;
    tcp::socket socket_;
    MainWindow& MainWindow_;

public:
    explicit Server(boost::asio::io_service &io_service, MainWindow& window);

    void get_message();
};

#endif //POOLSIDEGUI_TCP_SERVER_H
