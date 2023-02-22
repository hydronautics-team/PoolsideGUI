#ifndef CREATEVEHICLEWIZARD_H
#define CREATEVEHICLEWIZARD_H

#include "ui_vehiclewizard.h"
#include <QStateMachine>
#include <QFinalState>
#include <QCloseEvent>

class VehicleWizard : public QWidget, private Ui::VehicleWizard {
Q_OBJECT

signals:
    void nextPressed();
    void backPressed();
    void finishPressed();
    void updateMainWindow(); //

public:
    explicit VehicleWizard(QWidget *parent = nullptr);
    void startStateMachine();

protected:
    void closeEvent(QCloseEvent *event);

private:
    int thrusters_count;

    QString settingsFile;

    QStateMachine stateMachine;
    QState *idle, *setName, *setParameters;
    QFinalState *finish;

private slots:
    void enableButtonNext();
    void enableButtonFinish();
    void finishWizard();
    void updateThrustersCount();
};

#endif // CREATEVEHICLEWIZARD_H
