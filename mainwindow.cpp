#include "mainwindow.h"

//double X[2000][2];

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent) {
    setupUi(this);
    //start in full screen format
//    QMainWindow::showFullScreen();
//    QMainWindow::menuBar()->setVisible(true);

    // Full screen and back
    QShortcut* keyCtrlF = new QShortcut(this);
    keyCtrlF->setKey(Qt::CTRL | Qt::Key_F);
    connect(keyCtrlF, &QShortcut::activated, this, &MainWindow::fullScreenKey);

    // Menu:
    connect(action_SettingsThruster, SIGNAL(triggered()), &thrusterWindow, SLOT(show()));
    connect(action_SettingsControlSystem, SIGNAL(triggered()), &stabilizationWindow, SLOT(show()));

    // Package Type Changed
    connect(radioButton_PackageNormal, SIGNAL(clicked()), this, SLOT(normalPackageClick()));
    connect(radioButton_PackageDirect, SIGNAL(clicked()), this, SLOT(directPackageClick()));
    connect(radioButton_PackageConfig, SIGNAL(clicked()), this, SLOT(configPackageClick()));
    radioButton_PackageNormal->setChecked(true); // default Connection type

    connect(checkBox_StabilizeRoll, SIGNAL(toggled(bool)), this, SLOT(stabilizeRollToggled(bool)));
    connect(checkBox_StabilizePitch, SIGNAL(toggled(bool)), this, SLOT(stabilizePitchToggled(bool)));
    connect(checkBox_StabilizeYaw, SIGNAL(toggled(bool)), this, SLOT(stabilizeYawToggled(bool)));
    connect(checkBox_StabilizeDepth, SIGNAL(toggled(bool)), this, SLOT(stabilizeDepthToggled(bool)));

    connect(radioButton_Serial, SIGNAL(clicked()), this, SLOT(connectSerialClick()));
    connect(radioButton_UDP, SIGNAL(clicked()), this, SLOT(connectUDPClick()));
    connect(pushButton_ReconnectROV, SIGNAL(clicked()), this, SLOT(reconnectcROVclick()));

    uv_interface.setConnectionMode(e_Connection::CONNECTION_SERIAL);
    serial_client = new SerialClient();
    connect(serial_client, SIGNAL(dataUpdatedSerialClient()), this, SLOT(updateUi()));
    serial_client->start();
    // emit reconnectcROVclick();

    // connect(serial_client, SIGNAL(dataUpdatedSerialClient()), this, SLOT(updateUi()));
    // connect(serial_client, SIGNAL(dataUpdatedSerialClient()), this, SLOT(updateUi()));

    // joystick = new Joystick(10);
    gamepad = new Gamepad(10);


    connect(pushButton_ResetIMU, SIGNAL(pressed()), this, SLOT(resetImu()));
    connect(pushButton_ResetIMU, SIGNAL(released()), this, SLOT(clearResetImu()));

    QPixmap pic(":/images/Cousteau3.png");
    label_6->setPixmap(pic.scaled(450, 300));

    // QTimer *update_timer = new QTimer(this);
    // connect(update_timer, SIGNAL(timeout()), this, SLOT(updateUi()));
    // update_timer->start(10);

    connect(this, SIGNAL(updateCompass(double)), compassFrame, SLOT(setYaw(double)));
    updateUi();

    //    const QString ConfigFile = "protocols.conf";
    //    const QString XI = "xi";
    //    const QString KI = "ki";
    //    //передача K
    //    Qkx_coeffs* kProtocol = new Qkx_coeffs(ConfigFile, KI);
    //    //передача X
    //    x_protocol* xProtocol = new x_protocol(ConfigFile, XI, X);
}

// void MainWindow::reconnectcROVclick() {
//     if (udp_client != nullptr) {
//         qDebug() << "udp_client != nullptr";
//         udp_client->disconnect();

//         delete udp_client;
//         udp_client = nullptr;
//     }
//     if (serial_client != nullptr) {
//         qDebug() << "serial_client != nullptr";
//         serial_client->disconnect();
//         qDebug() << "serial_client->disconnect";

//         delete serial_client;
//         serial_client = nullptr;
//     }
//     e_Connection connectionMode = uv_interface.getConnectionMode();

