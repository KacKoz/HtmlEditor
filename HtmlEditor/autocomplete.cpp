#include "autocomplete.h"
#include <QDebug>
#include <QMenu>


//Autocomplete::Autocomplete(){ qDebug()<<"jeje";}
void Autocomplete::runautocomplete(QString editortext,QTextCursor editorcursor,QRect editorcursorpos)
{
    QTextCursor cursor =editorcursor;
    int cursorpos = cursor.position();
    QString text =editortext;
//    if(cursorpos>0)
//    {
//        //NawetqDebug()<<text[cursorpos-1];
//        int posless = text.lastIndexOf("<",cursorpos-2);
//        int posgreater =text.lastIndexOf(">",cursorpos-2);
//        qDebug()<<cursorpos-2;
//        qDebug()<<posless;
//        qDebug()<<posgreater;
//        if(posless>posgreater)
//        {
//            islessthan = true;
//            if(text[cursorpos-1]==">" and text.length()>previouslength )
//            {
//                islessthan=false;
//                tag=text.mid(posless+1,cursorpos-2-posless);
//                if(text.indexOf("</"+tag+">",cursorpos)!=cursorpos and tag!="")
//                    emit closingtag("</"+tag+">");
//                emit hidelist();
//            }
//        }
//        else
//        {
//            islessthan =false;
//            emit hidelist();
//        }
//        if(islessthan)
//            emit sendcursorpos(editor->cursorRect());
//    }
//    previouslength=text.length();

    if(cursorpos>0)
    {
        QString textbeforecursor = text.left(cursorpos);
//        cursor.select(QTextCursor::LineUnderCursor);
//        QString textbeforecursor = cursor.selectedText();
        //qDebug()<<textbeforecursor;
        int posless = textbeforecursor.lastIndexOf("<");
        int posgreater =textbeforecursor.lastIndexOf(">");
        if(posless>posgreater)
        {
            islessthan = true;
            tag=textbeforecursor.mid(posless);
            //qDebug()<<tag;
        }
        else
        {
            if(text[cursorpos-1]==">" and tag.mid(1)!=nullptr)
            {
                emit closingtag("</"+tag.mid(1)+">");
                qDebug()<<"</"+tag.mid(1)+">";
            }
            tag="";
            islessthan = false;
            emit hidelist();
        }
        if(islessthan)
            emit sendcursorpos(editorcursorpos);
    }
    else
    {
        emit hidelist();
    }

}
