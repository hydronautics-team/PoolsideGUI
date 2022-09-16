#include "StabilizationWindow.h"
#include "ui_StabilizationWindow.h"

double X[2000][2];

StabilizationWindow::StabilizationWindow(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::StabilizationWindow) {
    ui->setupUi(this);

    updateStabilizationState = new QTimer(this);
    connect(updateStabilizationState, SIGNAL(timeout()), this, SLOT(updateStabilizationStateUi()));
//    connect(updateStabilizationState, SIGNAL(timeout()), this, SLOT(ContourEdited()));
    updateStabilizationState->start(100);

    jsonName = "stabilizationJson.json";
    std::ifstream file(jsonName.toStdString());
    if (!file) {
        qDebug() << jsonName << " не открыт";
        createDefaultStabilizationJson();
        std::ifstream file(jsonName.toStdString());
        qDebug() << jsonName << " создан";
        file >> allStabilizationJson;
        file.close();
    } else {
        qDebug() << jsonName << " открыт";
        allStabilizationJson = json::parse(file);
        file.close();
    }
//    ros_config = json::parse(std::ifstream("/configs/ros.json"));
    connect(ui->pushButton_CS_saveConfig, SIGNAL(released()), this, SLOT(saveToJsonFile()));

    // TODO:нужно что-то сделать с огромным количеством кода
    connect(ui->doubleSpinBox_CS_pErrGain, SIGNAL(valueChanged(double)), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_pJoyUnitCast, SIGNAL(valueChanged(double)), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_pSpeedDyn, SIGNAL(valueChanged(double)), this, SLOT(ContourEdited()));

    connect(ui->doubleSpinBox_CS_pThrustersCast, SIGNAL(valueChanged(double)), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_pThrustersMax, SIGNAL(valueChanged(double)), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_pThrustersMin, SIGNAL(valueChanged(double)), this, SLOT(ContourEdited()));

    connect(ui->doubleSpinBox_CS_pid_iGain, SIGNAL(valueChanged(double)), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_pid_iMax, SIGNAL(valueChanged(double)), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_pid_iMin, SIGNAL(valueChanged(double)), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_pid_pGain, SIGNAL(valueChanged(double)), this, SLOT(ContourEdited()));

    connect(ui->doubleSpinBox_CS_posFilterK, SIGNAL(valueChanged(double)), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_posFilterT, SIGNAL(valueChanged(double)), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_speedFilterK, SIGNAL(valueChanged(double)), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_speedFilterT, SIGNAL(valueChanged(double)), this, SLOT(ContourEdited()));

    connect(ui->radioButton_CS_YawSelect, SIGNAL(clicked()), this, SLOT(ContourChanged()));
    connect(ui->radioButton_CS_RollSelect, SIGNAL(clicked()), this, SLOT(ContourChanged()));
    connect(ui->radioButton_CS_PitchSelect, SIGNAL(clicked()), this, SLOT(ContourChanged()));
    connect(ui->radioButton_CS_DepthSelect, SIGNAL(clicked()), this, SLOT(ContourChanged()));
    connect(ui->radioButton_CS_MarchSelect, SIGNAL(clicked()), this, SLOT(ContourChanged()));
    connect(ui->radioButton_CS_LagSelect, SIGNAL(clicked()), this, SLOT(ContourChanged()));

    X_Protocol = new x_protocol("protocols.conf", "xi", X);

    controlContour_amount = allStabilizationJson["stabilizationСontour"].size();
    qDebug() << "controlContour_amount in allStabilizationJson" <<controlContour_amount;
    ConstantsControlContour = new UV_StabilizationConstants[controlContour_amount];
    StateControlContour = new UV_StabilizationState[controlContour_amount];
    interface.setControlContourAmount(controlContour_amount);
    for (int i = 0; i < controlContour_amount; ++i) {
        setUV_ControlContour(i, allStabilizationJson["stabilizationСontour"][i]);
        interface.setControlContourData(i, ConstantsControlContour[i]);
    }

    emit ui->radioButton_CS_YawSelect->setChecked(true);
    emit ContourChanged();
}
void StabilizationWindow::updateStabilizationStateUi() {
    StateControlContour[currentContour] = interface.getControlContourData(currentContour).state;

//    qDebug() << "currentContour StateUi " << currentContour;

    ui->lineEdit_CS_inputSignal->setText(QString::number(StateControlContour[currentContour].inputSignal));
    ui->lineEdit_CS_speedSignal->setText(QString::number(StateControlContour[currentContour].speedSignal));
    ui->lineEdit_CS_speedFiltered->setText(QString::number(StateControlContour[currentContour].speedFiltered));
    ui->lineEdit_CS_posSignal->setText(QString::number(StateControlContour[currentContour].posSignal));

    ui->lineEdit_CS_joyUnitCasted->setText(QString::number(StateControlContour[currentContour].joyUnitCasted));
    ui->lineEdit_CS_joy_iValue->setText(QString::number(StateControlContour[currentContour].joy_iValue));
    ui->lineEdit_CS_posError->setText(QString::number(StateControlContour[currentContour].posError));
    ui->lineEdit_CS_speedError->setText(QString::number(StateControlContour[currentContour].speedError));
    ui->lineEdit_CS_dynSummator->setText(QString::number(StateControlContour[currentContour].dynSummator));
    ui->lineEdit_CS_pidValue->setText(QString::number(StateControlContour[currentContour].pidValue));
    ui->lineEdit_CS_posError->setText(QString::number(StateControlContour[currentContour].posErrorAmp));
    ui->lineEdit_CS_posFiltered->setText(QString::number(StateControlContour[currentContour].posFiltered));
    ui->lineEdit_CS_pid_iValue->setText(QString::number(StateControlContour[currentContour].pid_iValue));

    updateVariables_KX();

//    qDebug() << "currentContour].pid_iValue" << StateControlContour[currentContour].pid_iValue;
}

