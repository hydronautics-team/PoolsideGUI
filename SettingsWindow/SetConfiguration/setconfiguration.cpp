#include "setconfiguration.h"
#include "ui_setconfiguration.h"
#include <QProcess>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
setConfiguration::setConfiguration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setConfiguration)
{
    ui->setupUi(this);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
setConfiguration::~setConfiguration()
{
    delete ui;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void setConfiguration::on_pushButton_ThrusterSet_commit_clicked()
{
    if(!file_flag) //работа кнопки только в случае настройки гит клиента
    {
        configGitBush();
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void setConfiguration::on_pushButton_VehicleSetting_commit_clicked()
{
    if(!file_flag) //работа кнопки только в случае настройки гит клиента
    {
        configGitBush();
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void setConfiguration::on_pushButton_devices_commit_clicked()
{
    if(!file_flag) //работа кнопки только в случае настройки гит клиента
    {
        configGitBush();
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void setConfiguration::on_pushButton_pull_clicked()
{
    if(!file_flag) //работа кнопки только в случае настройки гит клиента
    {
        configGitBush();
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void setConfiguration::on_pushButton_push_clicked()
{
    if(!file_flag) //работа кнопки только в случае настройки гит клиента
    {
        configGitBush();
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void setConfiguration::on_pushButton_Accept_Configurations_clicked()
{
    if(!file_flag) //работа кнопки только в случае настройки гит клиента
    {
        configGitBush();
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void setConfiguration::configGitBush()
{
    QString file = QFileDialog::getOpenFileName(this,tr("Open exe file"),"", tr("Exe Files (*.exe)"));

    if(file != 0)
    {
        QFileInfo fi(file);
        QString fileName = fi.fileName();
        filePath = fi.filePath();

        if(fileName == "git-bash.exe")
        {
            QProcess* process = new QProcess(this);
            process->start(filePath, {"-c", "'ls'"});
            process->waitForFinished();
            file_flag = true;
        }
        else
            QMessageBox::information(this, "Error","Select git-bash.exe file");

    }
    else QMessageBox::information(this, "Error","Select second .exe file");
}
