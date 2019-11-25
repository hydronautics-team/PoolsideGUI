#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "SettingsWindow/settingswindow.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    SettingsWindow settingsWindow;

private slots:
    void enableAUVMode();
    void enableROVMode();
    void showPageConfigThruster();
};

#endif // MAINWINDOW_H