void StabilizationWindow::ContourChanged() {
    if (ui->radioButton_CS_YawSelect->isChecked() == true) {currentContour = CONTOUR_YAW; interface.setCurrentControlContour(CONTOUR_YAW); qDebug() << "currentContour" << CONTOUR_YAW;}
    if (ui->radioButton_CS_RollSelect->isChecked() == true) {currentContour = CONTOUR_ROLL; interface.setCurrentControlContour(CONTOUR_ROLL); qDebug() << "currentContour" << CONTOUR_ROLL;}
    if (ui->radioButton_CS_PitchSelect->isChecked() == true) {currentContour = CONTOUR_PITCH; interface.setCurrentControlContour(CONTOUR_PITCH); qDebug() << "currentContour" << CONTOUR_PITCH;}
    if (ui->radioButton_CS_DepthSelect->isChecked() == true) {currentContour = CONTOUR_DEPTH; interface.setCurrentControlContour(CONTOUR_DEPTH); qDebug() << "currentContour" << CONTOUR_DEPTH;}
    if (ui->radioButton_CS_MarchSelect->isChecked() == true) {currentContour = CONTOUR_MARCH; interface.setCurrentControlContour(CONTOUR_MARCH); qDebug() << "currentContour" << CONTOUR_MARCH;}
    if (ui->radioButton_CS_LagSelect->isChecked() == true) {currentContour = CONTOUR_LAG; interface.setCurrentControlContour(CONTOUR_LAG); qDebug() << "currentContour" << CONTOUR_LAG;}


    // TODO:нужно что-то сделать с огромным количеством кода(например обьеденить doubleSpinBox в массив)
    ui->doubleSpinBox_CS_pJoyUnitCast->setValue(ConstantsControlContour[currentContour].pJoyUnitCast);
    ui->doubleSpinBox_CS_pSpeedDyn->setValue(ConstantsControlContour[currentContour].pSpeedDyn);
    ui->doubleSpinBox_CS_pErrGain->setValue(ConstantsControlContour[currentContour].pErrGain);

    ui->doubleSpinBox_CS_posFilterT->setValue(ConstantsControlContour[currentContour].posFilterT);
    ui->doubleSpinBox_CS_posFilterK->setValue(ConstantsControlContour[currentContour].posFilterK);
    ui->doubleSpinBox_CS_speedFilterT->setValue(ConstantsControlContour[currentContour].speedFilterT);
    ui->doubleSpinBox_CS_speedFilterK->setValue(ConstantsControlContour[currentContour].speedFilterK);

    ui->doubleSpinBox_CS_pid_pGain->setValue(ConstantsControlContour[currentContour].pid_pGain);
    ui->doubleSpinBox_CS_pid_iGain->setValue(ConstantsControlContour[currentContour].pid_iGain);
    ui->doubleSpinBox_CS_pid_iMax->setValue(ConstantsControlContour[currentContour].pid_iMax);
    ui->doubleSpinBox_CS_pid_iMin->setValue(ConstantsControlContour[currentContour].pid_iMin);

    ui->doubleSpinBox_CS_pThrustersMin->setValue(ConstantsControlContour[currentContour].pThrustersMin);
    ui->doubleSpinBox_CS_pThrustersMax->setValue(ConstantsControlContour[currentContour].pThrustersMax);
    ui->doubleSpinBox_CS_pThrustersCast->setValue(ConstantsControlContour[currentContour].pThrustersCast);
}

