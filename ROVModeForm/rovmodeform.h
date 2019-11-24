#ifndef ROVMODEFORM_H
#define ROVMODEFORM_H

#include "ui_rovmodeform.h"

class ROVModeForm : public QWidget, private Ui::ROVModeForm
{
    Q_OBJECT

public:
    explicit ROVModeForm(QWidget *parent = nullptr);
};

#endif // ROVMODEFORM_H
