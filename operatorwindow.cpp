#include "operatorwindow.h"
#include "ui_operatorwindow.h"

OperatorWindow::OperatorWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OperatorWIndow)
{
    ui->setupUi(this);
}

OperatorWindow::~OperatorWindow()
{
    delete ui;
}

