#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QTreeView>
#include <windows.h>
#include <winuser.h>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setCentralWidget(ui->horizontalLayoutWidget);

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
    //    ui->treeView->setVisible(true);
    }
}

void MainWindow::wheelEvent(QWheelEvent *event)
{


    if(GetAsyncKeyState(VK_LCONTROL) & 0x81)
    {
        QFont f = ui->plainTextEdit->font();
        int size = f.pointSize();
        size += event->angleDelta().y()/15;
        f.setPointSize(size);
        ui->plainTextEdit->setFont(f);
    }
}

