#ifndef GITPROCESS_H
#define GITPROCESS_H

#include <QObject>
#include <QProcess>

class GitProcess: public QObject
{
    Q_OBJECT
public:
    GitProcess();
    void set_project_directory(QString directory);
    void set_repository(QString repository);
    void commandGitCommit(QString commit);
private slots:
    void result(int exitCode);
    void commandGitInit();
    void commandGitAdd();
    void commandGitPush();
    void commandGitStatus();
signals:
    void gitEnabled();
    void gitNotEnabled();
    void gitResult(QString);
    void gitListFiles(QStringList);
private:
    void resultGit(int exitCode);
    void commandCheckGit();
    void resultGitStatus(int exitCode);
    void resultCheckGit(int exitCode);
    enum typeCommand
    {
        check,
        gitInit,
        gitAdd,
        gitCommit,
        gitPush,
        gitStatus
    };
    typeCommand executingCommand;
    QString m_projectDirectory,m_repository,m_command;
    QProcess *m_process;
};

#endif // GITPROCESS_H