void StabilizationWindow::ContourEdited() {
    // TODO:нужно что-то сделать с огромным количеством кода
    ConstantsControlContour[currentContour].pJoyUnitCast = ui->doubleSpinBox_CS_pJoyUnitCast->value();
    qDebug() << "pJoyUnitCast" << ConstantsControlContour[currentContour].pJoyUnitCast;
    ConstantsControlContour[currentContour].pSpeedDyn = ui->doubleSpinBox_CS_pSpeedDyn->value();
    ConstantsControlContour[currentContour].pErrGain = ui->doubleSpinBox_CS_pErrGain->value();

    ConstantsControlContour[currentContour].posFilterT = ui->doubleSpinBox_CS_posFilterT->value();
    ConstantsControlContour[currentContour].posFilterK = ui->doubleSpinBox_CS_posFilterK->value();
    ConstantsControlContour[currentContour].speedFilterT = ui->doubleSpinBox_CS_speedFilterT->value();
    ConstantsControlContour[currentContour].speedFilterK = ui->doubleSpinBox_CS_speedFilterK->value();
    qDebug() << "ConstantsControlContour[currentContour].speedFilterK" << ConstantsControlContour[currentContour].speedFilterK;


    ConstantsControlContour[currentContour].pid_pGain = ui->doubleSpinBox_CS_pid_pGain->value();
    ConstantsControlContour[currentContour].pid_iGain = ui->doubleSpinBox_CS_pid_iGain->value();
    ConstantsControlContour[currentContour].pid_iMax = ui->doubleSpinBox_CS_pid_iMax->value();
    ConstantsControlContour[currentContour].pid_iMin = ui->doubleSpinBox_CS_pid_iMin->value();

    ConstantsControlContour[currentContour].pThrustersMin = ui->doubleSpinBox_CS_pThrustersMin->value();
    ConstantsControlContour[currentContour].pThrustersMax = ui->doubleSpinBox_CS_pThrustersMax->value();
    ConstantsControlContour[currentContour].pThrustersCast = ui->doubleSpinBox_CS_pThrustersCast->value();

    interface.setControlContourData(currentContour, ConstantsControlContour[currentContour]);
    qDebug() << "Contour.pJoyUnitCast" << currentContour << ConstantsControlContour[currentContour].pJoyUnitCast;
}

StabilizationWindow::~StabilizationWindow() {
    delete[] ConstantsControlContour;
    delete ui;
}

void StabilizationWindow::saveToJsonFile() {
    for (int i = 0; i < controlContour_amount; ++i) {
        allStabilizationJson["stabilizationСontour"][i]["pJoyUnitCast"] = ConstantsControlContour[i].pJoyUnitCast;
        allStabilizationJson["stabilizationСontour"][i]["pSpeedDyn"] = ConstantsControlContour[i].pSpeedDyn;
        allStabilizationJson["stabilizationСontour"][i]["pErrGain"] = ConstantsControlContour[i].pErrGain;
        allStabilizationJson["stabilizationСontour"][i]["posFilterT"] = ConstantsControlContour[i].posFilterT;
        allStabilizationJson["stabilizationСontour"][i]["posFilterK"] = ConstantsControlContour[i].posFilterK;
        allStabilizationJson["stabilizationСontour"][i]["speedFilterT"] = ConstantsControlContour[i].speedFilterT;
        allStabilizationJson["stabilizationСontour"][i]["speedFilterK"] = ConstantsControlContour[i].speedFilterK;
        allStabilizationJson["stabilizationСontour"][i]["pid_pGain"] = ConstantsControlContour[i].pid_pGain;
        allStabilizationJson["stabilizationСontour"][i]["pid_iGain"] = ConstantsControlContour[i].pid_iGain;
        allStabilizationJson["stabilizationСontour"][i]["pid_iMax"] = ConstantsControlContour[i].pid_iMax;
        allStabilizationJson["stabilizationСontour"][i]["pid_iMin"] = ConstantsControlContour[i].pid_iMin;
        allStabilizationJson["stabilizationСontour"][i]["pThrustersMin"] = ConstantsControlContour[i].pThrustersMin;
        allStabilizationJson["stabilizationСontour"][i]["pThrustersMax"] = ConstantsControlContour[i].pThrustersMax;
        allStabilizationJson["stabilizationСontour"][i]["pThrustersCast"] = ConstantsControlContour[i].pThrustersCast;
    };
    std::ofstream o(jsonName.toStdString());
    o << std::setw(4) << allStabilizationJson << std::endl;
    o.close();
}

