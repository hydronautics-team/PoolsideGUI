#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi(this);
    //start in full screen format
//    QMainWindow::showFullScreen();
//    QMainWindow::menuBar()->setVisible(true);

    // update vehicle and all parameters
    connect(&wizard, SIGNAL(updateMainWindow()), this, SIGNAL(updateVehicle()));
    connect(this, SIGNAL(updateVehicle()), this, SLOT(updateVehiclesMenu()));

    // Reading the key combination of turning the window to the full screen and back
    QShortcut *keyCtrlF = new QShortcut(this);
    keyCtrlF->setKey(Qt::CTRL + Qt::Key_F);
    connect(keyCtrlF, &QShortcut::activated, this, &MainWindow::fullScreenKey);

    // Controller Changed
    controller.setDefoultEnabeling();
    connect(&controlWindow, SIGNAL(controllersEnabelChanged(Control::e_controllerType, bool)),
            this, SLOT(enableControllerChanged(Control::e_controllerType, bool)));

    // Connection Type Changed
    radioButton_ConnectionNormal->setChecked(true); // default Connection type
    connect(radioButton_ConnectionNormal, SIGNAL(clicked()), this, SLOT(normalConnectionClick()));
    connect(radioButton_ConnectionDirect, SIGNAL(clicked()), this, SLOT(directConnectionClick()));
    connect(radioButton_ConnectionConfig, SIGNAL(clicked()), this, SLOT(configConnectionClick()));

    connect(pushButtonReconnectROV, SIGNAL(clicked()), this, SLOT(reconnectcROVclick()));

    // Menu:
    // Vehicle
    // New vehicle
    connect(action_create_vehicle, SIGNAL(triggered()), this, SLOT(createVehicle()));
    // Choose vehicle and configuration
    connect(menu_choose_configuration, SIGNAL(triggered(QAction * )), this, SLOT(chooseConfiguration(QAction * )));
    connect(menu_choose_vehicle, SIGNAL(triggered(QAction * )), this, SLOT(chooseVehicle(QAction * )));
//    // Settings
//    connect(action_config_com, SIGNAL(triggered()), &settingsWindow, SLOT(showPageConfigRS()));
    connect(action_config_thrusters, SIGNAL(triggered()), &thrusterWindow, SLOT(show()));
//    connect(action_config_coef, SIGNAL(triggered()), &settingsWindow, SLOT(showPageConfigCoef()));
//    // Surface control unit
    connect(action_config_controls, SIGNAL(triggered()), &controlWindow, SLOT(show()));
//    connect(action_config_view, SIGNAL(triggered()), &settingsWindow, SLOT(showPageConfigView()));
//    // Other settings
//    connect(action_about_program, SIGNAL(triggered()), &settingsWindow, SLOT(showPageAboutProgram()));
//    connect(action_other_settings, SIGNAL(triggered()), &settingsWindow, SLOT(showPageOtherSettings()));
    connect(action_full_screen, &QAction::triggered, this, &MainWindow::fullScreenKey);


//    stabilizationWindow.show();


    settingsFile = QApplication::applicationDirPath() + "/settings.ini"; // path to settings file
    checkFile(settingsFile); // check file existance
    settings = new QSettings(settingsFile, QSettings::IniFormat);

    currentVehicle = settings->value("currentVehicle").toString();
    currentConfiguration = settings->value("currentConfiguration").toString();
    emit updateVehicle();

    reconnectROV();

//    udp_client = new UdpClient();
//    udp_client->start();

    connect(this, SIGNAL(updateCompass(double)), compassFrame, SLOT(setYaw(double)));
    connect(pushButtonResetIMU, SIGNAL(pressed()), this, SLOT(resetImu()));
    connect(pushButtonResetIMU, SIGNAL(released()), this, SLOT(clearResetImu()));

    //load image
    vehiclePic->setScene(new QGraphicsScene(vehiclePic));
    vehiclePic->setStyleSheet("background: transparent");
    vehiclePic->setRenderHint(QPainter::Antialiasing);
    vehiclePic->scene()->addPixmap(QPixmap(":/images/Cousteau_2A.png"))->setTransform(QTransform::fromScale(0.2, 0.2));

    initializeDataUi();
    updateUi();
}


