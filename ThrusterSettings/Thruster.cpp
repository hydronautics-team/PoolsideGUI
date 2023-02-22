#include "Thruster.h"
#include "ui_Thruster.h"
#include "Thruster.moc"

Thruster::Thruster(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Thruster) {
    ui->setupUi(this);

    //change parameters
    connect(ui->CheckBox_ThrusterPower, SIGNAL(stateChanged(int)), this, SLOT(powerCheckBoxChanged(int)));
    connect(ui->SpinBox_ThrusterId, SIGNAL(valueChanged(int)), this, SLOT(idChanged(int)));
    connect(ui->SpinBox_ThrusterSetSpeed, SIGNAL(valueChanged(int)), this, SLOT(speedChanged(int)));
    connect(ui->DoubleSpinBox_SetForwardK, SIGNAL(valueChanged(double)), this, SLOT(forwardKChanged(double)));
    connect(ui->DoubleSpinBox_SetBackwardK, SIGNAL(valueChanged(double)), this, SLOT(backwardKChanged(double)));
    connect(ui->SpinBox_ThrusterSetForwardSaturation, SIGNAL(valueChanged(int)), this,
            SLOT(forwardSaturationChanged(int)));
    connect(ui->SpinBox_ThrusterSetBackwardSaturation, SIGNAL(valueChanged(int)), this,
            SLOT(backwardSaturationChanged(int)));
    connect(ui->CheckBox_ThrusterReverse, SIGNAL(stateChanged(int)), this, SLOT(reverseChanged(int)));

    //speed
    connect(ui->PushButton_ThrusterSetForward, SIGNAL(clicked()), this, SLOT(speedSetForward()));
    connect(ui->PushButton_ThrusterSetStop, SIGNAL(clicked()), this, SLOT(speedSetStop()));
    connect(ui->PushButton_ThrusterSetBackward, SIGNAL(clicked()), this, SLOT(speedSetBackward()));
    connect(this, SIGNAL(speedSpinBoxChange(int)), ui->SpinBox_ThrusterSetSpeed, SLOT(setValue(int)));
}

Thruster::~Thruster() {
    delete ui;
}

UV_Thruster Thruster::getUV_Thruster() {
    return ThisThruster;
}

void Thruster::setThruster(int number, json ThrusterJson) {
    this->ThisThruster.slot = number;
    this->ThrusterJson = ThrusterJson;
    emit setUV_Thruster();
    emit setUi();
}

void Thruster::setAutoSave(int autoSave) {
    this->autoSave = !!autoSave;
}

void Thruster::save(bool click) {
    ThrusterJson["id"] = ThisThruster.id;
    ThrusterJson["kForward"] = ThisThruster.kForward;
    ThrusterJson["kBackward"] = ThisThruster.kBackward;
    ThrusterJson["forward_saturation"] = ThisThruster.sForward;
    ThrusterJson["backward_saturation"] = ThisThruster.sBackward;
    ThrusterJson["reverse"] = ThisThruster.reverse;

    emit parametorsChanged(ThrusterJson, ThisThruster);
}

void Thruster::setUV_Thruster() {
    ThisThruster.name = QString::fromStdString(ThrusterJson["name"]);
    ThisThruster.id = ThrusterJson["id"];
    ThisThruster.reverse = ThrusterJson["reverse"];
    ThisThruster.kForward = ThrusterJson["kForward"];
    ThisThruster.kBackward = ThrusterJson["kBackward"];
    ThisThruster.sForward = ThrusterJson["forward_saturation"];
    ThisThruster.sBackward = ThrusterJson["backward_saturation"];
}

void Thruster::setUi() {
    ui->SpinBox_ThrusterId->setEnabled(!power);
    ui->Label_ThrusterName->setText(QString::fromStdString(ThrusterJson["name"]));
    ui->SpinBox_ThrusterId->setValue(ThrusterJson["id"]);
    ui->DoubleSpinBox_SetForwardK->setValue(ThrusterJson["kForward"]);
    ui->DoubleSpinBox_SetBackwardK->setValue(ThrusterJson["kBackward"]);
    ui->SpinBox_ThrusterSetForwardSaturation->setValue(ThrusterJson["forward_saturation"]);
    ui->SpinBox_ThrusterSetBackwardSaturation->setValue(ThrusterJson["backward_saturation"]);
    if (ThrusterJson["reverse"] == true) {
        ui->CheckBox_ThrusterReverse->setCheckState(Qt::Checked);
    } else {
        ui->CheckBox_ThrusterReverse->setCheckState(Qt::Unchecked);
    }
}

void Thruster::powerCheckBoxChanged(int power) {
    ThisThruster.power = power;
    ui->SpinBox_ThrusterId->setEnabled(!power);
    emit parametorsChanged(ThrusterJson, ThisThruster);
}

void Thruster::idChanged(int id) {
    ui->SpinBox_ThrusterSetSpeed->setValue(0); // обнулям, чтобы не крутились не нужные движки
    ThisThruster.velocity = 0;
    emit parametorsChanged(ThrusterJson, ThisThruster);

    if (autoSave == true) ThrusterJson["id"] = id;

    ThisThruster.id = id;
    emit parametorsChanged(ThrusterJson, ThisThruster);
}

void Thruster::speedChanged(int speed) {
    ThisThruster.velocity = speed;
    emit parametorsChanged(ThrusterJson, ThisThruster);
}

void Thruster::forwardKChanged(double forwardK) {
    if (autoSave == true) ThrusterJson["kForward"] = forwardK;
    ThisThruster.kForward = forwardK;
    emit parametorsChanged(ThrusterJson, ThisThruster);
}

void Thruster::backwardKChanged(double backwardK) {
    if (autoSave == true) ThrusterJson["kBackward"] = backwardK;
    ThisThruster.kBackward = backwardK;
    emit parametorsChanged(ThrusterJson, ThisThruster);
}

void Thruster::forwardSaturationChanged(int forwardSaturation) {
    if (autoSave == true) ThrusterJson["forward_saturation"] = forwardSaturation;
    ThisThruster.sForward = forwardSaturation;
    emit parametorsChanged(ThrusterJson, ThisThruster);
}

void Thruster::backwardSaturationChanged(int backwardSaturation) {
    if (autoSave == true) ThrusterJson["backward_saturation"] = backwardSaturation;
    ThisThruster.sBackward = backwardSaturation;
    emit parametorsChanged(ThrusterJson, ThisThruster);
}

void Thruster::reverseChanged(int state) {
    if (autoSave == true) ThrusterJson["reverse"] = !!state;
    ThisThruster.reverse = !!state;
    emit parametorsChanged(ThrusterJson, ThisThruster);
}

void Thruster::speedSetForward() {
    emit speedSpinBoxChange(15);
}

void Thruster::speedSetStop() {
    emit speedSpinBoxChange(0);
}

void Thruster::speedSetBackward() {
    emit speedSpinBoxChange(-15);
}
