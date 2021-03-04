#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QTextStream>
#include <QTreeView>
#include <windows.h>
#include <winuser.h>
#include <iostream>
#include<QDebug>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    codeeditor = new CodeEditor();
    lna = new LineNumberArea();

    connect(codeeditor, &CodeEditor::fontSizeChanged, lna, &LineNumberArea::handleFontSize);
    connect(codeeditor, &QPlainTextEdit::textChanged, this, &MainWindow::on_plainTextEdit_textChanged);

    //codeeditor->connect(codeeditor,SIGNAL("textchanged()"),qDebug()<<"jfdhg");

    ui->horizontalLayout->addWidget(lna);
    ui->horizontalLayout->addWidget(codeeditor);

    this->setCentralWidget(ui->horizontalLayoutWidget);
    setWindowTitle("Untitled");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete codeeditor;
    delete lna;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if(this->width() < 500)
    {
        ui->treeView->setVisible(false);
    }
    else if(!ui->treeView->isVisible())
    {
        ui->treeView->setVisible(true);
    }
}


void MainWindow::on_actionNew_triggered()
{
    int isCanceled = 1;
    if(hasChanged)
    {
        isCanceled = saveInfo();
    }
    if(isCanceled and !(isCanceled==1 and hasChanged==true)){
        currentFile.clear();
        codeeditor->setPlainText(QString());
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
        currentFile=filename;
        if(!file.open(QIODevice::ReadWrite | QFile::Text)){
            QMessageBox::warning(this,"Warning","Cannot open file: "+file.errorString());
            return;
        }
        QTextStream in(&file);
        QString text = in.readAll();
        codeeditor->setPlainText(text);
        hasChanged = false;
        setWindowTitle(filename);
        file.close();
    }
}

int MainWindow::saveInfo() {
    QMessageBox msgBox;
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
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = codeeditor->toPlainText();
    out<<text;
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    qDebug()<<currentFile;
    if(currentFile !=""){
        setWindowTitle(windowTitle().replace(0,1,""));
        hasChanged=false;
        QFile file(currentFile);
        if(!file.open(QIODevice::ReadWrite | QFile::Text)){
            QMessageBox::warning(this,"Warning","Cannot open file: "+file.errorString());
            return;
        }
        QTextStream out(&file);
        QString text = codeeditor->toPlainText();
        qDebug()<< text;
        out<<text;
    }
    else{
        on_actionSave_as_triggered();
    }
}



void MainWindow::closeEvent(QCloseEvent *event)
{
    int isCanceled = 1;
    if(hasChanged)
    {
        isCanceled = saveInfo();
    }
    qDebug()<<hasChanged;
    qDebug()<<isCanceled;
    if(!isCanceled or (isCanceled==1 and hasChanged==true)){
        event->ignore();
    }
}


void MainWindow::on_actionCut_triggered()
{
    codeeditor->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    codeeditor->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    codeeditor->paste();
}

void MainWindow::on_actionDelete_triggered()
{
    QTextCursor cur = codeeditor->textCursor();
    cur.removeSelectedText();
}

void MainWindow::on_actionUndo_triggered()
{
    codeeditor->undo();
}

void MainWindow::on_plainTextEdit_textChanged()
{
    if(!hasChanged)
    {
        setWindowTitle("*"+this->windowTitle());
    }
    hasChanged=true;
}