/*!
 * @brief Reconnect rov
 */
void MainWindow::reconnectROV() // TODO: присутствует утечка пямяти при reconnectROV из-заnew SerialClient
{
    if (radioButton_ConnectionNormal->isChecked() == true) {
        serial_client = new SerialClient(MESSAGE_NORMAL);
    }
    if (radioButton_ConnectionDirect->isChecked() == true) {
        serial_client = new SerialClient(MESSAGE_DIRECT);
    }
    if (radioButton_ConnectionConfig->isChecked() == true) {
        serial_client = new SerialClient(MESSAGE_CONFIG);
    }
    serial_client->start();

    connect(serial_client, SIGNAL(dataUpdated()), this, SLOT(updateUi()));
//    connect(settingsWindow.pageConfigThruster, SIGNAL(ThrusterChanged(unsigned int)), serial_client,
//            SLOT(changeSelectedThruster(unsigned int)));
}

void MainWindow::createVehicle() {
    wizard.startStateMachine();
    wizard.show();
}

void MainWindow::chooseVehicle(QAction *action) {
    currentVehicle = action->text();
    settings->beginGroup("vehicle/" + currentVehicle + "/configuration");
    for (qsizetype i = 0; i < settings->childKeys().size(); i++) {
        if (settings->value(settings->childKeys().at(i)).toBool()) {
            currentConfiguration = settings->childKeys().at(i);
            break;
        }
    }
    settings->endGroup();

    settings->setValue("currentVehicle", currentVehicle);
    settings->setValue("currentConfiguration", currentConfiguration);
    emit updateVehicle();
}

