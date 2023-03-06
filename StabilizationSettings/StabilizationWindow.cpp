#include "StabilizationWindow.h"
#include "ui_StabilizationWindow.h"

// double X[2000][2];

StabilizationWindow::StabilizationWindow(QWidget* parent):
    QWidget(parent), ui(new Ui::StabilizationWindow) {
    ui->setupUi(this);
    jsonName = "stabilizationJson.json";

    if (std::filesystem::exists(jsonName.toStdString())) {
        getJsonFromFile();
        qDebug() << jsonName << " открыт имеющийся";
    } else {
        createDefaultStabilizationJson();
        qDebug() << "createDefaultStabilizationJson done";
        saveToFile();
        qDebug() << jsonName << " создан новый";
    }
    getConstantsFromJson();

    connect(ui->pushButton_CS_saveConfig, SIGNAL(clicked()), this, SLOT(saveConfigClicked()));

    connect(ui->doubleSpinBox_CS_pJoyUnitCast, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_pSpeedDyn, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_pErrGain, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));

    connect(ui->doubleSpinBox_CS_posFilterT, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_posFilterK, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_speedFilterT, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_speedFilterK, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));

    connect(ui->doubleSpinBox_CS_pid_pGain, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_pid_iGain, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_pid_iMax, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_pid_iMin, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));

    connect(ui->doubleSpinBox_CS_pThrustersMin, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_pThrustersMax, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));
    connect(ui->doubleSpinBox_CS_pThrustersCast, SIGNAL(editingFinished()), this, SLOT(ContourEdited()));

    connect(ui->radioButton_CS_YawSelect, SIGNAL(clicked()), this, SLOT(ContourChangedYaw()));
    connect(ui->radioButton_CS_RollSelect, SIGNAL(clicked()), this, SLOT(ContourChangedRoll()));
    connect(ui->radioButton_CS_PitchSelect, SIGNAL(clicked()), this, SLOT(ContourChangedPitch()));
    connect(ui->radioButton_CS_DepthSelect, SIGNAL(clicked()), this, SLOT(ContourChangedDepth()));
    connect(ui->radioButton_CS_MarchSelect, SIGNAL(clicked()), this, SLOT(ContourChangedMarch()));
    connect(ui->radioButton_CS_LagSelect, SIGNAL(clicked()), this, SLOT(ContourChangedLag()));

    // X_Protocol = new x_protocol("protocols.conf", "xi", X);

    emit ui->radioButton_CS_YawSelect->setChecked(true);
    emit ContourChangedYaw();

    FillUiConstants();
    FillUiStates();
}

void StabilizationWindow::ContourChangedYaw() {
    currentContour = CONTOUR_YAW;
    interface.setCurrentControlContour(CONTOUR_YAW);
    FillUiConstants();
}

void StabilizationWindow::ContourChangedRoll() {
    currentContour = CONTOUR_ROLL;
    interface.setCurrentControlContour(CONTOUR_ROLL);
    FillUiConstants();
}

void StabilizationWindow::ContourChangedPitch() {
    currentContour = CONTOUR_PITCH;
    interface.setCurrentControlContour(CONTOUR_PITCH);
    FillUiConstants();
}

void StabilizationWindow::ContourChangedDepth() {
    currentContour = CONTOUR_DEPTH;
    interface.setCurrentControlContour(CONTOUR_DEPTH);
    FillUiConstants();
}

void StabilizationWindow::ContourChangedMarch() {
    currentContour = CONTOUR_MARCH;
    interface.setCurrentControlContour(CONTOUR_MARCH);
    FillUiConstants();
}

void StabilizationWindow::ContourChangedLag() {
    currentContour = CONTOUR_LAG;
    interface.setCurrentControlContour(CONTOUR_LAG);
    FillUiConstants();
}

void StabilizationWindow::ContourEdited() {
    ConstantsControlContour[currentContour].pJoyUnitCast = float(ui->doubleSpinBox_CS_pJoyUnitCast->value());
    ConstantsControlContour[currentContour].pSpeedDyn = float(ui->doubleSpinBox_CS_pSpeedDyn->value());
    ConstantsControlContour[currentContour].pErrGain = float(ui->doubleSpinBox_CS_pErrGain->value());

    ConstantsControlContour[currentContour].posFilterT = float(ui->doubleSpinBox_CS_posFilterT->value());
    ConstantsControlContour[currentContour].posFilterK = float(ui->doubleSpinBox_CS_posFilterK->value());
    ConstantsControlContour[currentContour].speedFilterT = float(ui->doubleSpinBox_CS_speedFilterT->value());
    ConstantsControlContour[currentContour].speedFilterK = float(ui->doubleSpinBox_CS_speedFilterK->value());

    ConstantsControlContour[currentContour].pid_pGain = float(ui->doubleSpinBox_CS_pid_pGain->value());
    ConstantsControlContour[currentContour].pid_iGain = float(ui->doubleSpinBox_CS_pid_iGain->value());
    ConstantsControlContour[currentContour].pid_iMax = float(ui->doubleSpinBox_CS_pid_iMax->value());
    ConstantsControlContour[currentContour].pid_iMin = float(ui->doubleSpinBox_CS_pid_iMin->value());

    ConstantsControlContour[currentContour].pThrustersMin = float(ui->doubleSpinBox_CS_pThrustersMin->value());
    ConstantsControlContour[currentContour].pThrustersMax = float(ui->doubleSpinBox_CS_pThrustersMax->value());
    ConstantsControlContour[currentContour].pThrustersCast = float(ui->doubleSpinBox_CS_pThrustersCast->value());

    interface.setControlContourConstants(ConstantsControlContour[currentContour]);
}

