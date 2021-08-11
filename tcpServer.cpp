#include "tcpServer.h"
#include <iostream>
#include <QByteArray>

tcpServer::tcpServer(boost::asio::io_service &io_service) : acceptor_(io_service,
                                                                      tcp::endpoint(tcp::v4(), 2001)),
                                                            socket_(io_service) {}

void tcpServer::Accept() {
    acceptor_.accept(socket_);
    while (true) {
        GetMessage();
    }
}

void tcpServer::GetMessage() {
    boost::asio::streambuf data_;
    boost::asio::read_until(socket_, data_, "end");
    std::string str_data((std::istreambuf_iterator<char>(&data_)), std::istreambuf_iterator<char>());
    str_data.erase(str_data.end() - 3, str_data.end());
    if (str_data.empty()) {
        return;
    }
    QByteArray arr(str_data.c_str(), str_data.size());
    emit readyUpdatePixmap(arr);
}
