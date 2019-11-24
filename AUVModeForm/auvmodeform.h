#ifndef AUVMODEFORM_H
#define AUVMODEFORM_H

#include "ui_auvmodeform.h"

class AUVModeForm : public QWidget, private Ui::AUVModeForm
{
    Q_OBJECT

public:
    explicit AUVModeForm(QWidget *parent = nullptr);
};

#endif // AUVMODEFORM_H
