#include "vehiclesettings.h"

double X[2000][2];

VehicleSettings::VehicleSettings(QWidget *parent) :
    QWidget(parent)
{
//    connect(server, &Server::updateCsView, mainWindow,
//            &MainWindow::update_csView);
//    connect(mainWindow, &MainWindow::reset_IMU_btn_clicked,
//            server, &Server::reset_IMU);
//    connect(mainWindow, &MainWindow::stabilize_roll_toggled,
//            server, &Server::set_stabilize_roll);
//    connect(mainWindow, &MainWindow::stabilize_pitch_toggled,
//            server, &Server::set_stabilize_pitch);
//    connect(mainWindow, &MainWindow::stabilize_yaw_toggled,
//            server, &Server::set_stabilize_yaw);
//    connect(mainWindow, &MainWindow::stabilize_depth_toggled,
//            server, &Server::set_stabilize_depth);
    setupUi(this);
    qDebug () << " - VehicleSettings constructor";

    uv_interface = new ITuningData();

    current_contour = 0;

    X_Protocol = new x_protocol("protocols.conf", "xi", X);
}

void VehicleSettings::updateData()
{
    updateLabels();
    updateSpinboxes();
    updateVariables_KX();
}

void VehicleSettings::on_radioButton_CS_MarchSelect_released()
{
    current_contour = CONTOUR_MARCH;
    updateData();
}

void VehicleSettings::on_radioButton_CS_LagSelect_released()
{
    current_contour = CONTOUR_LAG;
    updateData();
}

void VehicleSettings::on_radioButton_CS_YawSelect_released()
{
    current_contour = CONTOUR_YAW;
    updateData();
}

void VehicleSettings::on_radioButton_CS_DepthSelect_released()
{
    current_contour = CONTOUR_DEPTH;
    updateData();
}

void VehicleSettings::on_radioButton_CS_RollSelect_released()
{
    current_contour = CONTOUR_ROLL;
    updateData();
}

void VehicleSettings::on_radioButton_CS_PitchSelect_released()
{
    current_contour = CONTOUR_PITCH;
    updateData();
}

void VehicleSettings::updateLabels()
{
    // Secure updating UVState structure
    UV_ControlContour data = uv_interface->getControlContourData(current_contour);

    lineEdit_CS_inputSignal->setText(QString::number(static_cast<double>(data.state.inputSignal), 'f', 2));
    lineEdit_CS_joyUnitCasted->setText(QString::number(static_cast<double>(data.state.joyUnitCasted), 'f', 2));
    lineEdit_CS_joy_iValue->setText(QString::number(static_cast<double>(data.state.joy_iValue), 'f', 2));
    lineEdit_CS_posError->setText(QString::number(static_cast<double>(data.state.posError), 'f', 2));
    lineEdit_CS_posSignal->setText(QString::number(static_cast<double>(data.state.posSignal), 'f', 2));
    lineEdit_CS_posFiltered->setText(QString::number(static_cast<double>(data.state.posFiltered), 'f', 2));
    lineEdit_CS_pidValue->setText(QString::number(static_cast<double>(data.state.pidValue), 'f', 2));
    lineEdit_CS_dynSummator->setText(QString::number(static_cast<double>(data.state.dynSummator), 'f', 2));
    lineEdit_CS_speedError->setText(QString::number(static_cast<double>(data.state.speedError), 'f', 2));
    lineEdit_CS_speedSignal->setText(QString::number(static_cast<double>(data.state.speedSignal), 'f', 2));
    lineEdit_CS_speedFiltered->setText(QString::number(static_cast<double>(data.state.speedFiltered), 'f', 2));
    lineEdit_CS_pid_iValue->setText(QString::number(static_cast<double>(data.state.pid_iValue), 'f', 2));
    lineEdit_CS_thrustersFiltered->setText(QString::number(static_cast<double>(data.state.thrustersFiltered), 'f', 2));
    lineEdit_CS_outputSignal->setText(QString::number(static_cast<double>(data.state.outputSignal), 'f', 2));
}

