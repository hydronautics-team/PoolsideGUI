#include "thrustersettings.h"
#include <QDebug>
#include <QFileInfo>

ThrusterSettings::ThrusterSettings(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    qDebug () << " - ThrusterSettings constructor";

    settingsFile = QApplication::applicationDirPath() + "/settings.ini"; // path to settings file
    settings = new QSettings(settingsFile, QSettings::IniFormat);
    currentVehicle = settings->value("currentVehicle").toString();
    currentThruster = 0;
    thrustersCount = settings->value("vehicle/" + currentVehicle + "/thrusters/count").toInt();

    thrusterButtonGroup = new QButtonGroup();
    thrusterButtonGroup->addButton(thrusterBtn0, 0);
    thrusterButtonGroup->addButton(thrusterBtn1, 1);
    thrusterButtonGroup->addButton(thrusterBtn2, 2);
    thrusterButtonGroup->addButton(thrusterBtn3, 3);
    thrusterButtonGroup->addButton(thrusterBtn4, 4);
    thrusterButtonGroup->addButton(thrusterBtn5, 5);
    thrusterButtonGroup->addButton(thrusterBtn6, 6);
    thrusterButtonGroup->addButton(thrusterBtn7, 7);

    connect(thrusterButtonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(thrusterButtonClicked(int))); // thruster button clicked

    connect(idSpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(thrusterIdChanged(int))); // thruster id
    connect(checkBoxReverse, SIGNAL(stateChanged(int)),
            this, SLOT(thrusterReverseChanged(int))); //thruster reverse

    connect(verticalSliderVelocity, SIGNAL(valueChanged(int)),
            this, SLOT(thrusterVelocityChanged(int)));
    connect(verticalSliderForwardK, SIGNAL(valueChanged(int)),
            this, SLOT(thrusterKForwardChanged(int)));
    connect(verticalSliderBackwardK, SIGNAL(valueChanged(int)),
            this, SLOT(thrusterKBackwardChanged(int)));
    connect(verticalSliderForwardSaturation, SIGNAL(valueChanged(int)),
            this, SLOT(thrusterForwardSaturationChanged(int)));
    connect(verticalSliderBackwardSaturation, SIGNAL(valueChanged(int)),
            this, SLOT(thrusterBackwardSaturationChanged(int)));

    updateThrusterSettings();
}

void ThrusterSettings::updateVehicle()
{
    currentVehicle = settings->value("currentVehicle").toString();
    currentThruster = 0;
    //update buttons
    foreach (QAbstractButton *button, thrusterButtonGroup->buttons()) {
        button->hide();
    }
    for (int i = 0; i < thrustersCount; i++){
        thrusterButtonGroup->button(i)->show();
        thrusterButtonGroup->button(i)->setText(settings->value(
                                                    "vehicle/" +
                                                    currentVehicle +
                                                    "/thrusters/" +
                                                    QString::number(i) + "/name").toString());
    }
    updateThrusterSettings();
}

void ThrusterSettings::updateThrusterSettings()
{
    idSpinBox->setValue(
                settings->value("vehicle/" +
                                currentVehicle +
                                "/thrusters/" +
                                QString::number(currentThruster) +
                                "/id").toInt());
    checkBoxReverse->setChecked(
                settings->value("vehicle/" +
                                currentVehicle +
                                "/thrusters/" +
                                QString::number(currentThruster) +
                                "/reverse").toBool());
    verticalSliderVelocity->setValue(
                settings->value("vehicle/" +
                                currentVehicle +
                                "/thrusters/" +
                                QString::number(currentThruster) +
                                "/velocity").toInt());
    verticalSliderForwardK->setValue(
                settings->value("vehicle/" +
                                currentVehicle +
                                "/thrusters/" +
                                QString::number(currentThruster) +
                                "/forwardK").toInt() * verticalSliderForwardK->maximum());
    verticalSliderBackwardK->setValue(
                settings->value("vehicle/" +
                                currentVehicle +
                                "/thrusters/" +
                                QString::number(currentThruster) +
                                "/backwardK").toInt() * verticalSliderBackwardK->maximum());
    verticalSliderForwardSaturation->setValue(
                settings->value("vehicle/" +
                                currentVehicle +
                                "/thrusters/" +
                                QString::number(currentThruster) +
                                "/forwardSaturation").toInt());
    verticalSliderBackwardSaturation->setValue(
                settings->value("vehicle/" +
                                currentVehicle +
                                "/thrusters/" +
                                QString::number(currentThruster) +
                                "/backwardSaturation").toInt());
    qDebug () << settings->value(
                     "vehicle/" +
                     currentVehicle +
                     "/thrusters/" +
                     QString::number(currentThruster) + "/name").toString() << "Thrusters updated";
}

void ThrusterSettings::thrusterButtonClicked(int value)
{
    currentThruster = value;
    updateThrusterSettings();
}

void ThrusterSettings::thrusterIdChanged(int value)
{
    settings->setValue("vehicle/" +
                       currentVehicle +
                       "/thrusters/" +
                       QString::number(currentThruster) +
                       "/id", value);
}

void ThrusterSettings::thrusterReverseChanged(int state)
{
    settings->setValue("vehicle/" +
                       currentVehicle +
                       "/thrusters/" +
                       QString::number(currentThruster) +
                       "/reverse", state);
}

void ThrusterSettings::thrusterVelocityChanged(int value)
{
    settings->setValue("vehicle/" +
                       currentVehicle +
                       "/thrusters/" +
                       QString::number(currentThruster) +
                       "/velocity", value);
    spinBoxVelocity->setValue(value);
}

void ThrusterSettings::thrusterKForwardChanged(int value)
{
    settings->setValue("vehicle/" +
                       currentVehicle +
                       "/thrusters/" +
                       QString::number(currentThruster) +
                       "/forwardK", value);
    spinBoxForwardK->setValue(value/1000);
}

void ThrusterSettings::thrusterKBackwardChanged(int value)
{
    settings->setValue("vehicle/" +
                       currentVehicle +
                       "/thrusters/" +
                       QString::number(currentThruster) +
                       "/backwardK", value);
    spinBoxBackwardK->setValue(value/1000);
}

void ThrusterSettings::thrusterForwardSaturationChanged(int value)
{
    settings->setValue("vehicle/" +
                       currentVehicle +
                       "/thrusters/" +
                       QString::number(currentThruster) +
                       "/forwardSaturation", value);
    spinBoxForwardSaturation->setValue(value);
}

void ThrusterSettings::thrusterBackwardSaturationChanged(int value)
{
    settings->setValue("vehicle/" +
                       currentVehicle +
                       "/thrusters/" +
                       QString::number(currentThruster) +
                       "/backwardSaturation", value);
    spinBoxBackwardSaturation->setValue(value);
}


