#include "tcpSettings.h"

tcpSettings::tcpSettings(QWidget *parent) : QWidget(parent), qvbox_(new QVBoxLayout(this)), qvboxTop_(new QVBoxLayout),
                                            qvboxLeft_(new QVBoxLayout),
                                            qvboxRight_(new QVBoxLayout), qhboxSettings_(new QHBoxLayout),
                                            fpsLabel_(new QLabel("FPS: ", this)),
                                            infoGroup_(new QGroupBox(tr("Info"))),
                                            portLabel_(new QLabel("Port", this)),
                                            portSlider_(new QSlider(Qt::Vertical, this)),
                                            portSpinBox_(new QSpinBox(this)),
                                            compressionLabel_(new QLabel("Compression", this)),
                                            compressionSlider_(new QSlider(Qt::Vertical, this)),
                                            compressionSpinBox_(new QSpinBox(this)),
                                            startBtn_(new QPushButton("Start", this)),
                                            stopBtn_(new QPushButton("Stop", this)),
                                            settingsGroup_(new QGroupBox(tr("Settings"))),
                                            rebuildBtn_(new QPushButton("Rebuild", this)), run_(false) {

    qvboxTop_->addWidget(fpsLabel_);
    infoGroup_->setLayout(qvboxTop_);

    portSlider_->setMinimum(1);
    portSlider_->setMaximum(65536);
    portSlider_->setValue(10000);
    portSlider_->setSingleStep(1);
    portSlider_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    portSpinBox_->setMinimum(1);
    portSpinBox_->setMaximum(65536);
    portSpinBox_->setValue(10000);
    portSpinBox_->setSingleStep(1);

    qvboxLeft_->addWidget(portLabel_);
    qvboxLeft_->addWidget(portSlider_);
    qvboxLeft_->addWidget(portSpinBox_);
    qvboxLeft_->addWidget(startBtn_);

    compressionSlider_->setMinimum(1);
    compressionSlider_->setMaximum(10);
    compressionSlider_->setValue(1);
    compressionSlider_->setSingleStep(1);
    compressionSlider_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    compressionSpinBox_->setMinimum(1);
    compressionSpinBox_->setMaximum(10);
    compressionSpinBox_->setValue(1);
    compressionSpinBox_->setSingleStep(1);

    qvboxRight_->addWidget(compressionLabel_);
    qvboxRight_->addWidget(compressionSlider_);
    qvboxRight_->addWidget(compressionSpinBox_);

    stopBtn_->setEnabled(false);
    qvboxRight_->addWidget(stopBtn_);

    qhboxSettings_->addLayout(qvboxLeft_);
    qhboxSettings_->addLayout(qvboxRight_);
    settingsGroup_->setLayout(qhboxSettings_);

    qvbox_->addWidget(infoGroup_);
    qvbox_->addWidget(settingsGroup_);

    rebuildBtn_->setEnabled(false);
    qvbox_->addWidget(rebuildBtn_);

    connect(portSlider_, SIGNAL(valueChanged(int)), this, SLOT(changePortSpinBoxValue(int)));
    connect(portSpinBox_, SIGNAL(valueChanged(int)), this, SLOT(changePortSliderValue(int)));
    connect(compressionSpinBox_, SIGNAL(valueChanged(int)), this, SLOT(changeCompressionSliderValue(int)));
    connect(compressionSlider_, SIGNAL(valueChanged(int)), this, SLOT(changeCompressionSpinBoxValue(int)));

    connect(startBtn_, &QPushButton::clicked, this, &tcpSettings::startBtnClicked);
    connect(stopBtn_, &QPushButton::clicked, this, &tcpSettings::stopBtnClicked);
    connect(rebuildBtn_, &QPushButton::clicked, this, &tcpSettings::rebuildBtnClicked);
}

void tcpSettings::changeCompressionSliderValue(int value) {
    compressionSlider_->setValue(value);
}

void tcpSettings::changeCompressionSpinBoxValue(int value) {
    compressionSpinBox_->setValue(value);
}

void tcpSettings::changePortSliderValue(int value) {
    portSlider_->setValue(value);
}

void tcpSettings::changePortSpinBoxValue(int value) {
    portSpinBox_->setValue(value);
}

void tcpSettings::startBtnClicked() {
    portSlider_->setEnabled(false);
    portSpinBox_->setReadOnly(true);
    rebuildBtn_->setEnabled(false);
    startBtn_->setEnabled(false);
    stopBtn_->setEnabled(true);
    run_ = true;
    emit start(portSpinBox_->value());
}

void tcpSettings::stopBtnClicked() {
    portSlider_->setEnabled(true);
    portSpinBox_->setReadOnly(false);
    rebuildBtn_->setEnabled(true);
    startBtn_->setEnabled(true);
    stopBtn_->setEnabled(false);
    run_ = false;
}

void tcpSettings::returnRunState(bool *state) {
    *state = run_;
}

void tcpSettings::returnCompressionState(int *cmp) {
    *cmp = compressionSpinBox_->value();
}

void tcpSettings::setFPS(int fps) {
    fpsLabel_->setText("FPS: " + QString::number(fps));
}

void tcpSettings::rebuildBtnClicked() {
    rebuildBtn_->setEnabled(false);
    run_ = false;
    emit rebuildServer();
}

tcpSettings::~tcpSettings() {
    delete qvbox_;
    delete qvboxTop_;
    delete qvboxLeft_;
    delete qvboxRight_;
    delete qhboxSettings_;
    delete fpsLabel_;
    delete infoGroup_;
    delete portLabel_;
    delete portSlider_;
    delete portSpinBox_;
    delete compressionLabel_;
    delete compressionSlider_;
    delete compressionSpinBox_;
    delete stopBtn_;
    delete stopBtn_;
    delete settingsGroup_;
}
