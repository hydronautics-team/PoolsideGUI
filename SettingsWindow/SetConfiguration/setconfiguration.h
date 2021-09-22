#ifndef SETCONFIGURATION_H
#define SETCONFIGURATION_H

#include <QWidget>

namespace Ui {
class setConfiguration;
}

class setConfiguration : public QWidget
{
    Q_OBJECT

public:
    explicit setConfiguration(QWidget *parent = nullptr);
    ~setConfiguration();

    void configGitBush(); //функция настройки гит клиента на пк

    bool file_flag = false; //переменная обработка .exe приложения
    QString filePath; //путь к действующему git-bash.exe

private slots:
    void on_pushButton_ThrusterSet_commit_clicked();

    void on_pushButton_VehicleSetting_commit_clicked();

    void on_pushButton_devices_commit_clicked();

    void on_pushButton_pull_clicked();

    void on_pushButton_push_clicked();

    void on_pushButton_Accept_Configurations_clicked();

private:
    Ui::setConfiguration *ui;
};

#endif // SETCONFIGURATION_H
