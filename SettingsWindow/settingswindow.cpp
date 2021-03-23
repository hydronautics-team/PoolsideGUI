#include "settingswindow.h"
#include <QDebug>
#include <QDesktopWidget>

SettingsWindow::SettingsWindow(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    qDebug () << " - SettingsWindow constructor";
    connect(this, SIGNAL(updateVehicle()),
            pageConfigThruster, SLOT(updateVehicle()));

    table = new QTableWidget(30, 2, this->groupBox_10);

    table->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

    table->setStyleSheet("QTableView {selection-background-color: white;}");

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    table->resize(this->groupBox_10->size());

    QStringList horizontalLabels;
    horizontalLabels.append("Info Type");
    horizontalLabels.append("Value");
    table->setHorizontalHeaderLabels(horizontalLabels);

    table->setItem(0, 0, new QTableWidgetItem("Name"));
    table->setItem(1, 0, new QTableWidgetItem("ID"));
    table->setItem(2, 0, new QTableWidgetItem("axisLeftX"));
    table->setItem(3, 0, new QTableWidgetItem("axisLeftY"));
    table->setItem(4, 0, new QTableWidgetItem("axisRightX"));
    table->setItem(5, 0, new QTableWidgetItem("axisRightY"));
    table->setItem(6, 0, new QTableWidgetItem("buttonL1"));
    table->setItem(7, 0, new QTableWidgetItem("buttonL2"));
    table->setItem(8, 0, new QTableWidgetItem("buttonL3"));
    table->setItem(9, 0, new QTableWidgetItem("buttonR1"));
    table->setItem(10, 0, new QTableWidgetItem("buttonR2"));
    table->setItem(11, 0, new QTableWidgetItem("buttonR3"));
    table->setItem(12, 0, new QTableWidgetItem("buttonA"));
    table->setItem(13, 0, new QTableWidgetItem("buttonB"));
    table->setItem(14, 0, new QTableWidgetItem("buttonCenter"));
    table->setItem(15, 0, new QTableWidgetItem("buttonDown"));
    table->setItem(16, 0, new QTableWidgetItem("buttonGuide"));
    table->setItem(17, 0, new QTableWidgetItem("buttonLeft"));
    table->setItem(18, 0, new QTableWidgetItem("buttonRight"));
    table->setItem(19, 0, new QTableWidgetItem("buttonSelect"));
    table->setItem(20, 0, new QTableWidgetItem("buttonStart"));
    table->setItem(21, 0, new QTableWidgetItem("buttonUp"));
    table->setItem(22, 0, new QTableWidgetItem("buttonX"));
    table->setItem(23, 0, new QTableWidgetItem("buttonY"));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTickEvent()));
    timer->start(100);
}

void SettingsWindow::showPageConfigThruster()
{
    this->show();
    stackedWidget->setCurrentWidget(pageConfigThruster);
    this->setWindowTitle("Thruster settings");
}

void SettingsWindow::showPageConfigRS()
{
    this->show();
    stackedWidget->setCurrentWidget(pageConfigRS);
    this->setWindowTitle("Communication settings");
}

void SettingsWindow::showPageConfigSSH()
{
    this->show();
    stackedWidget->setCurrentWidget(pageConfigSSH);
    this->setWindowTitle("Communication settings");
}

void SettingsWindow::showPageConfigCoef()
{
    this->show();
    stackedWidget->setCurrentWidget(pageVehicleSettings);
    this->setWindowTitle("Vehicle settings");
}

void SettingsWindow::showPageConfigControls()
{
    this->show();
    stackedWidget->setCurrentWidget(pageConfigControls);

    table->show();

    this->setWindowTitle("Controls settings");
}

void SettingsWindow::showPageConfigView()
{
    this->show();
    stackedWidget->setCurrentWidget(pageConfigView);
    this->setWindowTitle("View settings");
}

void SettingsWindow::showPageAboutProgram()
{
    this->show();
    stackedWidget->setCurrentWidget(pageAboutProgram);
    this->setWindowTitle("About program");
}

void SettingsWindow::showPageOtherSettings()
{
    this->show();
    stackedWidget->setCurrentWidget(pageOtherSettings);
    this->setWindowTitle("Other settings");
}

void SettingsWindow::timerTickEvent()
{
    auto gamepads = QGamepadManager::instance()->connectedGamepads();
    qDebug() << "Gamepads:" << gamepads.size();
    gamepad.setDeviceId(gamepads[0]);

    table->setItem(0, 1, new QTableWidgetItem(gamepad.name()));
    table->setItem(1, 1, new QTableWidgetItem(QString::number(gamepad.deviceId())));
    table->setItem(2, 1, new QTableWidgetItem(QString::number(gamepad.axisLeftX())));
    table->setItem(3, 1, new QTableWidgetItem(QString::number(gamepad.axisLeftY())));
    table->setItem(4, 1, new QTableWidgetItem(QString::number(gamepad.axisRightX())));
    table->setItem(5, 1, new QTableWidgetItem(QString::number(gamepad.axisRightY())));
    table->setItem(6, 1, new QTableWidgetItem(QString::number(gamepad.buttonL1())));
    table->setItem(7, 1, new QTableWidgetItem(QString::number(gamepad.buttonL2())));
    table->setItem(8, 1, new QTableWidgetItem(QString::number(gamepad.buttonL3())));
    table->setItem(9, 1, new QTableWidgetItem(QString::number(gamepad.buttonR1())));
    table->setItem(10, 1, new QTableWidgetItem(QString::number(gamepad.buttonR2())));
    table->setItem(11, 1, new QTableWidgetItem(QString::number(gamepad.buttonR3())));
    table->setItem(12, 1, new QTableWidgetItem(QString::number(gamepad.buttonA())));
    table->setItem(13, 1, new QTableWidgetItem(QString::number(gamepad.buttonB())));
    table->setItem(14, 1, new QTableWidgetItem(QString::number(gamepad.buttonCenter())));
    table->setItem(15, 1, new QTableWidgetItem(QString::number(gamepad.buttonDown())));
    table->setItem(16, 1, new QTableWidgetItem(QString::number(gamepad.buttonGuide())));
    table->setItem(17, 1, new QTableWidgetItem(QString::number(gamepad.buttonLeft())));
    table->setItem(18, 1, new QTableWidgetItem(QString::number(gamepad.buttonRight())));
    table->setItem(19, 1, new QTableWidgetItem(QString::number(gamepad.buttonSelect())));
    table->setItem(20, 1, new QTableWidgetItem(QString::number(gamepad.buttonStart())));
    table->setItem(21, 1, new QTableWidgetItem(QString::number(gamepad.buttonUp())));
    table->setItem(22, 1, new QTableWidgetItem(QString::number(gamepad.buttonX())));
    table->setItem(23, 1, new QTableWidgetItem(QString::number(gamepad.buttonY())));
}