void StabilizationWindow::setUV_ControlContour(int number, json StabilizationJson) {
    // TODO:нужно что-то сделать с огромным количеством кода
//    qDebug() << "setUV_ControlContour pThrustersMax" << StabilizationJson["pThrustersMax"].type_name();
    auto v4 = StabilizationJson["pThrustersMax"].get<float>();
    qDebug() << "setUV_ControlContour pThrustersMax" << v4;

//    ConstantsControlContour[number].pJoyUnitCast = StabilizationJson.get<float>("pJoyUnitCast");
//            StabilizationJson.get("pJoyUnitCast")
//            ["pJoyUnitCast"];
    ConstantsControlContour[number].pSpeedDyn = StabilizationJson["pSpeedDyn"];
    ConstantsControlContour[number].pErrGain = StabilizationJson["pErrGain"];

    ConstantsControlContour[number].posFilterT = StabilizationJson["posFilterT"];
    ConstantsControlContour[number].posFilterK = StabilizationJson["posFilterK"];
    ConstantsControlContour[number].speedFilterT = StabilizationJson["speedFilterT"];
    ConstantsControlContour[number].speedFilterK = StabilizationJson["speedFilterK"];

    ConstantsControlContour[number].pid_pGain = StabilizationJson["pid_pGain"];
    ConstantsControlContour[number].pid_iGain = StabilizationJson["pid_iGain"];
    ConstantsControlContour[number].pid_iMax = StabilizationJson["pid_iMax"];
    ConstantsControlContour[number].pid_iMin = StabilizationJson["pid_iMin"];

    ConstantsControlContour[number].pThrustersMin = StabilizationJson["pThrustersMin"];
    ConstantsControlContour[number].pThrustersMax = v4;
    ConstantsControlContour[number].pThrustersCast = StabilizationJson["pThrustersCast"];

    ConstantsControlContour[number].thrustersFilterT = StabilizationJson["thrustersFilterT"];
    ConstantsControlContour[number].thrustersFilterK = StabilizationJson["thrustersFilterK"];

    ConstantsControlContour[number].sOutSummatorMax = StabilizationJson["sOutSummatorMax"];
    ConstantsControlContour[number].sOutSummatorMin = StabilizationJson["sOutSummatorMin"];
    qDebug() << "setUV_ControlContour sOutSummatorMin" << ConstantsControlContour[number].sOutSummatorMin;


}