void MainWindow::chooseConfiguration(QAction *action) {
    currentConfiguration = action->text();
    settings->setValue("currentConfiguration", currentConfiguration);
    updateVehicleConfigurationMenu();
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

void MainWindow::updateVehiclesMenu() {
    if (!currentVehicle.isEmpty()) {
        if (!menu_choose_vehicle->isEmpty())
            menu_choose_vehicle->clear();
        settings->beginGroup("vehicle");
        for (auto &key: settings->childGroups()) {
            auto *vehicle = new QAction(key);
            if (key == currentVehicle) {
                QFont f = vehicle->font();
                f.setBold(true);
                vehicle->setFont(f);
                menu_choose_vehicle->addAction(vehicle);
            } else
                menu_choose_vehicle->addAction(vehicle);
        }
        settings->endGroup();
    }
    settings->sync();
//    qDebug() << currentVehicle;
    updateVehicleConfigurationMenu();
}

void MainWindow::updateVehicleConfigurationMenu() {
    menu_choose_configuration->clear();
    settings->beginGroup("vehicle/" + currentVehicle + "/configuration");
    for (qsizetype i = 0; i < settings->childKeys().size(); i++) {
        if (settings->value(settings->childKeys().at(i)).toBool()) {
            QAction *configuration = new QAction(settings->childKeys().at(i));
            if (settings->childKeys().at(i) == currentConfiguration) {
                QFont f = configuration->font();
                f.setBold(true);
                configuration->setFont(f);
                menu_choose_configuration->addAction(configuration);
            } else
                menu_choose_configuration->addAction(configuration);
        }
    }
    settings->endGroup();
//    qDebug() << currentConfiguration;
}

void MainWindow::checkFile(QString filename) {
    QFile file(filename);
    if (QFileInfo::exists(filename)) {
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        file.close();
    } else {
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        file.close();
    }
}

void MainWindow::updateVehicleUi() {
    currentVehicle = settings->value("currentVehicle").toString();
    thrustersCount = settings->value("vehicle/" + currentVehicle + "/thrusters/count").toInt();
    //update bars
            foreach (QProgressBar *bar, thrusterBarGroup) {
            bar->hide();
        }
    for (int i = 0; i < thrustersCount; i++) {
        thrusterBarGroup[i]->show();
        thrusterBarGroup[i]->setFormat(
                settings->value("vehicle/" + currentVehicle + "/thrusters/" + QString::number(i) + "/name").toString());
    }
    initializeDataUi();
    updateUi();
}

void MainWindow::initializeDataUi() {
            foreach (QProgressBar *bar, thrusterBarGroup) {
            bar->setValue(0);
        }
    pitchBar->setValue(0);
    depthBar->setValue(0);
    depthLabel->setText("0");   // label under bar
    pitchLabel->setText("0");   // label under bar
    sensorsDepthLabel->setText("0");
    sensorsPitchLabel->setText("0");
    sensorsYawLabel->setText("0");
    sensorsRollLabel->setText("0");
    emit updateCompass(0);
}

void MainWindow::updateUi() {
    // Get data from UVState object
    ImuData sensors = uv_interface.getImuData();

    // Update user interface
    depthBar->setValue(static_cast<int>(sensors.depth * depthLin + depthOffset));   // bar
    pitchBar->setValue(static_cast<int>(sensors.pitch));   // bar

    depthLabel->setText(QString::number(sensors.depth * depthLin + depthOffset, 'f', 2));   // label under bar
    pitchLabel->setText(QString::number(sensors.pitch, 'f', 2));   // label under bar

    sensorsDepthLabel->setText(QString::number(sensors.depth * depthLin + depthOffset, 'f', 2));
    sensorsPitchLabel->setText(QString::number(sensors.pitch, 'f', 2));

    sensorsYawLabel->setText(QString::number(sensors.yaw, 'f', 2));
    sensorsRollLabel->setText(QString::number(sensors.roll, 'f', 2));

    // Update drawing of a compass
    emit updateCompass(sensors.yaw);

    ControlData control = uv_interface.getControlData();

    label_march->setText(QString::number(control.march, 'f', 2));
    label_lag->setText(QString::number(control.lag, 'f', 2));
    label_depth->setText(QString::number(control.depth, 'f', 2));
    label_yaw->setText(QString::number(control.yaw, 'f', 2));
    label_roll->setText(QString::number(control.roll, 'f', 2));

    label_grabber->setText(QString::number(uv_interface.getDeviceVelocity(UV_Device::DEVICE_GRAB), 'f', 2));
    label_grabber_rotation->setText(
            QString::number(uv_interface.getDeviceVelocity(UV_Device::DEVICE_GRAB_ROTATE), 'f', 2));
    label_tilt->setText(QString::number(uv_interface.getDeviceVelocity(UV_Device::DEVICE_TILT), 'f', 2));
//    qDebug() << "updateData";
}


void MainWindow::resetImu() {
    IUserInterfaceData interface;
    interface.setResetImuValue(true);
}

void MainWindow::clearResetImu() {
    IUserInterfaceData interface;
    interface.setResetImuValue(false);
}

void MainWindow::reconnectcROVclick() {
    emit reconnectROV();
}

void MainWindow::enableControllerChanged(Control::e_controllerType controllerType, bool enabel) {
    controller.setEnabel(controllerType, enabel);
}

void MainWindow::normalConnectionClick() {
    emit(ConnectionTypeChanged(MESSAGE_NORMAL));

}

void MainWindow::directConnectionClick() {
    emit(ConnectionTypeChanged(MESSAGE_DIRECT));
}

void MainWindow::configConnectionClick() {
    emit(ConnectionTypeChanged(MESSAGE_CONFIG));
}

void MainWindow::ConnectionTypeChanged(e_MessageTypes connectionType) {
    switch (connectionType) {
        case MESSAGE_NORMAL:
            radioButton_ConnectionDirect->setChecked(false);
            radioButton_ConnectionConfig->setChecked(false);
            break;

        case MESSAGE_CONFIG:
            radioButton_ConnectionNormal->setChecked(false);
            radioButton_ConnectionConfig->setChecked(false);
            break;

        case MESSAGE_DIRECT:
            radioButton_ConnectionNormal->setChecked(false);
            radioButton_ConnectionDirect->setChecked(false);
            break;
    }
    emit serial_client->changeSelectedConnectionType(connectionType);
}
