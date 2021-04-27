#include "button.h"

#include <QDebug>
#include <QInputDialog>
#include <QDir>
#include <QMessageBox>
#include <regex>

Button::Button(QString text)
{
    this->setText(text);
}



void Button::makedir(){
    emit askforcurrentdir();
    //qDebug()<<currentdir;
    if(currentdir!="")
    {
        QString name = QInputDialog::getText(this,"Create directory","Enter a name:",QLineEdit::Normal);
//        for(int i =0;i<9;i++)
//        {
//            if(name.indexOf(forbiddennames[i])>=0 or name.length()==0)
//            {
//                infoinvalidname("directory");
//                return;
//            }
//        }
        if(std::regex_match(name.toStdString(),std::regex("[^\\\\/:*?<>|\"]+")))
        {
            QDir dir(currentdir+"/"+name);            
            if (!dir.exists())
                dir.mkpath(currentdir+"/"+name);
        }
        else
        {
            infoinvalidname("directory");
        }
    }
    else
    {
        infofirstopen("Creating directory");
    }

}

void Button::makefile(){
    //qDebug()<<"makefile";
    emit askforcurrentdir();
    //qDebug()<<currentdir;
    if(currentdir!="")
    {
        QString name = QInputDialog::getText(this,"Create file","Enter a name:",QLineEdit::Normal,"*.txt");
//        for(int i =0;i<9;i++)
//        {
//            if(name.indexOf(forbiddennames[i])>=0 or name.length()==0)
//            {
//                infoinvalidname("file");
//                return;
//            }
//        }
        if(std::regex_match(name.toStdString(),std::regex("[^\\\\/:*?<>|]+\\.(txt|html)")))
        {
            QFile file(currentdir+"/"+name);
            if (!file.exists())
            {
                if (file.open(QIODevice::ReadWrite)) {
                        QTextStream stream(&file);
                        file.close();
                    }
                else
                    qDebug() << "file open error";
            }
        }
        else
        {
            infoinvalidname("file");
        }
    }
//        if(!std::regex_search(name.toStdString(),std::regex("[^\\\\/:*?<>|]+")))
//        {
//            infoinvalidname("file");
//        }
//        else
//        {
//            qDebug()<<"prawidlowa";
//        }
//    }
//    else
//    {
//        infofirstopen("Creating file");
//    }

}

void Button::receivecurrentdir(QString path){
    currentdir= path;
}

void Button::infofirstopen(QString fileordir){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle(fileordir);
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

void Button::infoinvalidname(QString fileordir){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("Invalid name");
    msgBox.setText("The "+fileordir+" name cannot contain any of the following characters: \\/:*?\"<>|\nAnd can't be empty");
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

void Button::movetoparent()
{
    emit askforcurrentdir();
    //qDebug()<<currentdir;
    if(currentdir!="")
    {
       QString name = currentdir;
       if(name[name.length()-1]=='/')
       {
           emit directorychanged("");
           return;
       }
       while(name[name.length()-1]!='/')
       {
           name.remove(name.length()-1,1);
       }
       //qDebug()<<name;
       if(name[name.length()-2]!=':')
           name.remove(name.length()-1,1);
       //qDebug()<<name;
       emit directorychanged(name);
    }
    else
    {
        infofirstopen("Moving to parent");
    }
}
