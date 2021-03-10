#include "button.h"

#include <QDebug>
#include <QInputDialog>
#include <QDir>
#include <QMessageBox>

Button::Button(QString text)
{
    this->setText(text);
}

void Button::makedir(){
    emit askforcurrentdir();
    qDebug()<<currentdir;
    if(currentdir!="")
    {
        QString name = QInputDialog::getText(this,"Create directory","Enter a name:",QLineEdit::Normal);
        QDir dir(currentdir+"/"+name);
        qDebug()<<currentdir+"/"+name;
        if (!dir.exists())
            dir.mkpath(currentdir+"/"+name);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Creating directory");
        msgBox.setText("Open some directory first");
        //msgBox.setInformativeText("Do you want to save your changes?");
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

void Button::makefile(){
    qDebug()<<"makefile";
    emit askforcurrentdir();
    qDebug()<<currentdir;
}

void Button::receivecurrentdir(QString path){
    currentdir= path;
}
