#include "gitprocess.h"
#include <QMessageBox>

GitProcess::GitProcess()
{
    m_process=new QProcess(this);
    connect(m_process,SIGNAL(finished(int)),this,SLOT(result(int)));
    if(QSysInfo::productType()=="windows")
       m_command = "cmd /C git";
    commandCheckGit();
}

void GitProcess::set_repository(QString repository)
{
    m_repository=repository;
}
void GitProcess::commandCheckGit()
{
    executingCommand=check;
    m_process->start(m_command+" --version");
}

void GitProcess::commandGitInit()
{
    executingCommand=gitInit;
    m_process->start(m_command+" init "+m_projectDirectory);
}
void GitProcess::commandGitAdd()
{
    executingCommand=gitAdd;
    m_process->start(m_command+" -C "+m_projectDirectory+" add *.*");
}

void GitProcess::commandGitCommit(QString commit)
{
    executingCommand=gitCommit;
    m_process->start(m_command+" -C "+m_projectDirectory+" commit -m '"+commit+"'");
}

void GitProcess::commandGitPush()
{
    emit gitResult("Push is run. Please wait...");
    executingCommand=gitPush;
    m_process->start(m_command+" -C "+m_projectDirectory+" push "+m_repository+" master");
}
void GitProcess::commandGitStatus()
{
    executingCommand=gitStatus;
    m_process->start(m_command+" -C "+m_projectDirectory+" status --u");
}
void GitProcess::result(int exitCode)
{
    switch (executingCommand)
    {
        case check:
        {
            resultCheckGit(exitCode);
            break;
        }
        case gitStatus:
        {
            resultGitStatus(exitCode);
            break;
        }
        default:
        {
            resultGit(exitCode);
            break;
        }
    }

}
void GitProcess::resultGit(int exitCode)
{
    if (exitCode==0)
    {
        QString out=m_process->readAllStandardOutput();
        if (out.isEmpty())
            out="complete";
         emit gitResult(out);
    }
    else
    {
        QString error=m_process->readAllStandardError();
        if (error.isEmpty())
            error="error in call command";
        emit gitResult(error);
    }
}
void GitProcess::resultCheckGit(int exitCode)
{
    if (exitCode==0)
    {
        emit gitEnabled();
    }
    else
    {
        QMessageBox info(QMessageBox::Warning,"Отсутствует Git","На вашем компьютере не был обнаружен Git. "
                                                                "Для использования всех возможностей программы "
                                                                "рекомендуется установить Git.",QMessageBox::Ok);
        info.exec();
        emit gitNotEnabled();
    }
}

void GitProcess::resultGitStatus(int exitCode)
{
    if (exitCode==0)
    {
       QString result=m_process->readAllStandardOutput();
       emit gitResult(result);
       QRegExp file("(?=\\n\\t).*.(txt|png|json|upp)");
       file.setMinimal(true);
       QStringList result_list;
       int pos;
       while ((pos = file.indexIn(result, pos)) != -1) {
            QString temp= file.cap(0);
            temp.remove(0,2);
            result_list << temp;
            pos += file.matchedLength();
        }
       emit gitListFiles(result_list);
    }
    else
    {
         emit gitResult(m_process->readAllStandardError());
    }
}

void GitProcess::set_project_directory(QString directory)
{
    m_projectDirectory=directory;
}
