#include "StabilizationWindow.h"
#include "ui_StabilizationWindow.h"

StabilizationWindow::StabilizationWindow(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::StabilizationWindow) {
    ui->setupUi(this);

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
    ControlContour = new UV_ControlContour[controlContour_amount];
    interface.setControlContourAmount(controlContour_amount);
    for (int i = 0; i < controlContour_amount; ++i) {
        setUV_ControlContour(i, allStabilizationJson["stabilizationСontour"][i]);
        interface.setControlContourData(i, ControlContour[i]);
    }
    emit ContourChanged();
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
    ui->doubleSpinBox_CS_pJoyUnitCast->setValue(ControlContour[currentContour].constant.pJoyUnitCast);
    ui->doubleSpinBox_CS_pSpeedDyn->setValue(ControlContour[currentContour].constant.pSpeedDyn);
    ui->doubleSpinBox_CS_pErrGain->setValue(ControlContour[currentContour].constant.pErrGain);

    ui->doubleSpinBox_CS_posFilterT->setValue(ControlContour[currentContour].constant.posFilterT);
    ui->doubleSpinBox_CS_posFilterK->setValue(ControlContour[currentContour].constant.posFilterK);
    ui->doubleSpinBox_CS_speedFilterT->setValue(ControlContour[currentContour].constant.speedFilterT);
    ui->doubleSpinBox_CS_speedFilterK->setValue(ControlContour[currentContour].constant.speedFilterK);

    ui->doubleSpinBox_CS_pid_pGain->setValue(ControlContour[currentContour].constant.pid_pGain);
    ui->doubleSpinBox_CS_pid_iGain->setValue(ControlContour[currentContour].constant.pid_iGain);
    ui->doubleSpinBox_CS_pid_iMax->setValue(ControlContour[currentContour].constant.pid_iMax);
    ui->doubleSpinBox_CS_pid_iMin->setValue(ControlContour[currentContour].constant.pid_iMin);

    ui->doubleSpinBox_CS_pThrustersMin->setValue(ControlContour[currentContour].constant.pThrustersMin);
    ui->doubleSpinBox_CS_pThrustersMax->setValue(ControlContour[currentContour].constant.pThrustersMax);
    ui->doubleSpinBox_CS_pThrustersCast->setValue(ControlContour[currentContour].constant.pThrustersCast);

}

void StabilizationWindow::ContourEdited() {
    // TODO:нужно что-то сделать с огромным количеством кода
    ControlContour[currentContour].constant.pJoyUnitCast = ui->doubleSpinBox_CS_pJoyUnitCast->value();
    ControlContour[currentContour].constant.pSpeedDyn = ui->doubleSpinBox_CS_pSpeedDyn->value();
    ControlContour[currentContour].constant.pErrGain = ui->doubleSpinBox_CS_pErrGain->value();

    ControlContour[currentContour].constant.posFilterT = ui->doubleSpinBox_CS_posFilterT->value();
    ControlContour[currentContour].constant.posFilterK = ui->doubleSpinBox_CS_posFilterK->value();
    ControlContour[currentContour].constant.speedFilterT = ui->doubleSpinBox_CS_speedFilterT->value();
    ControlContour[currentContour].constant.speedFilterK = ui->doubleSpinBox_CS_speedFilterK->value();

    ControlContour[currentContour].constant.pid_pGain = ui->doubleSpinBox_CS_pid_pGain->value();
    ControlContour[currentContour].constant.pid_iGain = ui->doubleSpinBox_CS_pid_iGain->value();
    ControlContour[currentContour].constant.pid_iMax = ui->doubleSpinBox_CS_pid_iMax->value();
    ControlContour[currentContour].constant.pid_iMin = ui->doubleSpinBox_CS_pid_iMin->value();

    ControlContour[currentContour].constant.pThrustersMin = ui->doubleSpinBox_CS_pThrustersMin->value();
    ControlContour[currentContour].constant.pThrustersMax = ui->doubleSpinBox_CS_pThrustersMax->value();
    ControlContour[currentContour].constant.pThrustersCast = ui->doubleSpinBox_CS_pThrustersCast->value();

    interface.setControlContourData(currentContour, ControlContour[currentContour]);
}

