#include "mainwindow.h"

bool _boolfix = 0;
double _depsh = 0;
const double _value = 500000;

//double X[2000][2];

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent) {
    setupUi(this);
    //start in full screen format
//    QMainWindow::showFullScreen();
//    QMainWindow::menuBar()->setVisible(true);

    // Reading the key combination of turning the window to the full screen and back
    QShortcut* keyCtrlF = new QShortcut(this);
    keyCtrlF->setKey(Qt::CTRL | Qt::Key_F);
    connect(keyCtrlF, &QShortcut::activated, this, &MainWindow::fullScreenKey);

    // Package Type Changed
    radioButton_PackageNormal->setChecked(true); // default Connection type
    connect(radioButton_PackageNormal, SIGNAL(clicked()), this, SLOT(normalPackageClick()));
    connect(radioButton_PackageDirect, SIGNAL(clicked()), this, SLOT(directPackageClick()));
    connect(radioButton_PackageConfig, SIGNAL(clicked()), this, SLOT(configPackageClick()));

    // connect(pushButton_ReconnectROV, SIGNAL(clicked()), this, SLOT(reconnectcROVclick()));

    connect(checkBox_StabilizeRoll, SIGNAL(toggled(bool)), this, SLOT(stabilizeRollToggled(bool)));
    connect(checkBox_StabilizePitch, SIGNAL(toggled(bool)), this, SLOT(stabilizePitchToggled(bool)));
    connect(checkBox_StabilizeYaw, SIGNAL(toggled(bool)), this, SLOT(stabilizeYawToggled(bool)));
    connect(checkBox_StabilizeDepth, SIGNAL(toggled(bool)), this, SLOT(stabilizeDepthToggled(bool)));

    // Menu:
    // Vehicle
    // New vehicle
    // connect(action_create_vehicle, SIGNAL(triggered()), this, SLOT(createVehicle()));
//     // Choose vehicle and configuration
//     connect(menu_choose_configuration, SIGNAL(triggered(QAction * )), this, SLOT(chooseConfiguration(QAction * )));
//     connect(menu_choose_vehicle, SIGNAL(triggered(QAction * )), this, SLOT(chooseVehicle(QAction * )));
// //    // Settings
//    connect(action_config_com, SIGNAL(triggered()), &settingsWindow, SLOT(showPageConfigRS()));
    connect(action_SettingsThruster, SIGNAL(triggered()), &thrusterWindow, SLOT(show()));
    connect(action_SettingsControlSystem, SIGNAL(triggered()), &stabilizationWindow, SLOT(show()));

    //    // Surface control unit
    //    connect(action_config_controls, SIGNAL(triggered()), &controlWindow, SLOT(show()));
    //    connect(action_config_view, SIGNAL(triggered()), &settingsWindow, SLOT(showPageConfigView()));
    //    // Other settings
    //    connect(action_about_program, SIGNAL(triggered()), &settingsWindow, SLOT(showPageAboutProgram()));
    //    connect(action_other_settings, SIGNAL(triggered()), &settingsWindow, SLOT(showPageOtherSettings()));
    // connect(action_OtherFullScreen, &QAction::triggered, this, &MainWindow::fullScreenKey);




    serial_client = new SerialClient();
    serial_client->start();

    QTimer *update_timer = new QTimer(this);
    connect(update_timer, SIGNAL(timeout()), this, SLOT(updateUi()));
    update_timer->start(10);

    connect(serial_client, SIGNAL(dataUpdatedSerialClient()), this, SLOT(updateUi()));

    controller = new Joystick(10);



    //    const QString ConfigFile = "protocols.conf";
    //    const QString XI = "xi";
    //    const QString KI = "ki";
    //    //передача K
    //    Qkx_coeffs* kProtocol = new Qkx_coeffs(ConfigFile, KI);
    //    //передача X
    //    x_protocol* xProtocol = new x_protocol(ConfigFile, XI, X);

    connect(this, SIGNAL(updateCompass(double)), compassFrame, SLOT(setYaw(double)));
    connect(pushButton_ResetIMU, SIGNAL(pressed()), this, SLOT(resetImu()));
    connect(pushButton_ResetIMU, SIGNAL(released()), this, SLOT(clearResetImu()));

    //load image
    // vehiclePic->setScene(new QGraphicsScene(vehiclePic));
    // vehiclePic->setStyleSheet("background: transparent");
    // vehiclePic->setRenderHint(QPainter::Antialiasing);
    // vehiclePic->scene()->addPixmap(QPixmap(":/images/Cousteau_2A.png"));
    QPixmap pic(":/images/Cousteau3.png");
    label_6->setPixmap(pic.scaled(450, 300));
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

    // Update user interface
    progressBar_Depth->setValue(static_cast<int>(sensors.depth));
    progressBar_Pitch->setValue(static_cast<int>(sensors.pitch));

    label_BarDepth->setText(QString::number(sensors.depth, 'f', 2));
    label_BarPitch->setText(QString::number(sensors.pitch, 'f', 2));

    label_TelemetryRoll->setText(QString::number(sensors.roll, 'f', 2));
    label_TelemetryPitch->setText(QString::number(sensors.pitch, 'f', 2));
    label_TelemetryYaw->setText(QString::number(sensors.yaw, 'f', 2));
    //label_TelemetryDepth->setText(QString::number(sensors.depth, 'f', 2));
    label_TelemetryDepth->setText(QString::number(_depsh, 'f', 2));

    if(_boolfix){
        //ограниечение по возможным значениям
        if(_depsh <= 3.7 && _depsh >=0 ){
            _depsh += (double)uv_interface.getControlData().depth/_value;
        }
        else if(_depsh > 3){
            if(uv_interface.getControlData().depth < 0) _depsh += (double)uv_interface.getControlData().depth/_value;
        }
        else {
            if(uv_interface.getControlData().depth > 0) _depsh += (double)uv_interface.getControlData().depth/_value;
        }

        _depsh += (double)QRandomGenerator::global()->bounded(-100, 100)/30000.0;
    }
    else { //проверка на движение аппарата вперёд
        if (uv_interface.getControlData().depth) _boolfix = true;
    }

    // Update drawing of a compass
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

// void MainWindow::reconnectcROVclick() {
//     emit reconnectROV();
// }

//void MainWindow::enableControllerChanged(Control::e_controllerType controllerType, bool enabel) {
//    controller.setEnabel(controllerType, enabel);
//}

void MainWindow::normalPackageClick() {
        radioButton_PackageDirect->setChecked(false);
        radioButton_PackageConfig->setChecked(false);
    uv_interface.setPackegeMode(PACKAGE_NORMAL);

}


void MainWindow::configPackageClick() {
        radioButton_PackageNormal->setChecked(false);
        radioButton_PackageDirect->setChecked(false);
    uv_interface.setPackegeMode(PACKAGE_CONFIG);
}

void MainWindow::directPackageClick() {
        radioButton_PackageNormal->setChecked(false);
        radioButton_PackageConfig->setChecked(false);
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
