#ifndef GITWIDGET_H
#define GITWIDGET_H

#include "gitwidget_global.h"

#include <QDialog>

class GitProcess;
namespace Ui {
class GitWidget;
}

class GITWIDGET_EXPORT GitWidget : public QDialog
{
    Q_OBJECT

public:
    explicit GitWidget(QWidget *parent = nullptr,QString repository="",QString directory="");
    ~GitWidget();
   // void set_data(QString repository,QString directory);
public slots:
    void activateGit();
    void deactivateGit();
    void addLog(QString log);
    void setList(QStringList list);
    void gitCommit();
signals:
    void gitActivate();
private:

    Ui::GitWidget *ui;
    GitProcess* m_process;
};

#endif // GITWIDGET_H
