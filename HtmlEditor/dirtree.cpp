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

DirTree::DirTree()
{
    QSizePolicy sp;
    sp.setHorizontalPolicy(QSizePolicy::Fixed);
    sp.setVerticalPolicy(QSizePolicy::Expanding);
    this->setSizePolicy(sp);
    this->setMaximumSize(200, 10000);
    model = new QFileSystemModel;
    QString sPath = "sdafs";
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
    model->setNameFilters(QStringList() << "*.txt"<< "*.html");
    model->setFilter(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
    model->setNameFilterDisables(false);
    model->setRootPath("C://");
    this->setModel(model);
    this->setRootIndex(model->index(sPath));

}

void DirTree::changeDirectory(QString name){
    QString sPath = name;
    model->setNameFilters(QStringList() << "*.txt"<< "*.html");
    model->setFilter(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
    model->setNameFilterDisables(false);
    model->setRootPath("C://");
    this->setModel(model);
    this->setRootIndex(model->index(sPath));

}

void DirTree::mouseDoubleClickEvent(QMouseEvent * event){
    if(event->button()==Qt::LeftButton)
    {
        //QModelIndexList index = this->selectedIndexes();
        QModelIndex index = this->indexAt(event->localPos().toPoint());
        //qDebug()<<model->filePath(index);
        if(model->filePath(index)!="")
        {
            //emit openFileFromTree(model->filePath(index[0]));
            emit openFileFromTree(model->filePath(index));
        }
    }
}

void DirTree::on_actioncontextopen_triggered()
{

    QModelIndex index = this->indexAt(contextmenucords);
    if(model->filePath(index)!="")
    {
        emit openFileFromTree(model->filePath(index));
    }
}
void DirTree::on_actioncontextdelete_triggered()
{

    QModelIndex index = this->indexAt(contextmenucords);
    QString name = model->filePath(index);
    if(name!="")
    {
        emit askforcurrentfilename();
        qDebug()<<currentfile;
        if(currentfile==model->filePath(index))
        {
            emit filedeleted(true);
        }
        QFile file(name);
        file.remove();
    }
}
void DirTree::on_actioncontextrename_triggered()
{

    QModelIndex index = this->indexAt(contextmenucords);
    QString name = model->filePath(index);
    if(name!="")
    {
        QFile file(name);
        qDebug()<<file;
        while(name[name.length()-1]!='/')
        {
            name.remove(name.length()-1,1);
        }
        QString newname = QInputDialog::getText(this,"Rename","Enter a new name:",QLineEdit::Normal,model->fileName(index));
        file.rename(name+newname);
        qDebug()<<file;
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



