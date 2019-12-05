#ifndef CREATEVEHICLEWIZARD_H
#define CREATEVEHICLEWIZARD_H

#include "ui_createvehiclewizard.h"
#include <QStateMachine>
#include <QFinalState>
#include <QCloseEvent>

class CreateVehicleWizard : public QWidget, private Ui::CreateVehicleWizard
{
    Q_OBJECT

signals:
    void nextPressed();
    void backPressed();
    void finishPressed();

public:
    explicit CreateVehicleWizard(QWidget *parent = nullptr);
    void startStateMachine();

protected:
    void closeEvent(QCloseEvent *event);

private:
    QString settingsFile;
    QStateMachine stateMachine;
    QState *idle, *setName, *setParameters;
    QFinalState *finish;

private slots:
    void finishWizard();
};

#endif // CREATEVEHICLEWIZARD_H
