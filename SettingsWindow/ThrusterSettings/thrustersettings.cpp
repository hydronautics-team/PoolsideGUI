#include "thrustersettings.h"
#include "UV/uv_state.h"
#include "UV/ibasicdata.h"

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
    thrustersCount = settings->value("vehicle/" +
                                     currentVehicle +
                                     "/thrusters/count").toInt();

    // add buttons in group to easily access
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
            this, SLOT(thrusterButtonClicked(int)));    // thruster button clicked
    connect(idSpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(thrusterIdChanged(int)));        // thruster id
    connect(checkBoxReverse, SIGNAL(stateChanged(int)),
            this, SLOT(thrusterReverseChanged(int)));   // thruster reverse
    connect(flashButton, SIGNAL(clicked()),
            this, SLOT(flashButtonClicked()));          // flash button

    // sliders
    connect(verticalSliderVelocity, SIGNAL(valueChanged(int)),
            this, SLOT(sliderVelocityChanged(int)));
    connect(verticalSliderForwardK, SIGNAL(valueChanged(int)),
            this, SLOT(sliderKForwardChanged(int)));
    connect(verticalSliderBackwardK, SIGNAL(valueChanged(int)),
            this, SLOT(sliderKBackwardChanged(int)));
    connect(verticalSliderForwardSaturation, SIGNAL(valueChanged(int)),
            this, SLOT(sliderForwardSaturationChanged(int)));
    connect(verticalSliderBackwardSaturation, SIGNAL(valueChanged(int)),
            this, SLOT(sliderBackwardSaturationChanged(int)));

    // spin boxes
    connect(spinBoxVelocity, SIGNAL(valueChanged(int)),
            this, SLOT(spinBoxVelocityChanged(int)));
    connect(spinBoxForwardK, SIGNAL(valueChanged(double)),
            this, SLOT(spinBoxKForwardChanged(double)));
    connect(spinBoxBackwardK, SIGNAL(valueChanged(double)),
            this, SLOT(spinBoxKBackwardChanged(double)));
    connect(spinBoxForwardSaturation, SIGNAL(valueChanged(int)),
            this, SLOT(spinBoxForwardSaturationChanged(int)));
    connect(spinBoxBackwardSaturation, SIGNAL(valueChanged(int)),
            this, SLOT(spinBoxBackwardSaturationChanged(int)));

    updateThrusterSettings();
}

void ThrusterSettings::updateVehicle()
{
    currentVehicle = settings->value("currentVehicle").toString();
    thrustersCount = settings->value("vehicle/" +
                                     currentVehicle +
                                     "/thrusters/count").toInt();
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
                                                    QString::number(i) +
                                                    "/name").toString());
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
                static_cast<int>(settings->value("vehicle/" +
                                                 currentVehicle +
                                                 "/thrusters/" +
                                                 QString::number(currentThruster) +
                                                 "/forwardK").toDouble() * verticalSliderForwardK->maximum()));
    verticalSliderBackwardK->setValue(
                static_cast<int>(settings->value("vehicle/" +
                                                 currentVehicle +
                                                 "/thrusters/" +
                                                 QString::number(currentThruster) +
                                                 "/backwardK").toDouble() * verticalSliderBackwardK->maximum()));
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
//    UV_State *state;
//    IBasicData interface(&UVState, &UVMutex);
//    state = interface.gainAccess();
//    state->ThrusterSelected = static_cast<uint8_t>(value);
//    interface.closeAccess();

    currentThruster = value;
    updateThrusterSettings();
}

void ThrusterSettings::thrusterIdChanged(int value)
{
//    UV_State *state;
//    IBasicData interface(&UVState, &UVMutex);
//    state = interface.gainAccess();
//    state->thrusters[currentThruster].id = value;
//    interface.closeAccess();

    settings->setValue("vehicle/" +
                       currentVehicle +
                       "/thrusters/" +
                       QString::number(currentThruster) +
                       "/id", value);
}

void ThrusterSettings::thrusterReverseChanged(int state)
{
//    UV_State *cstate;
//    IBasicData interface(&UVState, &UVMutex);
//    cstate = interface.gainAccess();
//    cstate->thrusters[currentThruster].reverse = state;
//    interface.closeAccess();

    settings->setValue("vehicle/" +
                       currentVehicle +
                       "/thrusters/" +
                       QString::number(currentThruster) +
                       "/reverse", state);
}

void ThrusterSettings::flashButtonClicked()
{
    emit flashVehicle();
}

