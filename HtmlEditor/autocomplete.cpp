#include "autocomplete.h"
#include <QDebug>


Autocomplete::Autocomplete(QPlainTextEdit* editor): editor(editor){}
//Autocomplete::Autocomplete(){ qDebug()<<"jeje";}
void Autocomplete::ontextchanged()
{
    QTextCursor cursor =editor->textCursor();
    int cursorpos = cursor.position();
    QString text =editor->toPlainText();
    if(cursorpos>2)
    {
        //qDebug()<<text[cursorpos-1];
        if(text[cursorpos-1]==">")
        {
            int posless = text.lastIndexOf("<",cursorpos-2);
            int posgreater =text.lastIndexOf(">",cursorpos-2);
            if(posless>posgreater)
            {
                tag=text.mid(posless+1,cursorpos-2-posless);
                emit closingtag("</"+tag+">");
            }
        }
    }
}
