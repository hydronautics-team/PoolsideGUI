#include "tcpServer.h"
#include <vector>
#include <opencv2/opencv.hpp>

tcpServer::tcpServer() : context_(1), socket_(new zmq::socket_t(context_, zmq::socket_type::rep)), compression_("1"), cmp_(1), port_(10000) {
    socket_->bind("tcp://*:" + std::to_string(port_));
    last_fps_ = std::chrono::high_resolution_clock::now();
}

void tcpServer::start(int port) {
    if (port != port_) {
        port_ = port;
        socket_->close();
        delete socket_;
        socket_ = new zmq::socket_t(context_, zmq::socket_type::rep);
        socket_->bind("tcp://*:" + std::to_string(port_));
    }
    bool state = true;
    bool connected = true;
    while (state && connected) {
        connected = getMessage();
        emit checkRunState(&state);
        emit checkCompressionState(&cmp_);
        compression_ = std::to_string(cmp_);
        emit updateFPS(1000 / std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - last_fps_).count());
        last_fps_ = std::chrono::high_resolution_clock::now();

    }
}

bool tcpServer::getMessage() {
    zmq::message_t request;
    try {
        socket_->recv(request, zmq::recv_flags::none);
    } catch (const zmq::error_t& /* context was terminated */) {
        return false;
    }
    //for C++ client
    cv::Mat mImg(1080, 1920, CV_8UC3, const_cast<char*>(request.to_string().c_str()));
    emit readyUpdatePixmap(QImage(mImg.data, mImg.cols, mImg.rows, mImg.step, QImage::Format_RGB888).rgbSwapped());

    //for Python client
    /*
    std::string str_data = request.to_string();
    cv::Mat mImg = cv::imdecode(std::vector<char>{str_data.begin(), str_data.end()}, 1);
    cv::resize(mImg, mImg, cv::Size(1920, 1080), 0, 0, cv::INTER_CUBIC);
    emit readyUpdatePixmap(QImage(mImg.data, mImg.cols, mImg.rows, mImg.step, QImage::Format_RGB888).rgbSwapped());
    */
    socket_->send(zmq::buffer(compression_), zmq::send_flags::none);
    return true;
}

tcpServer::~tcpServer() noexcept {
    socket_->close();
    delete socket_;
}