StabilizationWindow::~StabilizationWindow() {
    delete[] ControlContour;
    delete ui;
}

void StabilizationWindow::saveToJsonFile() {
    for (int i = 0; i < controlContour_amount; ++i) {
        allStabilizationJson["stabilizationСontour"][i]["pJoyUnitCast"] = ControlContour[i].constant.pJoyUnitCast;
        allStabilizationJson["stabilizationСontour"][i]["pSpeedDyn"] = ControlContour[i].constant.pSpeedDyn;
        allStabilizationJson["stabilizationСontour"][i]["pErrGain"] = ControlContour[i].constant.pErrGain;
        allStabilizationJson["stabilizationСontour"][i]["posFilterT"] = ControlContour[i].constant.posFilterT;
        allStabilizationJson["stabilizationСontour"][i]["posFilterK"] = ControlContour[i].constant.posFilterK;
        allStabilizationJson["stabilizationСontour"][i]["speedFilterT"] = ControlContour[i].constant.speedFilterT;
        allStabilizationJson["stabilizationСontour"][i]["speedFilterK"] = ControlContour[i].constant.speedFilterK;
        allStabilizationJson["stabilizationСontour"][i]["pid_pGain"] = ControlContour[i].constant.pid_pGain;
        allStabilizationJson["stabilizationСontour"][i]["pid_iGain"] = ControlContour[i].constant.pid_iGain;
        allStabilizationJson["stabilizationСontour"][i]["pid_iMax"] = ControlContour[i].constant.pid_iMax;
        allStabilizationJson["stabilizationСontour"][i]["pid_iMin"] = ControlContour[i].constant.pid_iMin;
        allStabilizationJson["stabilizationСontour"][i]["pThrustersMin"] = ControlContour[i].constant.pThrustersMin;
        allStabilizationJson["stabilizationСontour"][i]["pThrustersMax"] = ControlContour[i].constant.pThrustersMax;
        allStabilizationJson["stabilizationСontour"][i]["pThrustersCast"] = ControlContour[i].constant.pThrustersCast;
    };
    std::ofstream o(jsonName.toStdString());
    o << std::setw(4) << allStabilizationJson << std::endl;
    o.close();
}

void StabilizationWindow::setUV_ControlContour(int number, json StabilizationJson) {
    // TODO:нужно что-то сделать с огромным количеством кода
    ControlContour[number].constant.pJoyUnitCast = StabilizationJson["pJoyUnitCast"];
    ControlContour[number].constant.pSpeedDyn = StabilizationJson["pSpeedDyn"];
    ControlContour[number].constant.pErrGain = StabilizationJson["pErrGain"];

    ControlContour[number].constant.posFilterT = StabilizationJson["posFilterT"];
    ControlContour[number].constant.posFilterK = StabilizationJson["posFilterK"];
    ControlContour[number].constant.speedFilterT = StabilizationJson["speedFilterT"];
    ControlContour[number].constant.speedFilterK = StabilizationJson["speedFilterK"];

    ControlContour[number].constant.pid_pGain = StabilizationJson["pid_pGain"];
    ControlContour[number].constant.pid_iGain = StabilizationJson["pid_iGain"];
    ControlContour[number].constant.pid_iMax = StabilizationJson["pid_iMax"];
    ControlContour[number].constant.pid_iMin = StabilizationJson["pid_iMin"];

    ControlContour[number].constant.pThrustersMin = StabilizationJson["pThrustersMin"];
    ControlContour[number].constant.pThrustersMax = StabilizationJson["pThrustersMax"];
    ControlContour[number].constant.pThrustersCast = StabilizationJson["pThrustersCast"];

    ControlContour[number].constant.thrustersFilterT = StabilizationJson["thrustersFilterT"];
    ControlContour[number].constant.thrustersFilterK = StabilizationJson["thrustersFilterK"];

    ControlContour[number].constant.sOutSummatorMax = StabilizationJson["sOutSummatorMax"];
    ControlContour[number].constant.sOutSummatorMin = StabilizationJson["sOutSummatorMin"];
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