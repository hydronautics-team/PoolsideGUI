#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui_mainwindow.h"

#include "UV/iuserinterfacedata.h"
#include "CommunicationSettings/SerialClient.h"
#include "CommunicationSettings/UdpClient.h"
#include "ControlSettings/Joystick.h"
#include "ControlSettings/Keyboard.h"

class MainWindow: public QMainWindow, private Ui::MainWindow {
    Q_OBJECT

signals:
public:
public slots:
private slots:

};

#endif // MAINWINDOW_H
