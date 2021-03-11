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
        infofirstopen("directory");
    }

}

void Button::makefile(){
    qDebug()<<"makefile";
    emit askforcurrentdir();
    qDebug()<<currentdir;
    if(currentdir!="")
    {
        QString name = QInputDialog::getText(this,"Create file","Enter a name:",QLineEdit::Normal,"*.txt");
        QFile file(currentdir+"/"+name);
        qDebug()<<currentdir+"/"+name;
        if (!file.exists())
        {
            if (file.open(QIODevice::ReadWrite)) {
                    QTextStream stream(&file);
                    //stream << "something" << endl;
                    file.close();
                }
            else
                qDebug() << "file open error";
        }
    }
    else
    {
        infofirstopen("file");
    }

}

void Button::receivecurrentdir(QString path){
    currentdir= path;
}

void Button::infofirstopen(QString fileordir){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("Creating "+fileordir);
    msgBox.setText("Open some directory first");
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
