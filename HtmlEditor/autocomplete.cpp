#include "autocomplete.h"
#include <QDebug>
#include <QMenu>


//Autocomplete::Autocomplete(){ qDebug()<<"jeje";}
void Autocomplete::runautocomplete(QString editortext,QTextCursor editorcursor,QRect editorcursorpos)
{
    QTextCursor cursor =editorcursor;
    int cursorpos = cursor.position();
    QString text =editortext;

    if(cursorpos>0)
    {
        QString textbeforecursor = text.left(cursorpos);
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
