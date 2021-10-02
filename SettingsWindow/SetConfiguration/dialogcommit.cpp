#include "dialogcommit.h"
#include "ui_dialogcommit.h"
#include <QFile>
#include <QTextStream>

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
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void DialogCommit::FilePath_Func(QString fileName_)
{
    filePath = fileName_;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void DialogCommit::on_pushButton_commit_Dialog_clicked()
{
    // Create a new file
    QFile file(filePath + ui->lineEdit_fileCreateName->text());
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << ui->textEdit_descriptionFile->toPlainText();

    emit updateUi();
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
