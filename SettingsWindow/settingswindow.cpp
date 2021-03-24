#include "settingswindow.h"
#include <QDebug>
#include "SFML/Window.hpp"

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

    table->setItem(0, 0, new QTableWidgetItem("isConnected"));
    table->setItem(1, 0, new QTableWidgetItem("Name"));
    table->setItem(2, 0, new QTableWidgetItem("vendorID"));
    table->setItem(3, 0, new QTableWidgetItem("productID"));
    table->setItem(4, 0, new QTableWidgetItem("ButtonCount"));
    table->setItem(5, 0, new QTableWidgetItem("Axises"));
    table->setItem(6, 0, new QTableWidgetItem("Buttons Pressed"));
    table->setItem(7, 0, new QTableWidgetItem("AxisX Position"));
    table->setItem(8, 0, new QTableWidgetItem("AxisY Position"));
    table->setItem(9, 0, new QTableWidgetItem("AxisZ Position"));
    table->setItem(10, 0, new QTableWidgetItem("AxisR Position"));
    table->setItem(11, 0, new QTableWidgetItem("AxisU Position"));
    table->setItem(12, 0, new QTableWidgetItem("AxisV Position"));

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
    unsigned int joystick_id = 0;
    QString buttons_list, axis_list;

//    sf::Joystick::update();

//    for (unsigned int i = 0; i<=sf::Joystick::ButtonCount; i++) {
//        if (sf::Joystick::isButtonPressed(joystick_id, i)) {
//            buttons_list += QString::number(i) + ", ";
//        }
//    }

//    for (unsigned int i = 0; i<=sf::Joystick::AxisCount; i++) {
//        if (sf::Joystick::hasAxis(joystick_id, static_cast<sf::Joystick::Axis>(i))) {
//            axis_list += QString::number(i) + ", ";
//        }
//    }

//    sf::Joystick::Identification identification = sf::Joystick::getIdentification(joystick_id);

//    //std::string name = identification.name;
//    //QString qname = QString::fromStdString(name);

//    table->setItem(0, 0, new QTableWidgetItem(QString::number(sf::Joystick::isConnected(joystick_id))));
//    //table->setItem(1, 0, new QTableWidgetItem(qname));
//    table->setItem(2, 0, new QTableWidgetItem(QString::number(identification.vendorId)));
//    table->setItem(3, 0, new QTableWidgetItem(QString::number(identification.productId)));
//    table->setItem(4, 0, new QTableWidgetItem(QString::number(sf::Joystick::getButtonCount(joystick_id))));
//    table->setItem(5, 0, new QTableWidgetItem(axis_list));
//    table->setItem(6, 0, new QTableWidgetItem(buttons_list));
//    table->setItem(7, 0, new QTableWidgetItem(QString::number(sf::Joystick::getAxisPosition(joystick_id, sf::Joystick::X))));
//    table->setItem(8, 0, new QTableWidgetItem(QString::number(sf::Joystick::getAxisPosition(joystick_id, sf::Joystick::Y))));
//    table->setItem(9, 0, new QTableWidgetItem(QString::number(sf::Joystick::getAxisPosition(joystick_id, sf::Joystick::Z))));
//    table->setItem(10, 0, new QTableWidgetItem(QString::number(sf::Joystick::getAxisPosition(joystick_id, sf::Joystick::R))));
//    table->setItem(11, 0, new QTableWidgetItem(QString::number(sf::Joystick::getAxisPosition(joystick_id, sf::Joystick::U))));
//    table->setItem(12, 0, new QTableWidgetItem(QString::number(sf::Joystick::getAxisPosition(joystick_id, sf::Joystick::V))));
}
