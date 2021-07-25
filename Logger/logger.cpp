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

QScopedPointer<QFile>   m_logFile;

//void initLogger(QString logfile_way);
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);



void initLogger(QString logfile_way)
{
    QString full_way = logfile_way + "/" + "logFile_" + QDateTime::currentDateTime().toString("yyyy-MM-dd__hh-mm-ss") + ".txt";
    qDebug()<<full_way;

    m_logFile.reset(new QFile(full_way));
    // Открываем файл логирования
    qDebug()<<full_way;
    m_logFile.data()->open(QFile::Append | QFile::Text);
    // Устанавливаем обработчик
    qDebug()<<full_way;
    qInstallMessageHandler(messageHandler);
    qDebug()<<full_way;

}

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // Открываем поток записи в файл
    QTextStream out(m_logFile.data());
    // Записываем дату записи
    out << QTime::currentTime().toString("hh:mm:ss.zzz ");
    // По типу определяем, к какому уровню относится сообщение
    switch (type)
    {
    case QtInfoMsg:     out << "INF :"; break;
    case QtDebugMsg:    out << "DBG :"; break;
    case QtWarningMsg:  out << "WRN :"; break;
    case QtCriticalMsg: out << "CRT :"; break;
    case QtFatalMsg:    out << "FTL :"; break;
    }
    // Записываем в вывод категорию сообщения и само сообщение
    out << msg << endl;
    out.flush();    // Очищаем буферизированные данные
}