void StabilizationWindow::createDefaultStabilizationJson() {
    std::ofstream o(jsonName.toStdString());
    json j = {{"stabilizationСontour", {
            {
                    {"name", "Depth"},

                    {"pJoyUnitCast", 1},
                    {"pSpeedDyn", 1},
                    {"pErrGain", 1},

                    {"posFilterT", 1},
                    {"posFilterK", 1},
                    {"speedFilterT", 1},
                    {"speedFilterK", 1},

                    {"pid_pGain", 1},
                    {"pid_iGain", 1},
                    {"pid_iMax", 1},
                    {"pid_iMin", 1},

                    {"pThrustersMin", 1},
                    {"pThrustersMax", 1},
                    {"pThrustersCast", 1},

                    {"thrustersFilterT", 1},
                    {"thrustersFilterK", 1},

                    {"sOutSummatorMax", 1},
                    {"sOutSummatorMin", 1}

            }, {
                    {"name", "March"},

                    {"pJoyUnitCast", 1},
                    {"pSpeedDyn", 1},
                    {"pErrGain", 1},

                    {"posFilterT", 1},
                    {"posFilterK", 1},
                    {"speedFilterT", 1},
                    {"speedFilterK", 1},

                    {"pid_pGain", 1},
                    {"pid_iGain", 1},
                    {"pid_iMax", 1},
                    {"pid_iMin", 1},

                    {"pThrustersMin", 1},
                    {"pThrustersMax", 1},
                    {"pThrustersCast", 1},

                    {"thrustersFilterT", 1},
                    {"thrustersFilterK", 1},

                    {"sOutSummatorMax", 1},
                    {"sOutSummatorMin", 1}
            }, {
                    {"name", "Lag"},

                    {"pJoyUnitCast", 1},
                    {"pSpeedDyn", 1},
                    {"pErrGain", 1},

                    {"posFilterT", 1},
                    {"posFilterK", 1},
                    {"speedFilterT", 1},
                    {"speedFilterK", 1},

                    {"pid_pGain", 1},
                    {"pid_iGain", 1},
                    {"pid_iMax", 1},
                    {"pid_iMin", 1},

                    {"pThrustersMin", 1},
                    {"pThrustersMax", 1},
                    {"pThrustersCast", 1},

                    {"thrustersFilterT", 1},
                    {"thrustersFilterK", 1},

                    {"sOutSummatorMax", 1},
                    {"sOutSummatorMin", 1}
            }, {
                    {"name", "Yaw"},

                    {"pJoyUnitCast", 1},
                    {"pSpeedDyn", 1},
                    {"pErrGain", 1},

                    {"posFilterT", 1},
                    {"posFilterK", 1},
                    {"speedFilterT", 1},
                    {"speedFilterK", 1},

                    {"pid_pGain", 1},
                    {"pid_iGain", 1},
                    {"pid_iMax", 1},
                    {"pid_iMin", 1},

                    {"pThrustersMin", 1},
                    {"pThrustersMax", 1},
                    {"pThrustersCast", 1},

                    {"thrustersFilterT", 1},
                    {"thrustersFilterK", 1},

                    {"sOutSummatorMax", 1},
                    {"sOutSummatorMin", 1}
            }, {
                    {"name", "Roll"},

                    {"pJoyUnitCast", 1},
                    {"pSpeedDyn", 1},
                    {"pErrGain", 1},

                    {"posFilterT", 1},
                    {"posFilterK", 1},
                    {"speedFilterT", 1},
                    {"speedFilterK", 1},

                    {"pid_pGain", 1},
                    {"pid_iGain", 1},
                    {"pid_iMax", 1},
                    {"pid_iMin", 1},

                    {"pThrustersMin", 1},
                    {"pThrustersMax", 1},
                    {"pThrustersCast", 1},

                    {"thrustersFilterT", 1},
                    {"thrustersFilterK", 1},

                    {"sOutSummatorMax", 1},
                    {"sOutSummatorMin", 1}
            }, {
                    {"name", "Pitch"},

                    {"pJoyUnitCast", 1},
                    {"pSpeedDyn", 1},
                    {"pErrGain", 1},

                    {"posFilterT", 1},
                    {"posFilterK", 1},
                    {"speedFilterT", 1},
                    {"speedFilterK", 1},

                    {"pid_pGain", 1},
                    {"pid_iGain", 1},
                    {"pid_iMax", 1},
                    {"pid_iMin", 1},

                    {"pThrustersMin", 1},
                    {"pThrustersMax", 1},
                    {"pThrustersCast", 1},

                    {"thrustersFilterT", 1},
                    {"thrustersFilterK", 1},

                    {"sOutSummatorMax", 1},
                    {"sOutSummatorMin", 1}
            },
    }}};
    o << std::setw(4) << j << std::endl;
    o.close();
}

void StabilizationWindow::updateVariables_KX()
{
    // Secure updating UVState structure
    UV_ControlContour data = interface.getControlContourData(currentContour);

    X[0][0] = static_cast<double>(data.state.inputSignal);
    X[1][0] = static_cast<double>(data.state.speedSignal);
    X[2][0] = static_cast<double>(data.state.posSignal);

    //X[3][0] = static_cast<double>(data.state.oldSpeed);
    //X[4][0] = static_cast<double>(data.state.oldPos);

    X[5][0] = static_cast<double>(data.state.joyUnitCasted);
    X[6][0] = static_cast<double>(data.state.joy_iValue);
    X[7][0] = static_cast<double>(data.state.posError);
    X[8][0] = static_cast<double>(data.state.speedError);
    X[9][0] = static_cast<double>(data.state.dynSummator);
    X[10][0] = static_cast<double>(data.state.pidValue);
    X[11][0] = static_cast<double>(data.state.posErrorAmp);
    X[12][0] = static_cast<double>(data.state.speedFiltered);
    X[13][0] = static_cast<double>(data.state.posFiltered);

    X[14][0] = static_cast<double>(data.state.pid_iValue);
    //X[15][0] = static_cast<double>(server->imu_raw_yaw);

    X[16][0] = static_cast<double>(data.state.thrustersFiltered);
    X[17][0] = static_cast<double>(data.state.outputSignal);
}