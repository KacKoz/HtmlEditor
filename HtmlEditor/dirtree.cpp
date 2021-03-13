#include "dirtree.h"
#include "mainwindow.h"

#include <windows.h>
#include <winuser.h>
#include <QDebug>
#include <QString>
#include <QObject>
#include <iostream>
#include <QFileSystemModel>
#include <QHeaderView>
#include <QDirModel>
#include <QDir>
#include <QAction>
#include <QInputDialog>
#include <QMenu>
#include <QMessageBox>

DirTree::DirTree()
{
    QSizePolicy sp;
    sp.setHorizontalPolicy(QSizePolicy::Fixed);
    sp.setVerticalPolicy(QSizePolicy::Expanding);
    this->setSizePolicy(sp);
    this->setMaximumSize(200, 10000);
    model = new QFileSystemModel;
    //QString sPath = "sdafs";
//    model->setNameFilters(QStringList() << "*.txt"<< "*.html");
//    model->setFilter(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
//    model->setNameFilterDisables(false);
    //model->setRootPath("H://");
    this->setModel(model);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    //this->setRootIndex(model->index(sPath));
//    this->setSortingEnabled(true);
//    this->sortByColumn(1,Qt::AscendingOrder);

    this->hideColumn(1);
    this->hideColumn(2);
    this->hideColumn(3);
    contextopen = new QAction(this);
    contextopen->setText("Open");
    contextdelete = new QAction(this);
    contextdelete->setText("Delete");
    contextrename = new QAction(this);
    contextrename->setText("Rename");

    connect(contextopen,&QAction::triggered, this,&DirTree::on_actioncontextopen_triggered);
    connect(contextdelete,&QAction::triggered, this,&DirTree::on_actioncontextdelete_triggered);
    connect(contextrename,&QAction::triggered, this,&DirTree::on_actioncontextrename_triggered);
    connect(this,&DirTree::customContextMenuRequested,this,&DirTree::customMenuRequested);

    //connect(this,&DirTree::doubleClicked,this,&DirTree::on_treeView_doubleClicked);
}

