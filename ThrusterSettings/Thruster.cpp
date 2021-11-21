#include "Thruster.h"
#include "ui_Thruster.h"
#include "Thruster.moc"

Thruster::Thruster(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Thruster) {
    ui->setupUi(this);

    //speed
    connect(ui->PushButton_ThrusterSetForward, SIGNAL(clicked()), this, SLOT(speedSetForward()));
    connect(ui->PushButton_ThrusterSetStop, SIGNAL(clicked()), this, SLOT(speedSetStop()));
    connect(ui->PushButton_ThrusterSetBackward, SIGNAL(clicked()), this, SLOT(speedSetBackward()));
    connect(this, SIGNAL(speedSpinBoxChange(int)), ui->SpinBox_ThrusterSetSpeed, SLOT(setValue(int)));

    // K and Saturation

}

Thruster::~Thruster() {
    delete ui;
}

//UV_Thruster Thruster::ThrusterDataChanged() {
//    ThisThruster.id
//}

void Thruster::setThruster(int number) {
    std::ifstream file("thrusterJson.json");
    json fullJson;
    file >> fullJson;
    file.close();

    ThisThrusterJson = fullJson["thrusters"][number];

    qDebug() << QString::fromStdString(ThisThrusterJson["name"]);

    ui->Label_ThrusterName->setText(QString::fromStdString(ThisThrusterJson["name"]));
    ThisThruster.name = name;
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