//     if (connectionMode == CONNECTION_UDP) {
//         qDebug() << "connectionMode == CONNECTION_UDP";
//         udp_client = new UdpClient();
//         connect(udp_client, SIGNAL(dataUpdatedUdpClient()), this, SLOT(updateUi()));
//         udp_client->start();
//     }

//     if (connectionMode == CONNECTION_SERIAL) {
//         qDebug() << "connectionMode == CONNECTION_SERIAL";
//         serial_client = new SerialClient();
//         connect(serial_client, SIGNAL(dataUpdatedSerialClient()), this, SLOT(updateUi()));
//         serial_client->start();
//     }
// }

// void MainWindow::connectSerialClick() {
//     uv_interface.setConnectionMode(e_Connection::CONNECTION_SERIAL);
//     emit reconnectcROVclick();
// }

// void MainWindow::connectUDPClick() {
//     uv_interface.setConnectionMode(e_Connection::CONNECTION_UDP);
//     emit reconnectcROVclick();
// }


void MainWindow::fullScreenKey() {
    if (QMainWindow::windowState() == Qt::WindowFullScreen) {
        QMainWindow::showNormal();
        QMainWindow::menuBar()->setVisible(true);
    } else {
        QMainWindow::showFullScreen();
        QMainWindow::menuBar()->setVisible(true);
    }
}

void MainWindow::updateUi() {
    ImuData sensors = uv_interface.getImuData();

    progressBar_Depth->setValue(static_cast<int>(sensors.depth));
    progressBar_Pitch->setValue(static_cast<int>(sensors.pitch));

    label_BarDepth->setText(QString::number(sensors.depth, 'f', 2));
    label_BarPitch->setText(QString::number(sensors.pitch, 'f', 2));

    label_TelemetryRoll->setText(QString::number(sensors.roll, 'f', 2));
    label_TelemetryPitch->setText(QString::number(sensors.pitch, 'f', 2));
    label_TelemetryYaw->setText(QString::number(sensors.yaw, 'f', 2));
    label_TelemetryDepth->setText(QString::number(sensors.depth, 'f', 2));

    emit updateCompass(sensors.yaw);

    ControlData control = uv_interface.getControlData();
    label_ImpactMarch->setText(QString::number(control.march, 'f', 2));
    label_ImpactLag->setText(QString::number(control.lag, 'f', 2));
    label_ImpactDepth->setText(QString::number(control.depth, 'f', 2));
    label_ImpactYaw->setText(QString::number(control.yaw, 'f', 2));
    label_ImpactRoll->setText(QString::number(control.roll, 'f', 2));
    label_ImpactPitch->setText(QString::number(control.pitch, 'f', 2));

    label_DevicesGrabber->setText(QString::number(uv_interface.getDeviceVelocity(DEVICE_GRAB)));
    label_DevicesGrabberRotation->setText(QString::number(uv_interface.getDeviceVelocity(DEVICE_GRAB_ROTATE)));
    label_DevicesTilt->setText(QString::number(uv_interface.getDeviceVelocity(DEVICE_TILT)));
    label_DevicesDev->setText(QString::number(uv_interface.getDeviceVelocity(DEVICE_DEV1)));
}

void MainWindow::resetImu() {
    uv_interface.setResetImu(true);
}

void MainWindow::clearResetImu() {
    uv_interface.setResetImu(false);
}

void MainWindow::normalPackageClick() {
    uv_interface.setPackegeMode(PACKAGE_NORMAL);
}

void MainWindow::configPackageClick() {
    uv_interface.setPackegeMode(PACKAGE_CONFIG);
}

void MainWindow::directPackageClick() {
    uv_interface.setPackegeMode(PACKAGE_DIRECT);
}

void MainWindow::stabilizeRollToggled(bool state) {
    uv_interface.setStabRoll(state);
}

void MainWindow::stabilizePitchToggled(bool state) {
    uv_interface.setStabPitch(state);
}

void MainWindow::stabilizeYawToggled(bool state) {
    uv_interface.setStabYaw(state);
}

void MainWindow::stabilizeDepthToggled(bool state) {
    uv_interface.setStabDepth(state);
}
