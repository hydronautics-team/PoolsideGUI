#ifndef CREATEVEHICLEWIZARD_H
#define CREATEVEHICLEWIZARD_H

#include "ui_createvehiclewizard.h"
#include <QStateMachine>

class CreateVehicleWizard : public QWidget, private Ui::CreateVehicleWizard
{
    Q_OBJECT

signals:
    void NextPressed();
    void BackPressed();
    void ExitPressed();
    void FinishPressed();

public:
    explicit CreateVehicleWizard(QWidget *parent = nullptr);

private:
    QStateMachine stateMachine;
    QState *idle, *setName, *setParameters, *exit, *finish;
};

#endif // CREATEVEHICLEWIZARD_H
