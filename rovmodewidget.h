#ifndef ROVMODEWIDGET_H
#define ROVMODEWIDGET_H

#include <QSettings>
#include <QList>
#include "ui_rovmodewidget.h"

class ROVModeWidget : public QWidget, private Ui::ROVModeWidget
{
    Q_OBJECT

public:
    explicit ROVModeWidget(QWidget *parent = nullptr);

public slots:
    void updateVehicle();

private:
    QString settingsFile;
    QSettings *settings;
    QString currentVehicle;
    QString currentConfiguration;
    int thrustersCount;
    QList<QProgressBar *> thrusterBarGroup;

    void initializeWindow();

private slots:
    void updateWindow();
};

#endif // ROVMODEWIDGET_H
