#ifndef POOLSIDEGUI_TCPSERVER_H
#define POOLSIDEGUI_TCPSERVER_H

#include <QObject>
#include <QImage>
#include <string>
#include <chrono>
#include <zmq.hpp>

class tcpServer : public QObject{
    Q_OBJECT
private:
    zmq::context_t context_;
    zmq::socket_t *socket_;
    std::string compression_;
    int cmp_;
    int port_;
    std::chrono::time_point<std::chrono::high_resolution_clock> last_fps_;
    bool getMessage();
signals:
    void readyUpdatePixmap(const QImage& img);
    void checkRunState(bool *state);
    void checkCompressionState(int *cmp);
    void updateFPS(int fps);
public:
    explicit tcpServer();
    ~tcpServer() noexcept;
public slots:
    void start(int port);
};

#endif //POOLSIDEGUI_TCPSERVER_H