void ThrusterSettings::sliderVelocityChanged(int value)
{
//    UV_State *cstate;
//    IBasicData interface(&UVState, &UVMutex);
//    cstate = interface.gainAccess();
//    cstate->thrusters[currentThruster].velocity = static_cast<int8_t>(value);
//    interface.closeAccess();

    settings->setValue("vehicle/" +
                       currentVehicle +
                       "/thrusters/" +
                       QString::number(currentThruster) +
                       "/velocity", value);
    spinBoxVelocity->setValue(value);
}

void ThrusterSettings::sliderKForwardChanged(int value)
{
//    UV_State *cstate;
//    IBasicData interface(&UVState, &UVMutex);
//    cstate = interface.gainAccess();
//    cstate->thrusters[currentThruster].kForward = static_cast<int8_t>(value);
//    interface.closeAccess();

    double d_value = value / verticalSliderForwardK->maximum();
    settings->setValue("vehicle/" +
                       currentVehicle +
                       "/thrusters/" +
                       QString::number(currentThruster) +
                       "/forwardK", d_value);
    spinBoxForwardK->setValue(d_value);
}

void ThrusterSettings::sliderKBackwardChanged(int value)
{
//    UV_State *cstate;
//    IBasicData interface(&UVState, &UVMutex);
//    cstate = interface.gainAccess();
//    cstate->thrusters[currentThruster].kBackward = static_cast<int8_t>(value);
//    interface.closeAccess();

    double d_value = value / verticalSliderBackwardK->maximum();
    settings->setValue("vehicle/" +
                       currentVehicle +
                       "/thrusters/" +
                       QString::number(currentThruster) +
                       "/backwardK", d_value);
    spinBoxBackwardK->setValue(d_value);
}

void ThrusterSettings::sliderForwardSaturationChanged(int value)
{
//    UV_State *cstate;
//    IBasicData interface(&UVState, &UVMutex);
//    cstate = interface.gainAccess();
//    cstate->thrusters[currentThruster].sForward = static_cast<int8_t>(value);
//    interface.closeAccess();

    settings->setValue("vehicle/" +
                       currentVehicle +
                       "/thrusters/" +
                       QString::number(currentThruster) +
                       "/forwardSaturation", value);
    spinBoxForwardSaturation->setValue(value);
}

void ThrusterSettings::sliderBackwardSaturationChanged(int value)
{
//    UV_State *cstate;
//    IBasicData interface(&UVState, &UVMutex);
//    cstate = interface.gainAccess();
//    cstate->thrusters[currentThruster].sBackward = static_cast<int8_t>(value);
//    interface.closeAccess();

    settings->setValue("vehicle/" +
                       currentVehicle +
                       "/thrusters/" +
                       QString::number(currentThruster) +
                       "/backwardSaturation", value);
    spinBoxBackwardSaturation->setValue(value);
}

void ThrusterSettings::spinBoxVelocityChanged(int value)
{
//    UV_State *cstate;
//    IBasicData interface(&UVState, &UVMutex);
//    cstate = interface.gainAccess();
//    cstate->thrusters[currentThruster].velocity = static_cast<int8_t>(value);
//    interface.closeAccess();

    settings->setValue("vehicle/" +
                       currentVehicle +
                       "/thrusters/" +
                       QString::number(currentThruster) +
                       "/velocity", value);
    verticalSliderVelocity->setValue(value);
}

void ThrusterSettings::spinBoxKForwardChanged(double value)
{
    int i_value = static_cast<int>(value * verticalSliderForwardK->maximum());
    settings->setValue("vehicle/" +
                       currentVehicle +
                       "/thrusters/" +
                       QString::number(currentThruster) +
                       "/forwardK", value);
    verticalSliderForwardK->setValue(i_value);
}

void ThrusterSettings::spinBoxKBackwardChanged(double value)
{
    int i_value = static_cast<int>(value * verticalSliderBackwardK->maximum());
    settings->setValue("vehicle/" +
                       currentVehicle +
                       "/thrusters/" +
                       QString::number(currentThruster) +
                       "/backwardK", value);
    verticalSliderBackwardK->setValue(i_value);
}

void ThrusterSettings::spinBoxForwardSaturationChanged(int value)
{
    settings->setValue("vehicle/" +
                       currentVehicle +
                       "/thrusters/" +
                       QString::number(currentThruster) +
                       "/forwardSaturation", value);
    verticalSliderForwardSaturation->setValue(value);
}

void ThrusterSettings::spinBoxBackwardSaturationChanged(int value)
{
    settings->setValue("vehicle/" +
                       currentVehicle +
                       "/thrusters/" +
                       QString::number(currentThruster) +
                       "/backwardSaturation", value);
    verticalSliderBackwardSaturation->setValue(value);
}


