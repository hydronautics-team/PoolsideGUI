#ifndef POOLSIDEGUI_TCPSETTINGS_H
#define POOLSIDEGUI_TCPSETTINGS_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QGroupBox>
#include <QSpinBox>
#include <QLabel>

class tcpSettings : public QWidget {
    Q_OBJECT
private slots:
    void changeCompressionSliderValue(int value);
    void changeCompressionSpinBoxValue(int value);
    void changePortSliderValue(int value);
    void changePortSpinBoxValue(int value);
    void startBtnClicked();
    void stopBtnClicked();
    void rebuildBtnClicked();
public slots:
    void returnRunState(bool *state);
    void returnCompressionState(int *cmp);
    void setFPS(int fps);
signals:
    void start(int port);
    void rebuildServer();
private:
    QVBoxLayout *qvbox_;
    QVBoxLayout *qvboxTop_;
    QVBoxLayout *qvboxLeft_;
    QVBoxLayout *qvboxRight_;
    QHBoxLayout *qhboxSettings_;
    QLabel *fpsLabel_;
    QGroupBox *infoGroup_;
    QLabel *portLabel_;
    QSlider *portSlider_;
    QSpinBox *portSpinBox_;
    QLabel *compressionLabel_;
    QSlider *compressionSlider_;
    QSpinBox *compressionSpinBox_;
    QPushButton *startBtn_;
    QPushButton *stopBtn_;
    QGroupBox *settingsGroup_;
    QPushButton *rebuildBtn_;
    bool run_;
public:
    explicit tcpSettings(QWidget *parent = nullptr);
    ~tcpSettings();
};


#endif //POOLSIDEGUI_TCPSETTINGS_H