void StabilizationWindow::saveConfigClicked() {
    getJsonFromConstants();
    saveToFile();
}

void StabilizationWindow::FillUiConstants() {
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
    qDebug() << "pThrustersCast" << ConstantsControlContour[currentContour].pThrustersCast;
}

void StabilizationWindow::FillUiStates() {
    StateControlContour[currentContour] = interface.getControlContourState(currentContour);

    ui->lineEdit_CS_inputSignal->setText(QString::number(StateControlContour[currentContour].inputSignal));
    ui->lineEdit_CS_speedSignal->setText(QString::number(StateControlContour[currentContour].speedSignal));
    ui->lineEdit_CS_posSignal->setText(QString::number(StateControlContour[currentContour].posSignal));

    ui->lineEdit_CS_joyUnitCasted->setText(QString::number(StateControlContour[currentContour].joyUnitCasted));
    ui->lineEdit_CS_posError->setText(QString::number(StateControlContour[currentContour].posError));
    ui->lineEdit_CS_joy_iValue->setText(QString::number(StateControlContour[currentContour].joy_iValue));
    ui->lineEdit_CS_pid_iValue->setText(QString::number(StateControlContour[currentContour].pid_iValue));
    ui->lineEdit_CS_speedError->setText(QString::number(StateControlContour[currentContour].speedError));
    ui->lineEdit_CS_dynSummator->setText(QString::number(StateControlContour[currentContour].dynSummator));
    ui->lineEdit_CS_pidValue->setText(QString::number(StateControlContour[currentContour].pidValue));
    ui->lineEdit_CS_posFiltered->setText(QString::number(StateControlContour[currentContour].posFiltered));
    ui->lineEdit_CS_speedFiltered->setText(QString::number(StateControlContour[currentContour].speedFiltered));
    // updateVariables_KX();
}

void StabilizationWindow::getJsonFromFile() {
    std::ifstream file(jsonName.toStdString());
    allStabilizationJson = json::parse(file);
    file.close();
}

void StabilizationWindow::getJsonFromConstants() {
    for (int i = CONTOUR_DEPTH; i < CONTOUR_PITCH + 1; i++) {
        allStabilizationJson[std::to_string(i) + "_pJoyUnitCast"] = ConstantsControlContour[i].pJoyUnitCast;
        allStabilizationJson[std::to_string(i) + "_pSpeedDyn"] = ConstantsControlContour[i].pSpeedDyn;
        allStabilizationJson[std::to_string(i) + "_pErrGain"] = ConstantsControlContour[i].pErrGain;

        allStabilizationJson[std::to_string(i) + "_posFilterT"] = ConstantsControlContour[i].posFilterT;
        allStabilizationJson[std::to_string(i) + "_posFilterK"] = ConstantsControlContour[i].posFilterK;
        allStabilizationJson[std::to_string(i) + "_speedFilterT"] = ConstantsControlContour[i].speedFilterT;
        allStabilizationJson[std::to_string(i) + "_speedFilterK"] = ConstantsControlContour[i].speedFilterK;

        allStabilizationJson[std::to_string(i) + "_pid_pGain"] = ConstantsControlContour[i].pid_pGain;
        allStabilizationJson[std::to_string(i) + "_pid_iGain"] = ConstantsControlContour[i].pid_iGain;
        allStabilizationJson[std::to_string(i) + "_pid_iMax"] = ConstantsControlContour[i].pid_iMax;
        allStabilizationJson[std::to_string(i) + "_pid_iMin"] = ConstantsControlContour[i].pid_iMin;
        
        allStabilizationJson[std::to_string(i) + "_pThrustersMin"] = ConstantsControlContour[i].pThrustersMin;
        allStabilizationJson[std::to_string(i) + "_pThrustersMax"] = ConstantsControlContour[i].pThrustersMax;
        allStabilizationJson[std::to_string(i) + "_pThrustersCast"] = ConstantsControlContour[i].pThrustersCast;
    };
}

