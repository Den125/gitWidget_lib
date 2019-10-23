#include "gitwidget.h"
#include "ui_gitwidget.h"
#include "gitprocess.h"
#include <QDebug>

GitWidget::GitWidget(QWidget *parent,
                     QString repository,QString directory) :
    QDialog(parent),
    ui(new Ui::GitWidget)
{
    ui->setupUi(this);
    m_process=new GitProcess();
    connect(m_process,SIGNAL(gitEnabled()),this,SLOT(activateGit()));
    connect(m_process,SIGNAL(gitNotEnabled()),this,SLOT(deactivateGit()));
    connect(ui->buttonAdd,SIGNAL(clicked()),m_process,SLOT(commandGitAdd()));
    connect(ui->buttonInit,SIGNAL(clicked()),m_process,SLOT(commandGitInit()));
    connect(ui->buttonPush,SIGNAL(clicked()),m_process,SLOT(commandGitPush()));
    connect(ui->buttonStatus,SIGNAL(clicked()),m_process,SLOT(commandGitStatus()));
    connect(m_process,SIGNAL(gitResult(QString)),this,SLOT(addLog(QString)));
    connect(m_process,SIGNAL(gitListFiles(QStringList)),this,SLOT(setList(QStringList)));
    m_process->set_repository(repository);
    m_process->set_project_directory(directory);
}

void GitWidget::addLog(QString log)
{
    ui->Log->addItem(log);
}
/*
void GitWidget::set_data(QString repository,QString directory)
{
    m_process->set_repository(repository);
    m_process->set_project_directory(directory);
}*/
void GitWidget::activateGit()
{
  //  exec();
}

void GitWidget::deactivateGit()
{
    close();
}

void GitWidget::setList(QStringList list)
{
    ui->listWidget->clear();
    foreach(QString elem,list)
    {
        QListWidgetItem* item=new QListWidgetItem(elem);
        if (elem.contains("new file:"))
            item->setTextColor(Qt::green);
        else item->setTextColor(Qt::red);
        ui->listWidget->addItem(item);
    }
}
void GitWidget::gitCommit()
{
    if (ui->Commit->toPlainText().isEmpty())
    {
        addLog("Error: Commit is Empty");
        return;
    }
    m_process->commandGitCommit(ui->Commit->toPlainText());
}

GitWidget::~GitWidget()
{
    delete ui;
}
