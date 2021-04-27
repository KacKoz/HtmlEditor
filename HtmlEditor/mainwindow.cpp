#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTextStream>
#include <QTreeView>
#include <windows.h>
#include <winuser.h>
#include <iostream>
#include <QDebug>
#include <string>
#include <QThread>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    cda = new CodeEditorArea();
    dirtree = new DirTree();
    btndir = new Button("Create directory");
    btnfile = new Button("Create file");
    btnparent = new Button("Move to parent directory");
    verticallayout = new QVBoxLayout;
    horizontallayoutmain = new QHBoxLayout;
    horizontallayoutbuttons = new QHBoxLayout;
    window = new QWidget;
    dirmenu = new QWidget;
    parser = new Parser();
    browser = new BrowserView();
    autosave = new Autosave();

    connect(cda, &CodeEditorArea::codeTextChanged, this, &MainWindow::on_plainTextEdit_textChanged);
    connect(this, &MainWindow::filechanged, dirtree, &DirTree::changefileDirectory);
    connect(this, &MainWindow::directorychanged, dirtree, &DirTree::changeDirectory);
    connect(dirtree, &DirTree::openFileFromTree, this, &MainWindow::on_actionOpen_from_tree);
    connect(dirtree, &DirTree::askforcurrentfilename, this, &MainWindow::givecurrentfilename);
    connect(this, &MainWindow::currentfilename, dirtree, &DirTree::receivecurrentfilename);
    connect(dirtree, &DirTree::filedeleted, this, &MainWindow::on_actionNew_triggered);
    connect(dirtree, &DirTree::currentfilenamechanged, this, &MainWindow::newcurrentfilename);
    connect(btndir,&QPushButton::pressed,btndir, &Button::makedir);
    connect(btnfile,&QPushButton::pressed,btnfile, &Button::makefile);
    connect(btnparent,&QPushButton::pressed,btnparent, &Button::movetoparent);
    connect(btndir,&Button::askforcurrentdir,dirtree,&DirTree::givecurrentdir);
    connect(dirtree,&DirTree::currentdirpath,btndir,&Button::receivecurrentdir);
    connect(btnfile,&Button::askforcurrentdir,dirtree,&DirTree::givecurrentdir);
    connect(dirtree,&DirTree::currentdirpath,btnfile,&Button::receivecurrentdir);
    connect(btnparent,&Button::askforcurrentdir,dirtree,&DirTree::givecurrentdir);
    connect(dirtree,&DirTree::currentdirpath,btnparent,&Button::receivecurrentdir);
    connect(btnparent, &Button::directorychanged, dirtree, &DirTree::changeDirectory);
    //connect(browser, &BrowserView::askForFileName, this, &MainWindow::givecurrentfilename);
    connect(cda, &CodeEditorArea::newText, browser, &BrowserView::onNewText);
    connect(this, &MainWindow::filechanged, cda, &CodeEditorArea::receiveCurrentFileNameMiddle);
    connect(this, &MainWindow::stopthread, autosave, &Autosave::stopthread);
    connect(autosave, &Autosave::runsave, this, &MainWindow::autosaveRequest);
    connect(this, &MainWindow::wordWrapChanged, cda, &CodeEditorArea::receiveWordWrapMiddle);
    connect(this, &MainWindow::filechanged, this, &MainWindow::fileChangedSlot);

    //codeeditor->connect(codeeditor,SIGNAL("textchanged()"),qDebug()<<"jfdhg");
    //horizontallayoutmain->addWidget(dirtree);

    verticallayout ->addWidget(btnparent);
    verticallayout ->addWidget(dirtree);
    verticallayout->addLayout(horizontallayoutbuttons);
    horizontallayoutbuttons->addWidget(btndir);
    horizontallayoutbuttons->addWidget(btnfile);
    dirmenu->setLayout(verticallayout);


    horizontallayoutmain->addWidget(dirmenu);
    horizontallayoutmain->addWidget(cda);
    //horizontallayoutmain->addWidget(lna);
    //horizontallayoutmain->addWidget(codeeditor);
    window->setLayout(horizontallayoutmain);


    this->setCentralWidget(window);
    setWindowTitle("Untitled");

}

