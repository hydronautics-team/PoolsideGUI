#include "tcpServer.h"
#include <QByteArray>

Server::Server(boost::asio::io_service &io_service, MainWindow &window) : acceptor_(io_service,
                                                                                tcp::endpoint(tcp::v4(), 2001)),
                                                                                socket_(io_service), MainWindow_(window) {
    acceptor_.accept(socket_);
}

void Server::get_message() {
    boost::asio::streambuf data_;
    boost::asio::read_until(socket_, data_, "end");
    std::string str_data((std::istreambuf_iterator<char>(&data_)), std::istreambuf_iterator<char>());
    str_data.erase(str_data.end() - 3, str_data.end());
    if (str_data.empty()) {
        return;
    }
    QByteArray arr(str_data.c_str(), static_cast<int>(str_data.size()));
    MainWindow_.updateArray(arr);
}

