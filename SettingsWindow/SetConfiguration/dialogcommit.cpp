#include "dialogcommit.h"
#include "ui_dialogcommit.h"
#include <QFile>
#include <QTextStream>
#include <QProcess>

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
void DialogCommit::FilePath_Func(QString fileNameDir_, QString fileNameProg_)
{
    filePathDir = fileNameDir_;
    filePathProg = fileNameProg_;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void DialogCommit::on_pushButton_commit_Dialog_clicked()
{
    // Create a new file
    QFile file(filePathDir + ui->lineEdit_fileCreateName->text());
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << ui->textEdit_descriptionFile->toPlainText();

    QProcess* process1 = new QProcess(this);
    process1->start(filePathProg, {"-c", "cd " + filePathDir + "\n" + "git add " + ui->lineEdit_fileCreateName->text()
                                   + "\n" + "git commit -m" + ui->textEdit_commit->toPlainText()});

    emit updateUi();
    this->close();
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
