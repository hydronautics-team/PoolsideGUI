#ifndef OPERATORWINDOW_H
#define OPERATORWINDOW_H

#include "ui_operatorwindow.h"

class OperatorWindow : public QWidget, private Ui::OperatorWindow
{
    Q_OBJECT

public:
    explicit OperatorWindow(QWidget *parent = nullptr);
};

#endif // OPERATORWINDOW_H
