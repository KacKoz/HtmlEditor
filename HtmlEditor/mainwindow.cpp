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

    this->setCentralWidget(ui->horizontalLayoutWidget);
    setWindowTitle("Untitled");
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::wheelEvent(QWheelEvent *event)
{
    if(GetAsyncKeyState(VK_LCONTROL) & 0x81)
    {
        QFont f = ui->plainTextEdit->font();
        int size = f.pointSize();
        size += event->angleDelta().y()/16;
        f.setPointSize(size);
        ui->plainTextEdit->setFont(f);
    }
}


void MainWindow::on_actionNew_triggered()
{
    bool isCanceled = 0;
    if(hasChanged)
    {
        isCanceled = saveInfo();
    }
    if(!isCanceled){
        currentFile.clear();
        ui->plainTextEdit->setPlainText(QString());
        setWindowTitle("Untitled");
        if(hasChanged)
        hasChanged = false;
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open the file");
    QFile file(filename);
    currentFile=filename;
    if(!file.open(QIODevice::ReadWrite | QFile::Text)){
        QMessageBox::warning(this,"Warning","Cannot open file: "+file.errorString());
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->plainTextEdit->setPlainText(text);
    hasChanged = false;
    setWindowTitle(filename);
    file.close();
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
          return 0;
      case QMessageBox::Discard:
          // Don't Save was clicked
          return 0;
      case QMessageBox::Cancel:
          msgBox.close();
          return 1;
      default:
          return 0;
          break;
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    setWindowTitle(windowTitle().replace(0,1,""));
    hasChanged=false;
    QString filename = QFileDialog::getSaveFileName(this,"Save as");
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","Cannot save file: "+file.errorString());
        return;
    }
    currentFile=filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->plainTextEdit->toPlainText();
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
        QString text = ui->plainTextEdit->toPlainText();
        qDebug()<< text;
        out<<text;
    }
    else{
        on_actionSave_as_triggered();
    }
}



void MainWindow::closeEvent(QCloseEvent *event)
{
    bool isCanceled = 0;
    if(hasChanged)
    {
        isCanceled = saveInfo();
    }
    if(isCanceled){
        event->ignore();
    }
}


void MainWindow::on_actionCut_triggered()
{
    ui->plainTextEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->plainTextEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->plainTextEdit->paste();
}

void MainWindow::on_actionDelete_triggered()
{
    QTextCursor cur = ui->plainTextEdit->textCursor();
    cur.removeSelectedText();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->plainTextEdit->undo();
}

void MainWindow::on_plainTextEdit_textChanged()
{
    if(!hasChanged)
    {
        setWindowTitle("*"+this->windowTitle());
    }
    hasChanged=true;
}
