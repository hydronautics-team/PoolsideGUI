#include "mainwindow.h"

//double X[2000][2];

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent) {
    setupUi(this);

    // Full screen and back
    QShortcut* keyCtrlF = new QShortcut(this);
    keyCtrlF->setKey(Qt::CTRL | Qt::Key_F);
    connect(keyCtrlF, &QShortcut::activated, this, &MainWindow::fullScreenKey);

    // Menu:
    connect(action_SettingsThruster, SIGNAL(triggered()), &thrusterWindow, SLOT(show()));
    connect(action_SettingsControlSystem, SIGNAL(triggered()), &stabilizationWindow, SLOT(show()));

    // connect(radioButton_Serial, SIGNAL(clicked()), this, SLOT(connectSerialClick()));
    // connect(radioButton_UDP, SIGNAL(clicked()), this, SLOT(connectUDPClick()));
    // connect(pushButton_ReconnectROV, SIGNAL(clicked()), this, SLOT(reconnectcROVclick()));

    // uv_interface.setConnectionMode(e_Connection::CONNECTION_SERIAL);
    // serial_client = new SerialClient();
    // connect(serial_client, SIGNAL(dataUpdatedSerialClient()), this, SLOT(updateUi()));

    uv_interface.setConnectionMode(e_Connection::CONNECTION_UDP);
    udp_client = new UdpClient();
    connect(udp_client, SIGNAL(dataUpdated()), this, SLOT(updateUi()));

    QTimer* update_timer = new QTimer(this);
    connect(update_timer, SIGNAL(timeout()), this, SLOT(updateUi()));
    update_timer->start(10);

    // joystick = new Joystick(10);
    gamepad = new Gamepad(10);

    connect(this, SIGNAL(updateCompass(double)), compassFrame, SLOT(setYaw(double)));
    connect(pushButton_ResetIMU, SIGNAL(pressed()), this, SLOT(resetImu()));
    connect(pushButton_ResetIMU, SIGNAL(released()), this, SLOT(clearResetImu()));

    //    const QString ConfigFile = "protocols.conf";
    //    const QString XI = "xi";
    //    const QString KI = "ki";
    //    //передача K
    //    Qkx_coeffs* kProtocol = new Qkx_coeffs(ConfigFile, KI);
    //    //передача X
    //    x_protocol* xProtocol = new x_protocol(ConfigFile, XI, X);

    updateUi();
}

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
    // Get data from UVState object
    ImuData sensors = uv_interface.getImuData();
    float depth = uv_interface.getIntegratedDepth() + ((static_cast<float>(std::rand()%35) - 17.5)/200.0);

    sensors.yaw = sensors.yaw/2;
    // Update user interface
    prev_yaw = label_TelemetryYaw->text().toDouble();


    if (prev_yaw > 150 and prev_yaw < 180 and sensors.yaw < 30) yaw_plus180 = true;
    if (prev_yaw > 330 and sensors.yaw < 30) yaw_plus180 = false;

    if (prev_yaw < 30 and sensors.yaw > 150) yaw_plus180 = true;
    if (prev_yaw > 180 and prev_yaw < 210 and sensors.yaw > 150) yaw_plus180 = false;

    progressBar_Depth->setValue(static_cast<int>(depth * 100));
    progressBar_Pitch->setValue(static_cast<int>(sensors.pitch));

    label_BarDepth->setText(QString::number(depth, 'f', 2));
    label_BarPitch->setText(QString::number(sensors.pitch, 'f', 2));

    label_TelemetryRoll->setText(QString::number(sensors.roll, 'f', 2));
    label_TelemetryPitch->setText(QString::number(sensors.pitch, 'f', 2));
    label_TelemetryYaw->setText(QString::number(sensors.yaw + (180 * yaw_plus180), 'f', 2));
    label_TelemetryDepth->setText(QString::number(depth, 'f', 2));

    // Update drawing of a compass
    emit updateCompass(sensors.yaw + (180 * yaw_plus180));

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