MainWindow::~MainWindow()
{
    delete ui;
    delete dirtree;
    delete btndir;
    delete btnfile;
    delete btnparent;
    delete horizontallayoutbuttons;
    delete verticallayout;
    delete dirmenu;
    delete horizontallayoutmain;
    delete window;
    delete browser;
    delete parser;
    delete autosave;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if(this->width() < 500)
    {
        dirmenu->setVisible(false);
    }
    else if(!dirmenu->isVisible())
    {
        dirmenu->setVisible(true);
    }
}


void MainWindow::on_actionNew_triggered(bool deletedintree)
{
    //qDebug()<<deletedintree;
    int isCanceled = 1;
    if(hasChanged and !deletedintree)
    {
        isCanceled = saveInfo();
    }
    if(deletedintree)
    {
        hasChanged=false;
    }
    if(isCanceled and !(isCanceled==1 and hasChanged==true)){
        currentFile.clear();// zobaczyć czy wysyłać emita=====================
        emit filechanged(currentFile);
        fileChangedSlot(currentFile);
        cda->setText(QString());
        setWindowTitle("Untitled");
        if(hasChanged)
        hasChanged = false;
    }
}

void MainWindow::on_actionOpen_triggered()
{
    int isCanceled = 1;
    if(hasChanged)
    {
        isCanceled = saveInfo();
    }
    if(isCanceled and !(isCanceled==1 and hasChanged==true)){
        QString filename = QFileDialog::getOpenFileName(this,"Open the file");
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly | QFile::Text)){
            QMessageBox::warning(this,"Warning","Cannot open file: "+file.errorString());
            return;
        }
        currentFile=filename;
        emit filechanged(currentFile);
        QTextStream in(&file);
        QString text = in.readAll();
        cda->setText(text);
        hasChanged = false;
        setWindowTitle(filename);
        file.close();
// ////////////////////////////////////////////////////////////////////////////////////
//        try
//        {
//            QString filename = QFileDialog::getOpenFileName(this,"Open the file");
//            QFile file(filename);
//            if(!file.open(QIODevice::ReadOnly | QFile::Text)){
//                throw 1;
//            }
//            currentFile=filename;
//            emit filechanged(currentFile);
//            QTextStream in(&file);
//            QString text = in.readAll();
//            cda->setText(text);
//            hasChanged = false;
//            setWindowTitle(filename);
//            file.close();
//        }
//        catch(...)
//        {
//            QMessageBox::warning(this,"Warning","Cannot open file: "+file.errorString());
//            return;
//        }
    }
}

void MainWindow::on_actionOpen_from_tree(QString path){
    if(currentFile!=path)
    {
        int isCanceled = 1;
        if(hasChanged)
        {
            isCanceled = saveInfo();
        }
        if(isCanceled and !(isCanceled==1 and hasChanged==true)){
            //QString filename = QFileDialog::getOpenFileName(this,"Open the file");
            QFile file(path);
            //qDebug()<<currentFile;
            if(!file.open(QIODevice::ReadWrite | QFile::Text)){
                QMessageBox::warning(this,"Warning","Cannot open file: "+file.errorString());
                return;
            }
            currentFile=path;
            emit filechanged(currentFile);
            QTextStream in(&file);
            QString text = in.readAll();
            cda->setText(text);
            hasChanged = false;
            setWindowTitle(path);
            file.close();
        }
    }
}


int MainWindow::saveInfo() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Save");
    msgBox.setText("Do you want to save changes to "+windowTitle()+"?");
    //msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    switch (ret) {
      case QMessageBox::Save:
          on_actionSave_triggered();
          return 1;
      case QMessageBox::Discard:
          // Don't Save was clicked
          return 2;
      case QMessageBox::Cancel:
          msgBox.close();
          return 0;
      default:
          return 0;
          break;
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,"Save as");
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","Cannot save file: "+file.errorString());
        return;
    }
    setWindowTitle(windowTitle().replace(0,1,""));
    hasChanged=false;
    currentFile=filename;
    emit filechanged(currentFile);
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = cda->getText();
    out<<text;
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    //qDebug()<<currentFile;
    if(hasChanged)
    {
        if(currentFile !=""){
            setWindowTitle(windowTitle().replace(0,1,""));
            hasChanged=false;
            QFile file(currentFile);
            if(!file.open(QIODevice::WriteOnly | QFile::Text)){
                QMessageBox::warning(this,"Warning","Cannot open file: "+file.errorString());
                return;
            }
            QTextStream out(&file);
            QString text = cda->getText();
            //qDebug()<< text;
            out<<text;
            file.close();
        }
        else{
            on_actionSave_as_triggered();
        }
    }
}