void DirTree::changefileDirectory(QString name){
    QString sPath = name;
    while(sPath[sPath.length()-1]!='/')
    {
        sPath.remove(sPath.length()-1,1);
    }
    sPath.remove(sPath.length()-1,1);
    model->setNameFilters(QStringList() << "*.txt"<< "*.html");
    model->setFilter(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
    model->setNameFilterDisables(false);
    model->setRootPath("C://");
    this->setModel(model);
    this->setRootIndex(model->index(sPath));
    currentdir=sPath;
    //qDebug()<<sPath;
}

void DirTree::changeDirectory(QString name){
    QString sPath = name;
    model->setNameFilters(QStringList() << "*.txt"<< "*.html");
    model->setFilter(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
    model->setNameFilterDisables(false);
    model->setRootPath("C://");
    this->setModel(model);
    this->setRootIndex(model->index(sPath));
    currentdir=sPath;
}

void DirTree::mouseDoubleClickEvent(QMouseEvent * event){
    if(event->button()==Qt::LeftButton)
    {
        //QModelIndexList index = this->selectedIndexes();
        QModelIndex index = this->indexAt(event->localPos().toPoint());
        qDebug()<<model->filePath(index);
        if(model->filePath(index)!="")
        {
            if(model->isDir(index))
                changeDirectory(model->filePath(index));
            else
                emit openFileFromTree(model->filePath(index));
            //emit openFileFromTree(model->filePath(index[0]));

        }
    }
}

void DirTree::on_actioncontextopen_triggered()
{
    QModelIndex index = this->indexAt(contextmenucords);
    if(model->filePath(index)!="")
    {
        if(model->isDir(index))
        {
            changeDirectory(model->filePath(index));
        }
        else
        {
            emit openFileFromTree(model->filePath(index));
        }
    }
}
void DirTree::on_actioncontextdelete_triggered()
{
    bool execute = deleteInfo();
    if(execute)
    {
        QModelIndex index = this->indexAt(contextmenucords);
        QString name = model->filePath(index);
        if(name!="")
        {
            emit askforcurrentfilename();
            //qDebug()<<currentfile;
            if(model->isDir(index))
            {
                if(currentfile.indexOf(name)>=0 and currentfile[name.length()]=="/")
                {
                    QMessageBox msgBox;
                    msgBox.setIcon(QMessageBox::Warning);
                    msgBox.setWindowTitle("Delete");
                    msgBox.setText("Folder is in use");
                    //msgBox.setInformativeText("Do you want to save your changes?");
                    msgBox.setStandardButtons(QMessageBox::Ok);
                    msgBox.setDefaultButton(QMessageBox::Ok);
                    int ret = msgBox.exec();
                    switch (ret)
                    {
                      case QMessageBox::Ok:
                          msgBox.close();
                      default:
                          msgBox.close();
                          break;
                    }
                }
                else
                {
                    QFile file(name);
                    file.moveToTrash();
                    QDir pathDir(name);

                   if (pathDir.exists())
                   {
                        QMessageBox msgBox;
                        msgBox.setFixedWidth(300);
                        msgBox.setIcon(QMessageBox::Warning);
                        msgBox.setWindowTitle("Delete");
                        msgBox.setText("Folder is in use\n\nTry to delete the most nested directories first");
                        //msgBox.setInformativeText("Try delete the most nested directories first");
                        msgBox.setStandardButtons(QMessageBox::Ok);
                        msgBox.setDefaultButton(QMessageBox::Ok);
                        int ret = msgBox.exec();
                        switch (ret)
                        {
                          case QMessageBox::Ok:
                              msgBox.close();
                              break;
                          default:
                              msgBox.close();
                              break;
                        }
                    }
                }
            }
            else
            {
                if(currentfile==model->filePath(index))
                {
                    emit filedeleted(true);
                }
                QFile file(name);
                file.moveToTrash();
            }
        }
    }
}

int DirTree::deleteInfo() {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("Delete");
    msgBox.setText("Are you sure?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();

    switch (ret) {
      case QMessageBox::Yes:
          msgBox.close();
          return 1;
      case QMessageBox::Cancel:
          msgBox.close();
          return 0;
      default:
          return 0;
          break;
    }
}

void DirTree::on_actioncontextrename_triggered()
{
    QModelIndex index = this->indexAt(contextmenucords);
    QString name = model->filePath(index);
    if(name!="")
    {
        emit askforcurrentfilename();
        bool renamecurrent = false;
        //emit askforcurrentfilename();
        if(name==currentfile)
            renamecurrent = true;
        QFile file(name);
        //qDebug()<<file;
        while(name[name.length()-1]!='/')
        {
            name.remove(name.length()-1,1);
        }
        QString newname = QInputDialog::getText(this,"Rename","Enter a new name:",QLineEdit::Normal,model->fileName(index));
        if(newname=="")
        {
            file.close();
            return;
        }
        for(int i =0;i<9;i++)
        {
            if(newname.indexOf(forbiddennames[i])>=0 or newname.length()==0)
            {
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setWindowTitle("Invalid name");
                msgBox.setText("The file name cannot contain any of the following characters: \\/:*?\"<>|\nAnd can't be empty");
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.setDefaultButton(QMessageBox::Ok);
                int ret = msgBox.exec();
                switch (ret)
                {
                  case QMessageBox::Ok:
                      msgBox.close();
                      return;
                      break;
                  default:
                      msgBox.close();
                      return;
                      break;
                }
            }
        }
        //qDebug()<<"dsfsdfdsa";
        file.rename(name+newname);
        if(renamecurrent)
            emit currentfilenamechanged(name+newname);
        //qDebug()<<file;
        file.close();
    }
}

//void DirTree::on_treeView_doubleClicked(const QModelIndex &index)
//{
//    qDebug()<<model->filePath(index);
//    emit openFileFromTree(model->filePath(index));
//}

//void DirTree::contextMenuEvent(QContextMenuEvent *event)
//{
//    QMenu menu(this);
//    menu.addAction(newAct);
//    //contextmenucords = event->localpos();
//    //contextmenucords=this->mapFromGlobal(event->globalPos());
//    menu.exec(event->globalPos());
//}

void DirTree::customMenuRequested(const QPoint &pos)
{
    if(model->filePath(this->indexAt(pos))!="")
    {
        QMenu menu(this);
        menu.addAction(contextopen);
        if(!model->isDir(this->indexAt(pos)))
            menu.addAction(contextrename);
        menu.addAction(contextdelete);
        contextmenucords = pos;
        menu.exec(this->viewport()->mapToGlobal(pos));
    }
}

void DirTree::receivecurrentfilename(QString name)
{
    currentfile=name;
}

void DirTree::givecurrentdir()
{
    emit currentdirpath(currentdir);
}


