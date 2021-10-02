#ifndef DIALOGCOMMIT_H
#define DIALOGCOMMIT_H

#include <QWidget>

namespace Ui {
class DialogCommit;
}

class DialogCommit : public QWidget
{
    Q_OBJECT

public:
    explicit DialogCommit(QWidget *parent = nullptr);
    ~DialogCommit();

    void FilePath_Func(QString);

    QString filePath;

signals:
    void updateUi();

private slots:
    void on_pushButton_commit_Dialog_clicked();

private:
    Ui::DialogCommit *ui;
};

#endif // DIALOGCOMMIT_H
