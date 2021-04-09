#include "autocomplete.h"
#include <QDebug>
#include <QMenu>



Autocomplete::Autocomplete(){
    this->_tags = new TagsTree("selfclosing.txt");
}

void Autocomplete::runautocomplete(QString editortext,QTextCursor editorcursor,QRect editorcursorpos)
{
    QTextCursor cursor =editorcursor;
    int cursorpos = cursor.position();
    QString text =editortext;

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
            if(text[cursorpos-1]=="<")
                emit showlist();
            tag=textbeforecursor.mid(posless);
            //qDebug()<<tag;
        }
        else
        {
            //qDebug()<<text[cursorpos-1];
            if(text[cursorpos-1]==">" and tag.mid(1)!=nullptr and tag.mid(1).indexOf('/')<0 and tag.mid(1).indexOf('!')<0 and !_tags->isInTree(tag.mid(1,tag.indexOf(' ')-1)))
            {
                emit closingtag("</"+tag.mid(1,tag.indexOf(' ')-1)+">");
                //qDebug()<<"</"+tag.mid(1)+">";

            }
            tag="";
            islessthan = false;
            emit hidelist();

        }
        if(islessthan)
        {
            //qDebug()<<tag.mid(1);
            emit askforrow(tag.mid(1));
            emit sendcursorpos(editorcursorpos,rowoftag);

        }

    }
    else
    {
        emit hidelist();
    }

}

void Autocomplete::receiverow(int row)
{
    rowoftag=row;

}
