#include "setconfiguration.h"
#include "ui_setconfiguration.h"
#include <QProcess>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QPushButton>

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
    delete vbox_ThrusterSet;
    delete vbox_VehicleSetting;
    delete vbox_Devices;
    delete message;
    delete ui;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void setConfiguration::on_pushButton_ThrusterSet_commit_clicked()
{
    if(!file_flag) //работа кнопки только в случае настройки гит клиента
    {
        configGitBush();
        if(fileName != "git-bash.exe")
            return;
    }

    if(message == nullptr)
    {
        message = new DialogCommit;
        message->show();
    }
    else
    {
        delete message;
        message = new DialogCommit;
        message->show();
    }



}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void setConfiguration::on_pushButton_VehicleSetting_commit_clicked()
{
    if(!file_flag) //работа кнопки только в случае настройки гит клиента
    {
        configGitBush();
        if(fileName != "git-bash.exe")
            return;
    }

    if(message == nullptr)
    {
        message = new DialogCommit;
        message->show();
    }
    else
    {
        delete message;
        message = new DialogCommit;
        message->show();
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void setConfiguration::on_pushButton_devices_commit_clicked()
{
    if(!file_flag) //работа кнопки только в случае настройки гит клиента
    {
        configGitBush();
        if(fileName != "git-bash.exe")
            return;
    }

    if(message == nullptr)
    {
        message = new DialogCommit;
        message->show();
    }
    else
    {
        delete message;
        message = new DialogCommit;
        message->show();
    }

}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void setConfiguration::on_pushButton_pull_clicked()
{
    if(!file_flag) //работа кнопки только в случае настройки гит клиента
    {
        configGitBush();
    }

    QProcess* process1 = new QProcess(this);
    process1->start(filePath, {"-c", "cd " + dirConfig_Path + "\n" + "git pull"});
    process1->waitForFinished();

    //обновление данных в связи с изменением локального репозитория
    //---------------------------------------------------------------
    QDir dir;
    dir.setPath(dirConfig_Path);
    dir.setFilter(QDir::AllDirs | QDir::NoDot | QDir::NoDotAndDotDot);
    QFileInfoList filesList = dir.entryInfoList();

    for(short i = 0; i < (int)filesList.size(); i++)
    {
        setElement_GroupBox(filesList[i]);
    }
    //---------------------------------------------------------------

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
        fileName = fi.fileName();
        filePath = fi.filePath();

        if(fileName == "git-bash.exe")
        {

            file_flag = true;

            QDir dir;
            int _dirExists = dir.exists( "SettingsWindow/Config" );

            if( !_dirExists ) // if not, create it
                dir.mkpath( "SettingsWindow/Config" );
            dir.setPath("SettingsWindow/Config");
            dirConfig_Path = dir.absolutePath();

            QProcess* process = new QProcess(this);
            process->start(filePath, {"-c", "git clone https://github.com/hidronautics/PoolsideGUI_config.git " + dirConfig_Path});

            dir.setFilter(QDir::AllDirs | QDir::NoDot | QDir::NoDotAndDotDot);
            QFileInfoList filesList = dir.entryInfoList();

            for(short i = 0; i < (int)filesList.size(); i++)
            {
                setElement_GroupBox(filesList[i]);
            }

        }
        else
            QMessageBox::information(this, "Error","Select git-bash.exe file");
    }
    else QMessageBox::information(this, "Error","Select second .exe file");
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void setConfiguration::setElement_GroupBox(QFileInfo file)
{
    QString file_path = dirConfig_Path + "/" + file.fileName();

    QDir fileDir(file_path);
    fileDir.setFilter(QDir::Files | QDir::NoDot | QDir::NoDotAndDotDot);
    QFileInfoList filesList = fileDir.entryInfoList();
    QString file_name = file.fileName();

    if(file.fileName() == "ThrusterSet")
    {
        if(vbox_ThrusterSet == nullptr)
        {
            vbox_ThrusterSet = new QVBoxLayout;
        }
        else
        {
            delete vbox_ThrusterSet;
            vbox_ThrusterSet = new QVBoxLayout;
            qDeleteAll(ui->groupBox_ThrusterSet->findChildren<QWidget*>());
            ui->groupBox_ThrusterSet->setLayout(vbox_ThrusterSet);
        }

        for(int i = 0; i < (int)filesList.size(); i++)
        {
            QPushButton* button = new QPushButton();
            button->setText(filesList[i].fileName());
            vbox_ThrusterSet->addWidget(button);
        }
        vbox_ThrusterSet->addStretch(1);
        ui->groupBox_ThrusterSet->setLayout(vbox_ThrusterSet);
    }

    if(file.fileName() == "VehicleSetting")
    {
        if(vbox_VehicleSetting == nullptr)
        {
            vbox_VehicleSetting = new QVBoxLayout;
        }
        else
        {
            delete vbox_VehicleSetting;
            vbox_VehicleSetting = new QVBoxLayout;
            qDeleteAll(ui->groupBox_VehicleSetting->findChildren<QWidget*>());
            ui->groupBox_VehicleSetting->setLayout(vbox_VehicleSetting);
        }

        for(int i = 0; i < (int)filesList.size(); i++)
        {
            QPushButton* button = new QPushButton();
            button->setText(filesList[i].fileName());
            vbox_VehicleSetting->addWidget(button);
        }
        vbox_VehicleSetting->addStretch(1);
        ui->groupBox_VehicleSetting->setLayout(vbox_VehicleSetting);
    }

    if(file.fileName() == "Devices")
    {
        if(vbox_Devices == nullptr)
        {
            vbox_Devices = new QVBoxLayout;
        }
        else
        {
            delete vbox_Devices;
            vbox_Devices = new QVBoxLayout;
            qDeleteAll(ui->groupBox_devices->findChildren<QWidget*>());
            ui->groupBox_devices->setLayout(vbox_Devices);
        }

        for(int i = 0; i < (int)filesList.size(); i++)
        {
            QPushButton* button = new QPushButton();
            button->setText(filesList[i].fileName());
            vbox_Devices->addWidget(button);
        }
        vbox_Devices->addStretch(1);
        ui->groupBox_devices->setLayout(vbox_Devices);
    }

}



