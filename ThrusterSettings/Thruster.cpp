#include "Thruster.h"
#include "ui_Thruster.h"
#include "Thruster.moc"

Thruster::Thruster(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Thruster) {
    ui->setupUi(this);

    //change parameters
    connect(ui->CheckBox_ThrusterPower, SIGNAL(stateChanged(int)), this, SLOT(powerChanged(int)));
    connect(ui->SpinBox_ThrusterId, SIGNAL(valueChanged(int)), this, SLOT(idChanged(int)));
    connect(ui->SpinBox_ThrusterSetSpeed, SIGNAL(valueChanged(int)), this, SLOT(speedChanged(int)));
    connect(ui->DoubleSpinBox_SetForwardK, SIGNAL(valueChanged(double)), this, SLOT(forwardKChanged(double)));
    connect(ui->DoubleSpinBox_SetBackwardK, SIGNAL(valueChanged(double)), this, SLOT(backwardKChanged(double)));
    connect(ui->SpinBox_ThrusterSetForwardSaturation, SIGNAL(valueChanged(int)), this, SLOT(forwardSaturationChanged(int)));
    connect(ui->SpinBox_ThrusterSetBackwardSaturation, SIGNAL(valueChanged(int)), this, SLOT(backwardSaturationChanged(int)));
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

void Thruster::setThruster(int number, json ThrusterJson) {
    this->ThisThruster.slot = number;
    this->ThrusterJson = ThrusterJson;
    emit setUV_Thruster();
    emit setUi();

    qDebug() << ThisThruster.name;
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

void  Thruster::setUi() {
    ui->Label_ThrusterName->setText(QString::fromStdString(ThrusterJson["name"]));
    ui->SpinBox_ThrusterId->setValue(ThrusterJson["id"]);
    ui->DoubleSpinBox_SetForwardK->setValue(ThrusterJson["kForward"]);
    ui->DoubleSpinBox_SetBackwardK->setValue(ThrusterJson["kBackward"]);
    ui->SpinBox_ThrusterSetForwardSaturation->setValue(ThrusterJson["forward_saturation"]);
    ui->SpinBox_ThrusterSetBackwardSaturation->setValue(ThrusterJson["backward_saturation"]);
    if (ThrusterJson["reverse"] == true) {
        ui->CheckBox_ThrusterReverse->setCheckState(Qt::Checked);
    } else{
        ui->CheckBox_ThrusterReverse->setCheckState(Qt::Unchecked);
    }
}

//json Thruster::configureJson() {
//    ThrusterJson["name"] = ui->Label_ThrusterName->text().toStdString();
//    ui->Label_ThrusterName->text();
//    ThrusterJson["id"] = ui->SpinBox_ThrusterId->value();
//
//    ThrusterJson["kForward"] = ui->DoubleSpinBox_SetForwardK->value();
//    ThrusterJson["kBackward"] = ui->DoubleSpinBox_SetBackwardK->value();
//
//    ThrusterJson["forward_saturation"] = ui->SpinBox_ThrusterSetForwardSaturation->value();
//    ThrusterJson["backward_saturation"] = ui->SpinBox_ThrusterSetBackwardSaturation->value();
//
//    ThrusterJson["reverse"] = !!ui->CheckBox_ThrusterReverse->checkState();
//
//    return ThrusterJson;
//}
//
//UV_Thruster Thruster::configureUV_Thruster() {
//
//    return ThisThruster
//}

//json Thruster::getThrusterJson() {
//    return ThrusterJson;
//}
//
//UV_Thruster Thruster::getThisThruster() {
//    return ThisThruster;
//}

void Thruster::powerChanged(int power){
    if (power == 0) {
        emit() //TODO вызов сизнала, который нужно реалтзовать
    } else{
        emit()
    }
}

void Thruster::idChanged(int id){
    ThrusterJson["id"] = id;
    ThisThruster.id = id;
    emit parametorsChanged(ThrusterJson, ThisThruster);
}
void Thruster::speedChanged(int speed){
    ThisThruster.velocity = speed;
    emit parametorsChanged(ThrusterJson, ThisThruster);
}
void Thruster::forwardKChanged(double forwardK){
    ThrusterJson["kForward"] = forwardK;
    ThisThruster.kForward = forwardK;
    emit parametorsChanged(ThrusterJson, ThisThruster);
}
void Thruster::backwardKChanged(double backwardK){
    ThrusterJson["kBackward"] = backwardK;
    ThisThruster.kBackward = backwardK;
    emit parametorsChanged(ThrusterJson, ThisThruster);
}
void Thruster::forwardSaturationChanged(int forwardSaturation){
    ThrusterJson["forward_saturation"] = forwardSaturation;
    ThisThruster.sForward = forwardSaturation;
    emit parametorsChanged(ThrusterJson, ThisThruster);
}
void Thruster::backwardSaturationChanged(int backwardSaturation){
    ThrusterJson["backward_saturation"] = backwardSaturation;
    ThisThruster.sBackward = backwardSaturation;
    emit parametorsChanged(ThrusterJson, ThisThruster);
}
void Thruster::reverseChanged(int state){
    ThrusterJson["reverse"] = !!state;
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
