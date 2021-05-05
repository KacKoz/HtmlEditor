#include "syntaxhighlighter.h"
#include <QDebug>


syntaxHighlighter::syntaxHighlighter(QPlainTextEdit* codeeditor)
    : QSyntaxHighlighter(codeeditor)
{
    this->setDocument(codeeditor->document());

    this->incorrect.setFontUnderline(true);
    this->incorrect.setUnderlineColor(Qt::red);
}

void syntaxHighlighter::receivecurrentfilename(QString name)
{
    if(name == "Untilted" || name == "*Untilted" || name.endsWith(".html"))
        shouldColor = true;
    else
        shouldColor = false;
}

void syntaxHighlighter::highlightBlock( const QString& text)
{
    //qDebug() << "Last line: " << previousBlockState();
    if(!shouldColor)
        return;
    // dodac zmienna mowiaca czy ma kolorowac

    if(text.length() == 0)
    {
        if(previousBlockState() > -1)
            setCurrentBlockState(previousBlockState());
        else
            setCurrentBlockState(NORMAL);
        return;
    }

    int startIndex = -1;
    int lastIndex = 0;
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
                startIndex = 0;
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
                    setFormat(startIndex, i-startIndex+3, colors["comment"]);
                    state = currentState::beggining;
                    lastIndex = i + 3;
                    startIndex = -1;
                }
                break;
            }

            case currentState::incorrectValue:
            {
                if(text[i] == '>')
                {

                    setFormat(startIndex, i-1, incorrect);
                    setFormat(i, i+1, colors["base"]);
                    startIndex = -1;
                    lastIndex = i;
                    state = currentState::beggining;
                }
                else if(text[i].isSpace())
                {

                    setFormat(startIndex, i-1, incorrect);
                    setFormat(i, i+1, colors["base"]);
                    startIndex = -1;
                    lastIndex = -1;
                    state = currentState::attribute;
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
                    {
                        lastIndex = i;
                        state = currentState::beggining;
                    }

                }
                else if(startIndex != -1)
                {
                    setFormat(startIndex, i-startIndex, colors["attribute"]);
                    if(text[i] == '=')
                    {
                        setFormat(i, i+1, colors["base"]);
                        startIndex = -1;
                        lastIndex = -1;
                        state = currentState::value;
                    }
                    else if(text[i] == '>')
                    {
                        lastIndex = i;
                        state = currentState::beggining;
                        startIndex = -1;
                    }

                }
                break;
            }

            case currentState::beggining:
            {
                if(text[i] == '<')
                {
                    comment = 1;
                    setFormat(lastIndex, i - lastIndex + 1, colors["base"]);
                    lastIndex = -1;
                    state = currentState::tagName;
                }
                break;
            }

            case currentState::string:
            {
                if(text[i] == '"')
                {
                    setFormat(startIndex, i-startIndex+1, colors["string"]);
                    startIndex = -1;
                    state = currentState::attribute;
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
                else if(text[i] == ">")
                {
                    lastIndex = i;
                    state = currentState::beggining;
                }
                else if(text[i].isSpace())
                {
                   continue;
                }
                else
                {
                    startIndex = i;
                    state = currentState::incorrectValue;
                    //qDebug() << "BLAD WARTOSCI";
                }

                break;
            }

            case currentState::tagName:
            {
                if(startIndex == -1)
                {
                    if(text[i] == '/')
                    {
                        setFormat(i, i+1, colors["base"]);
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
                        lastIndex = i;
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
                                lastIndex = -1;
                            }
                        }
                        else
                        {
                            lastIndex = i;
                            state = currentState::beggining;
                        }
                    }
                }
                else if(startIndex != -1)
                {
                    if(text[i].isSpace())
                    {
                        setFormat(startIndex, i-startIndex, colors["tag"]);
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
                        setFormat(startIndex, i-startIndex, colors["tag"]);
                        startIndex = -1;
                        lastIndex = i;
                        state = currentState::beggining;             
                    }

                }

                break;
            }

            case currentState::assign:
            {

                if(text[i] == '=')
                {
                    setFormat(i, i+1, colors["base"]);
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
            setFormat(startIndex, text.length()-startIndex, colors["comment"]);
            setCurrentBlockState(COMMENT);
            break;
        }

        case currentState::incorrectValue:
        {
            setFormat(startIndex, text.length()-startIndex, incorrect);
            setCurrentBlockState(ATTRIBUTE);
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
                setFormat(startIndex, text.length()-startIndex, colors["attribute"]);
                setCurrentBlockState(ATTRIBUTE);
            }
            break;
        }

        case currentState::beggining:
        {
            setFormat(lastIndex, text.size(), colors["base"]);
            setCurrentBlockState(NORMAL);
            break;
        }

        case currentState::string:
        {
                setFormat(startIndex, text.length()-startIndex, colors["string"]);

                setCurrentBlockState(STRING);


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
                setFormat(startIndex, text.length() - startIndex, colors["tag"]);
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

   // qDebug()<<"Koniec bloku z " << currentBlockState();


}

void syntaxHighlighter::setConfig(const std::shared_ptr<config> &conf)
{
    QColor col;
    for(const auto& i: conf->colors)
    {
        col.setNamedColor(i.second);
        this->colors[i.first] = col;
    }

    rehighlight();
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
            setFormat(match.capturedStart(), match.capturedLength(), colors["tag"]);
    }*/



 /*   tc.select(QTextCursor::Document);
    tc.removeSelectedText();

    QTextCharFormat f = tc.charFormat();
    //f.setForeground(this->colors["tag"]);

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
                f.setForeground(this->colors["tag"]);
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
                f.setForeground(this->colors["base"]);
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