void VehicleSettings::updateSpinboxes()
{
    // Secure updating UVState structure
    UV_ControlContour data = uv_interface->getControlContourData(current_contour);

    doubleSpinBox_CS_pJoyUnitCast->setValue(static_cast<double>(data.constant.pJoyUnitCast));
    doubleSpinBox_CS_pSpeedDyn->setValue(static_cast<double>(data.constant.pSpeedDyn));
    doubleSpinBox_CS_pErrGain->setValue(static_cast<double>(data.constant.pid_pGain));
    doubleSpinBox_CS_pid_pGain->setValue(static_cast<double>(data.constant.pid_pGain));
    doubleSpinBox_CS_pid_iGain->setValue(static_cast<double>(data.constant.pid_iGain));
    doubleSpinBox_CS_pid_iMax->setValue(static_cast<double>(data.constant.pid_iMax));
    doubleSpinBox_CS_pid_iMin->setValue(static_cast<double>(data.constant.pid_iMin));
    doubleSpinBox_CS_pThrustersMin->setValue(static_cast<double>(data.constant.pThrustersMin));
    doubleSpinBox_CS_pThrustersMax->setValue(static_cast<double>(data.constant.pThrustersMax));
    doubleSpinBox_CS_sOutputSummatorMin->setValue(static_cast<double>(data.constant.sOutSummatorMin));
    doubleSpinBox_CS_sOutputSummatorMax->setValue(static_cast<double>(data.constant.sOutSummatorMax));

    doubleSpinBox_CS_posFilterK->setValue(static_cast<double>(data.constant.posFilterK));
    doubleSpinBox_CS_posFilterT->setValue(static_cast<double>(data.constant.posFilterT));
    doubleSpinBox_CS_speedFilterK->setValue(static_cast<double>(data.constant.speedFilterK));
    doubleSpinBox_CS_speedFilterT->setValue(static_cast<double>(data.constant.speedFilterT));
    doubleSpinBox_CS_thrustersFilterK->setValue(static_cast<double>(data.constant.thrustersFilterK));
    doubleSpinBox_CS_thrustersFilterT->setValue(static_cast<double>(data.constant.thrustersFilterT));
}

void VehicleSettings::saveSpinboxes()
{
    UV_ControlContour data;

    data.constant.pJoyUnitCast = static_cast<float>(doubleSpinBox_CS_pJoyUnitCast->value());
    data.constant.pSpeedDyn = static_cast<float>(doubleSpinBox_CS_pSpeedDyn->value());
    data.constant.pErrGain = static_cast<float>(doubleSpinBox_CS_pErrGain->value());
    data.constant.pid_pGain = static_cast<float>(doubleSpinBox_CS_pid_pGain->value());
    data.constant.pid_iGain = static_cast<float>(doubleSpinBox_CS_pid_iGain->value());
    data.constant.pid_iMax = static_cast<float>(doubleSpinBox_CS_pid_iMax->value());
    data.constant.pid_iMin = static_cast<float>(doubleSpinBox_CS_pid_iMin->value());
    data.constant.pThrustersMin = static_cast<float>(doubleSpinBox_CS_pThrustersMin->value());
    data.constant.pThrustersMax = static_cast<float>(doubleSpinBox_CS_pThrustersMax->value());
    data.constant.sOutSummatorMin = static_cast<float>(doubleSpinBox_CS_sOutputSummatorMin->value());
    data.constant.sOutSummatorMax = static_cast<float>(doubleSpinBox_CS_sOutputSummatorMax->value());

    data.constant.posFilterK = static_cast<float>(doubleSpinBox_CS_posFilterK->value());
    data.constant.posFilterT = static_cast<float>(doubleSpinBox_CS_posFilterT->value());
    data.constant.speedFilterK = static_cast<float>(doubleSpinBox_CS_speedFilterK->value());
    data.constant.speedFilterT = static_cast<float>(doubleSpinBox_CS_speedFilterT->value());
    data.constant.thrustersFilterK = static_cast<float>(doubleSpinBox_CS_thrustersFilterK->value());
    data.constant.thrustersFilterT = static_cast<float>(doubleSpinBox_CS_thrustersFilterT->value());

    uv_interface->setControlContourData(current_contour, data);
}

void VehicleSettings::updateVariables_KX()
{
    // Secure updating UVState structure
    UV_ControlContour data = uv_interface->getControlContourData(current_contour);

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
