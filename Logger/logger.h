#ifndef LOGGER_H
#define LOGGER_H

#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QScopedPointer>
#include <QTextStream>
#include <QDateTime>
#include <QLoggingCategory>
#include <QString>

#include "LoggingCategories.h"

void initLogger(QString logfile_way);
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

#endif // LOGGER_H
