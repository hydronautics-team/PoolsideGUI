#include "StabilizationWindow.h"
#include "ui_StabilizationWindow.h"

StabilizationWindow::StabilizationWindow(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::StabilizationWindow) {
    ui->setupUi(this);

    updateStabilizationState = new QTimer(this);
    connect(updateStabilizationState, SIGNAL(timeout()), this, SLOT(updateStabilizationStateUi()));
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
        file >> allStabilizationJson;
        file.close();
    }
    connect(ui->pushButton_CS_saveConfig, SIGNAL(released()), this, SLOT(saveToJsonFile()));

    // TODO:нужно что-то сделать с огромным количеством кода
    connect(ui->doubleSpinBox_CS_pErrGain, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_pJoyUnitCast, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_pSpeedDyn, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));

    connect(ui->doubleSpinBox_CS_pThrustersCast, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_pThrustersMax, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_pThrustersMin, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));

    connect(ui->doubleSpinBox_CS_pid_iGain, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_pid_iMax, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_pid_iMin, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_pid_pGain, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));

    connect(ui->doubleSpinBox_CS_posFilterK, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_posFilterT, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_speedFilterK, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_speedFilterT, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));

    connect(ui->radioButton_CS_LagSelect, SIGNAL(released()), this, SLOT(ContourChanged()));
    connect(ui->radioButton_CS_RollSelect, SIGNAL(released()), this, SLOT(ContourChanged()));
    connect(ui->radioButton_CS_PitchSelect, SIGNAL(released()), this, SLOT(ContourChanged()));
    connect(ui->radioButton_CS_DepthSelect, SIGNAL(released()), this, SLOT(ContourChanged()));
    connect(ui->radioButton_CS_MarchSelect, SIGNAL(released()), this, SLOT(ContourChanged()));
    connect(ui->radioButton_CS_LagSelect, SIGNAL(released()), this, SLOT(ContourChanged()));

    controlContour_amount = allStabilizationJson["stabilizationСontour"].size();
    ConstantsControlContour = new UV_StabilizationConstants[controlContour_amount];
    StateControlContour = new UV_StabilizationState[controlContour_amount];
    interface.setControlContourAmount(controlContour_amount);
    for (int i = 0; i < controlContour_amount; ++i) {
        setUV_ControlContour(i, allStabilizationJson["stabilizationСontour"][i]);
        interface.setControlContourData(i, ConstantsControlContour[i]);
    }
    emit ContourChanged();
}
void StabilizationWindow::updateStabilizationStateUi() {
    StateControlContour[currentContour] = interface.getControlContourData(static_cast<unsigned int>(currentContour)).state;

    ui->lineEdit_CS_inputSignal->setText(QString::number(StateControlContour[currentContour].inputSignal));
    ui->lineEdit_CS_speedSignal->setText(QString::number(StateControlContour[currentContour].speedSignal));
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

    qDebug() << StateControlContour[currentContour].pid_iValue;
}

void StabilizationWindow::ContourChanged() {
    if (ui->radioButton_CS_YawSelect->isChecked() == true)
        currentContour = YAW;
    if (ui->radioButton_CS_RollSelect->isChecked() == true)
        currentContour = ROLL;
    if (ui->radioButton_CS_PitchSelect->isChecked() == true)
        currentContour = PITCH;
    if (ui->radioButton_CS_DepthSelect->isChecked() == true)
        currentContour = DEPTH;
    if (ui->radioButton_CS_MarchSelect->isChecked() == true)
        currentContour = MARCH;
    if (ui->radioButton_CS_LagSelect->isChecked() == true)
        currentContour = LAG;

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
    ConstantsControlContour[currentContour].pSpeedDyn = ui->doubleSpinBox_CS_pSpeedDyn->value();
    ConstantsControlContour[currentContour].pErrGain = ui->doubleSpinBox_CS_pErrGain->value();

    ConstantsControlContour[currentContour].posFilterT = ui->doubleSpinBox_CS_posFilterT->value();
    ConstantsControlContour[currentContour].posFilterK = ui->doubleSpinBox_CS_posFilterK->value();
    ConstantsControlContour[currentContour].speedFilterT = ui->doubleSpinBox_CS_speedFilterT->value();
    ConstantsControlContour[currentContour].speedFilterK = ui->doubleSpinBox_CS_speedFilterK->value();

    ConstantsControlContour[currentContour].pid_pGain = ui->doubleSpinBox_CS_pid_pGain->value();
    ConstantsControlContour[currentContour].pid_iGain = ui->doubleSpinBox_CS_pid_iGain->value();
    ConstantsControlContour[currentContour].pid_iMax = ui->doubleSpinBox_CS_pid_iMax->value();
    ConstantsControlContour[currentContour].pid_iMin = ui->doubleSpinBox_CS_pid_iMin->value();

    ConstantsControlContour[currentContour].pThrustersMin = ui->doubleSpinBox_CS_pThrustersMin->value();
    ConstantsControlContour[currentContour].pThrustersMax = ui->doubleSpinBox_CS_pThrustersMax->value();
    ConstantsControlContour[currentContour].pThrustersCast = ui->doubleSpinBox_CS_pThrustersCast->value();

    interface.setControlContourData(currentContour, ConstantsControlContour[currentContour]);
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
    ConstantsControlContour[number].pJoyUnitCast = StabilizationJson["pJoyUnitCast"];
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
    ConstantsControlContour[number].pThrustersMax = StabilizationJson["pThrustersMax"];
    ConstantsControlContour[number].pThrustersCast = StabilizationJson["pThrustersCast"];

    ConstantsControlContour[number].thrustersFilterT = StabilizationJson["thrustersFilterT"];
    ConstantsControlContour[number].thrustersFilterK = StabilizationJson["thrustersFilterK"];

    ConstantsControlContour[number].sOutSummatorMax = StabilizationJson["sOutSummatorMax"];
    ConstantsControlContour[number].sOutSummatorMin = StabilizationJson["sOutSummatorMin"];
}


void StabilizationWindow::createDefaultStabilizationJson() {
    std::ofstream o(jsonName.toStdString());
    json j = {{"stabilizationСontour", {
            {
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
            }, {
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
            },
    }}};
    o << std::setw(4) << j << std::endl;
    o.close();
}