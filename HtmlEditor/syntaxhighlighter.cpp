#include "syntaxhighlighter.h"
#include <QDebug>


syntaxHighlighter::syntaxHighlighter(QPlainTextEdit* codeeditor)
    : QSyntaxHighlighter(codeeditor)
{
    this->setDocument(codeeditor->document());
}

void syntaxHighlighter::highlightBlock( const QString& text)
{
    //qDebug() << "Last line: " << previousBlockState();

    if(text.length() == 0)
    {
        if(previousBlockState() > -1)
            setCurrentBlockState(previousBlockState());
        else
            setCurrentBlockState(NORMAL);
        return;
    }

    int startIndex = -1;
    int comment = 0;
    bool script = false;

    currentState state = currentState::beggining;
    //setCurrentBlockState(NORMAL);

    if(previousBlockState() != NORMAL)
    {
        switch (previousBlockState())
        {
            case STRING:
            {
                state = currentState::string;
                startIndex = 0;
                break;
            }

            case ATTRIBUTE:
            {
                state = currentState::attribute;
                break;
            }

            case VALUE:
            {
                state = currentState::value;
                break;
            }

            case ASSIGN:
            {
                state = currentState::assign;
                break;
            }

            case COMMENT:
            {
                state = currentState::comment;
                startIndex = 0;
            }

        }
    }


    for(int i=0; i<text.size(); i++)
    {

        switch(state)
        {
            case currentState::comment:
            {
                if(text[i] == '-' && text.length() > i+2 && text.mid(i, 3) == "-->")
                {
                    setFormat(startIndex, i-startIndex+3, colors.commentColor);
                    state = currentState::beggining;
                    startIndex = -1;
                }
                break;
            }

            case currentState::attribute:
            {
                if(startIndex == -1)
                {
                    if(text[i].isLetter())
                        startIndex = i;
                    else if(text[i] == '>' || text[i] == '<')
                        state = currentState::beggining;

                }
                else if(startIndex != -1 && (text[i] == '='))
                {
                    setFormat(startIndex, i-startIndex, colors.attributeColor);
                    startIndex = -1;
                    state = currentState::value;
                }
                break;
            }

            case currentState::beggining:
            {
                if(text[i] == '<')
                {
                    comment = 1;
                    state = currentState::tagName;
                }
                break;
            }

            case currentState::string:
            {
                if(text[i] == '"')
                {
                    setFormat(startIndex, i-startIndex+1, colors.stringColor);
                    startIndex = -1;
                    state = currentState::attribute;
                }

                break;
            }

            case currentState::number:
            {
                if(!text[i].isDigit())
                {
                    startIndex = -1;
                    if(text[i].isSpace())
                    {
                        setFormat(startIndex, i-startIndex, colors.numberColor);
                        state = currentState::attribute;
                    }
                    else
                        state = currentState::beggining;
                }

                break;
            }

            case currentState::value:
            {
                if(text[i] == '"')
                {
                    state = currentState::string;
                    startIndex = i;
                }
                else if(text[i].isDigit())
                {
                    startIndex = i;
                    state = currentState::number;
                }

                break;
            }

            case currentState::tagName:
            {
                if(startIndex == -1)
                {
                    if(text[i] == '/')
                    {
                        comment = 0;
                    }
                    else if(text[i].isLetter())
                    {
                        startIndex = i;
                        comment = 0;
                    }
                    else if(text[i].isSpace())
                    {
                        comment = 0;
                        state = currentState::beggining;
                    }
                    else if(text[i] == '!')
                    {
                        if(comment == 1 && text.length() > i+2)
                        {
                            if(text[i+1] == '-' && text[i+2] == '-')
                            {
                                state = currentState::comment;
                                startIndex = i-1;
                            }
                        }
                        else
                            state = currentState::beggining;
                    }
                }
                else if(startIndex != -1)
                {
                    if(text[i].isSpace())
                    {
                        setFormat(startIndex, i-startIndex, colors.tagColor);
                        startIndex = -1;
                        state = currentState::attribute;
                        if(text.mid(startIndex, i-startIndex) == "script" && text[startIndex-1] != '/')
                        {
                            script = true;
                        }
                        else
                        {
                            script = false;
                        }
                    }
                    else if(text[i] == '>')
                    {
                        setFormat(startIndex, i-startIndex, colors.tagColor);
                        startIndex = -1;
                        state = currentState::beggining;             
                    }

                }

                break;
            }

            case currentState::assign:
            {

                if(text[i] == '=')
                {
                    state = currentState::value;
                }


                break;
            }
        }

    }

    switch(state)
    {
        case currentState::comment:
        {
            setFormat(startIndex, text.length()-startIndex, colors.commentColor);
            setCurrentBlockState(COMMENT);
            break;
        }

        case currentState::attribute:
        {
            if(startIndex == -1)
            {
                setCurrentBlockState(ATTRIBUTE);
            }
            else
            {
                setFormat(startIndex, text.length()-startIndex, colors.attributeColor);
                setCurrentBlockState(ASSIGN);
            }
            break;
        }

        case currentState::beggining:
        {
            setCurrentBlockState(NORMAL);
            break;
        }

        case currentState::string:
        {
                setFormat(startIndex, text.length()-startIndex, colors.stringColor);

                setCurrentBlockState(STRING);


            break;
        }

        case currentState::number:
        {
            setFormat(startIndex, text.length()-startIndex, colors.numberColor);
            setCurrentBlockState(ATTRIBUTE);

            break;
        }

        case currentState::value:
        {
            setCurrentBlockState(VALUE);

            break;
        }

        case currentState::tagName:
        {
            if(startIndex == -1)
                setCurrentBlockState(NORMAL); //ERROR
            else
            {
                setFormat(startIndex, text.length() - startIndex, colors.tagColor);
                setCurrentBlockState(ATTRIBUTE);
            }

            break;
        }

        case currentState::assign:
        {
            setCurrentBlockState(ASSIGN);
            break;
        }

    }

    //qDebug()<<"Koniec bloku z " << currentBlockState();


  }


    /*QRegularExpression re;
    QRegularExpression re1;
    //re.setPattern("<\\w+|</\\w+");
    //re.setPattern("<\\s+\\w+|<\\w+|<\\s+\\w+|</\\w+");
    re.setPattern("<");
    re1.setPattern(">");
    QRegularExpressionMatchIterator it = re.globalMatch(text);
    QRegularExpressionMatchIterator it1 = re1.globalMatch(text);
    while(it.hasNext())
    {

        QRegularExpressionMatch match = it.next();
        if(it1.hasNext())
            setFormat(match.capturedStart(), match.capturedLength(), colors.tagColor);
    }*/



 /*   tc.select(QTextCursor::Document);
    tc.removeSelectedText();

    QTextCharFormat f = tc.charFormat();
    //f.setForeground(this->colors.tagColor);

    bool inTag = false;
    bool inWord = false;
   // int tagStart = 0;
    QString curWord = "";

    for(int i = 0; i<text.size(); i++)
    {
        if(text[i] == "<")
        {
            if(inWord)
            {
               curWord.append(text[i]);
            }
            else if(inTag)
            {
                    inTag = false;
                    inWord = true;

                    curWord.append(text[i]);
            }
            else
            {
                inTag = true;
                curWord.append(text[i]);
            }
        }
        else if(text[i] == ">")
        {
            if(inTag)
            {
                inTag = false;
                curWord.append(">");
                f.setForeground(this->colors.tagColor);
                tc.setCharFormat(f);
                tc.insertText(curWord);
                curWord="";
            }
            else if(inWord)
            {
                curWord.append(text[i]);
            }
            else
            {
                inWord = true;
                curWord = text[i];
            }
        }
        else if(text[i].isSpace())
        {
            if(inTag)
            {
                curWord.append(text[i]);
            }
            else if(inWord)
            {
                inWord = false;
                f.setForeground(this->colors.normalColor);
                tc.setCharFormat(f);
                curWord.append(text[i]);
                tc.insertText(curWord);
                curWord = "";
            }
            else
            {
                curWord.append(text[i]);
                tc.insertText(text.mid(i, 1));
                curWord = "";
            }
        }
        else
        {
            if(inTag or inWord)
            {
                curWord.append(text[i]);
            }
            else
            {
                inWord = true;
                curWord = "";
                curWord.append(text[i]);
            }
        }
    }




}*/

