#include "autocomplete.h"
#include <QDebug>
#include <QMenu>


<<<<<<< HEAD
Autocomplete::Autocomplete(){
    this->_tags = new TagsTree("C:\\Users\\Szymon Sieczko\\Desktop\\Repozytorium\\HtmlEditor\\HtmlEditor\\selfclosing.txt");
}


=======

Autocomplete::Autocomplete(){
    this->_tags = new TagsTree("D:\\C++\\Studia\\PK4\\HtmlEditor\\HtmlEditor\\HtmlEditor\\selfclosing.txt");
}

>>>>>>> Szymon
void Autocomplete::runautocomplete(QString editortext,QTextCursor editorcursor,QRect editorcursorpos)
{
    QTextCursor cursor =editorcursor;
    int cursorpos = cursor.position();
    QString text =editortext;
<<<<<<< HEAD
=======

>>>>>>> Szymon
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
            if(text[cursorpos-1]==">" and tag.mid(1)!=nullptr and tag.mid(1).indexOf('/')<0 and !_tags->isInTree(tag.mid(1,tag.indexOf(' ')-1)))
            {
                emit closingtag("</"+tag.mid(1,tag.indexOf(' ')-1)+">");
                //qDebug()<<"</"+tag.mid(1)+">";
<<<<<<< HEAD
=======

>>>>>>> Szymon
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
<<<<<<< HEAD
        }
=======

        }

>>>>>>> Szymon
    }
    else
    {
        emit hidelist();
    }

}

void Autocomplete::receiverow(int row)
{
    rowoftag=row;
<<<<<<< HEAD
=======

>>>>>>> Szymon
}
