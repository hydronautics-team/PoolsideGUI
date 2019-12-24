#include "thrustersettings.h"
#include <QDebug>
#include <QFileInfo>

ThrusterSettings::ThrusterSettings(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    qDebug () << " - ThrusterSettings constructor";

    connect(this, SIGNAL(updateVehicle()),
            this, SLOT(updateThrusterSettings()));

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
            this, SLOT(thrusterKForwardChanged(int))); // thruster id
    connect(checkBoxReverse, SIGNAL(stateChanged(int)),
            this, SLOT(thrusterReverseEnabled(int))); //thruster reverse

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
}

void ThrusterSettings::updateThrusterSettings()
{
    foreach (QAbstractButton *button, thrusterButtonGroup->buttons()) {
        button->hide();
    }
    //update buttons
    for (int i = 0; i < thrustersCount; i++){
        thrusterButtonGroup->button(i)->show();
        thrusterButtonGroup->button(i)->setText(settings->value(
                                                    "vehicle/" +
                                                    currentVehicle +
                                                    "/thrusters/" +
                                                    QString::number(i)).toString());
    }
    /*
    idSpinBox->setValue(settings->value(
                            "vehicle/" +
                            currentVehicle +
                            "/thrusters/" +
                            QString::number(currentThruster) +
                            "/id").toInt());
    checkBoxReverse->setChecked();
    verticalSliderVelocity->setValue(settings->thrusters_configs[settings->current_thrusters_numb].velocity);
    verticalSliderForwardK->setValue(static_cast<int>(settings->thrusters_configs[settings->current_thrusters_numb].kForward*ui->verticalSliderForwardK->maximum()));
    verticalSliderBackwardK->setValue(static_cast<int>(settings->thrusters_configs[settings->current_thrusters_numb].kBackward*ui->verticalSliderBackwardK->maximum()));
    verticalSliderForwardSaturation->setValue(settings->thrusters_configs[settings->current_thrusters_numb].forward_saturation);
    verticalSliderBackwardSaturation->setValue(settings->thrusters_configs[settings->current_thrusters_numb].backward_saturation);
    */

    qDebug () << currentVehicle + " (Thrusters)";
}

void ThrusterSettings::thrusterButtonClicked(int value)
{
    emit flashVehicle();
}

void ThrusterSettings::thrusterIdChanged(int value)
{
    emit flashVehicle();
}

void ThrusterSettings::thrusterReverseEnabled(int state)
{
    emit flashVehicle();
}

void ThrusterSettings::thrusterVelocityChanged(int value)
{
    settings->beginGroup("vehicle/" + currentVehicle + "/thrusters/" + QString::number(currentThruster));
    settings->setValue("thrusterVelocity", value);
    settings->endGroup();

    spinBoxVelocity->setValue(value);
    emit flashVehicle();
}

void ThrusterSettings::thrusterKForwardChanged(int value)
{
    settings->beginGroup("vehicle/" + currentVehicle + "/thrusters/" + QString::number(currentThruster));
    settings->setValue("ForwardK", value);
    settings->endGroup();

    spinBoxForwardK->setValue(value);
    emit flashVehicle();
}

void ThrusterSettings::thrusterKBackwardChanged(int value)
{
    settings->beginGroup("vehicle/" + currentVehicle + "/thrusters/" + QString::number(currentThruster));
    settings->setValue("BackwardK", value);
    settings->endGroup();

    spinBoxBackwardK->setValue(value);
    emit flashVehicle();
}

void ThrusterSettings::thrusterForwardSaturationChanged(int value)
{
    settings->beginGroup("vehicle/" + currentVehicle + "/thrusters/" + QString::number(currentThruster));
    settings->setValue("ForwardSaturation", value);
    settings->endGroup();

    spinBoxForwardSaturation->setValue(value);
    emit flashVehicle();
}

void ThrusterSettings::thrusterBackwardSaturationChanged(int value)
{
    settings->beginGroup("vehicle/" + currentVehicle + "/thrusters/" + QString::number(currentThruster));
    settings->setValue("BackwardSaturation", value);
    settings->endGroup();

    spinBoxBackwardSaturation->setValue(value);
    emit flashVehicle();
}


