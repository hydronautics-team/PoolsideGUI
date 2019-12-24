#ifndef ROVMODEWIDGET_H
#define ROVMODEWIDGET_H

#include "ui_rovmodewidget.h"

class ROVModeWidget : public QWidget, private Ui::ROVModeWidget
{
    Q_OBJECT

public:
    explicit ROVModeWidget(QWidget *parent = nullptr);
};

#endif // ROVMODEWIDGET_H
