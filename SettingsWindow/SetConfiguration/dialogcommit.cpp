#include "dialogcommit.h"
#include "ui_dialogcommit.h"

DialogCommit::DialogCommit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialogCommit)
{
    ui->setupUi(this);
}

DialogCommit::~DialogCommit()
{
    delete ui;
}