void MainWindow::closeEvent(QCloseEvent *event)
{
    int isCanceled = 1;
    if(hasChanged)
    {
        isCanceled = saveInfo();
    }
    //qDebug()<<hasChanged;
    //qDebug()<<isCanceled;
    if(!isCanceled or (isCanceled==1 and hasChanged==true)){
        event->ignore();
    }
    parser->parserTree.close();
}


void MainWindow::on_actionCut_triggered()
{
    cda->Cut();
}

void MainWindow::on_actionCopy_triggered()
{
    cda->Copy();
}

void MainWindow::on_actionPaste_triggered()
{
    cda->Paste();
}

void MainWindow::on_actionDelete_triggered()
{
    cda->Delete();
}

void MainWindow::on_actionUndo_triggered()
{
    cda->Undo();
}

void MainWindow::on_plainTextEdit_textChanged()
{
    if(!hasChanged)
    {
        setWindowTitle("*"+this->windowTitle());
    }
    hasChanged=true;
}

void MainWindow::on_actionOpen_directory_triggered()
{
    QString directoryname = QFileDialog::getExistingDirectory(this,"Open directory");
    if(directoryname!="")
        emit directorychanged(directoryname);
}

void MainWindow::givecurrentfilename()
{
    emit currentfilename(currentFile);
}

void MainWindow::newcurrentfilename(QString name)
{
    currentFile = name;
    if(hasChanged)
        setWindowTitle("*"+currentFile);
    else
        setWindowTitle(currentFile);
    emit filechanged(name);
}


void MainWindow::on_actionParsuj_triggered()
{
    parser->parsuj(cda->getText());
    parser->list.print(parser->list.head,0);
    parser->parserTree.clear();
    parser->fillTree(parser->list.head);
    parser->parserTree.show();
    parser->list.deleteTagsList(parser->list.head);
}

void MainWindow::on_actionShow_hide_preview_triggered()
{
    if(browser->isVisible())
        browser->setVisible(false);
    else
    {
        browser->setVisible(true);
        cda->onTextChanged();
    }
}

//void MainWindow::onlyhtml(QString func)
//{
//    QMessageBox msgBox;
//    msgBox.setIcon(QMessageBox::Warning);
//    msgBox.setWindowTitle("Wrong extension");
//    msgBox.setText(func+" works only on html files");
//    msgBox.setStandardButtons(QMessageBox::Ok);
//    msgBox.setDefaultButton(QMessageBox::Ok);
//    int ret = msgBox.exec();
//    switch (ret)
//    {
//      case QMessageBox::Ok:
//          msgBox.close();
//          break;
//      default:
//          msgBox.close();
//          break;
//    }
//}

//void MainWindow::autosave()
//{
//    while(autosaveon)
//    {
//        qDebug()<<"sdfsd";
//    }
//}

void MainWindow::on_actionAutosave_toggled(bool arg1)
{
    if(arg1)
    {
        ui->actionAutosave->setChecked(true);
        qDebug()<<"on";
        emit stopthread(false);
        autosave->start();
    }
    else
    {
        qDebug()<<"off";
        ui->actionAutosave->setChecked(false);
        if(autosave->isRunning() and currentFile!="")
        {
            emit stopthread(true);
            autosave->quit();
            autosave->wait();
        }
    }
}

void MainWindow::autosaveRequest()
{
    on_actionSave_triggered();
}



void MainWindow::on_actionWord_wrap_toggled(bool arg1)
{
    emit wordWrapChanged(arg1);
}

void MainWindow::fileChangedSlot(QString name){
    on_actionAutosave_toggled(false);
    if(name.endsWith("html"))
    {
        ui->actionShow_hide_preview->setEnabled(true);
        ui->actionParsuj->setEnabled(true);
        ui->actionAutosave->setEnabled(true);
    }
    else if(name.endsWith("txt")){
        ui->actionAutosave->setEnabled(true);
    }
    else
    {
        ui->actionAutosave->setEnabled(false);
        ui->actionShow_hide_preview->setEnabled(false);
        ui->actionParsuj->setEnabled(false);
    }
}