void StabilizationWindow::getConstantsFromJson() {
    for (int i = CONTOUR_DEPTH; i < CONTOUR_PITCH + 1; i++) {
        ConstantsControlContour[i].pJoyUnitCast =   allStabilizationJson[std::to_string(i) + "_pJoyUnitCast"];
        ConstantsControlContour[i].pSpeedDyn =      allStabilizationJson[std::to_string(i) + "_pSpeedDyn"];
        ConstantsControlContour[i].pErrGain =       allStabilizationJson[std::to_string(i) + "_pErrGain"];

        ConstantsControlContour[i].posFilterT =     allStabilizationJson[std::to_string(i) + "_posFilterT"];
        ConstantsControlContour[i].posFilterK =     allStabilizationJson[std::to_string(i) + "_posFilterK"];
        ConstantsControlContour[i].speedFilterT =   allStabilizationJson[std::to_string(i) + "_speedFilterT"];
        ConstantsControlContour[i].speedFilterK =   allStabilizationJson[std::to_string(i) + "_speedFilterK"];

        ConstantsControlContour[i].pid_pGain =      allStabilizationJson[std::to_string(i) + "_pid_pGain"];
        ConstantsControlContour[i].pid_iGain =      allStabilizationJson[std::to_string(i) + "_pid_iGain"];
        ConstantsControlContour[i].pid_iMax =       allStabilizationJson[std::to_string(i) + "_pid_iMax"];
        ConstantsControlContour[i].pid_iMin =       allStabilizationJson[std::to_string(i) + "_pid_iMin"];

        ConstantsControlContour[i].pThrustersMin =  allStabilizationJson[std::to_string(i) + "_pThrustersMin"];
        ConstantsControlContour[i].pThrustersMax =  allStabilizationJson[std::to_string(i) + "_pThrustersMax"];
        ConstantsControlContour[i].pThrustersCast = allStabilizationJson[std::to_string(i) + "_pThrustersCast"];
        interface.setControlContourConstants(ConstantsControlContour[i], static_cast<e_Countour>(i));
    };
}

void StabilizationWindow::createDefaultStabilizationJson() {
    for (int i = CONTOUR_DEPTH; i < CONTOUR_PITCH + 1; i++) {
        allStabilizationJson[std::to_string(i) + "_pJoyUnitCast"] = 1;
        allStabilizationJson[std::to_string(i) + "_pSpeedDyn"] = 1;
        allStabilizationJson[std::to_string(i) + "_pErrGain"] = 1;

        allStabilizationJson[std::to_string(i) + "_posFilterT"] = 1;
        allStabilizationJson[std::to_string(i) + "_posFilterK"] = 1;
        allStabilizationJson[std::to_string(i) + "_speedFilterT"] = 1;
        allStabilizationJson[std::to_string(i) + "_speedFilterK"] = 1;

        allStabilizationJson[std::to_string(i) + "_pid_pGain"] = 1;
        allStabilizationJson[std::to_string(i) + "_pid_iGain"] = 1;
        allStabilizationJson[std::to_string(i) + "_pid_iMax"] = 1;
        allStabilizationJson[std::to_string(i) + "_pid_iMin"] = 1;

        allStabilizationJson[std::to_string(i) + "_pThrustersMin"] = 1;
        allStabilizationJson[std::to_string(i) + "_pThrustersMax"] = 1;
        allStabilizationJson[std::to_string(i) + "_pThrustersCast"] = 1;
        // qDebug() << allStabilizationJson[std::to_string(i) + "pJoyUnitCast"].get<int>();

    }

}

void StabilizationWindow::saveToFile() {
    qDebug() << "saveToFile()";
    std::ofstream o(jsonName.toStdString());
    o << std::setw(4) << allStabilizationJson << std::endl;
    o.close();
}

// void StabilizationWindow::updateVariables_KX() {
//     // Secure updating UVState structure
//     UV_ControlContour data = interface.getControlContourData(currentContour);

//     X[0][0] = static_cast<double>(data.state.inputSignal);
//     X[1][0] = static_cast<double>(data.state.speedSignal);
//     X[2][0] = static_cast<double>(data.state.posSignal);

//     //X[3][0] = static_cast<double>(data.state.oldSpeed);
//     //X[4][0] = static_cast<double>(data.state.oldPos);

//     X[5][0] = static_cast<double>(data.state.joyUnitCasted);
//     X[6][0] = static_cast<double>(data.state.joy_iValue);
//     X[7][0] = static_cast<double>(data.state.posError);
//     X[8][0] = static_cast<double>(data.state.speedError);
//     X[9][0] = static_cast<double>(data.state.dynSummator);
//     X[10][0] = static_cast<double>(data.state.pidValue);
//     X[11][0] = static_cast<double>(data.state.posErrorAmp);
//     X[12][0] = static_cast<double>(data.state.speedFiltered);
//     X[13][0] = static_cast<double>(data.state.posFiltered);

//     X[14][0] = static_cast<double>(data.state.pid_iValue);
//     //X[15][0] = static_cast<double>(server->imu_raw_yaw);

//     X[16][0] = static_cast<double>(data.state.thrustersFiltered);
//     X[17][0] = static_cast<double>(data.state.outputSignal);
// }
