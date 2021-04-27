#include "codeeditor.h"
#include <QPalette>
#include <windows.h>
#include <winuser.h>
#include <QDebug>
#include <QTextBlock>
#include <QScrollBar>
#include <QApplication>
#include <QClipboard>
#include <QMimeData>
#include <QDir>

#include <iostream>

class syntaxHighlighter;

CodeEditor::CodeEditor()
{
    autocomplete = new Autocomplete();
    sh = new syntaxHighlighter(this);
    taghints = new Tagsuggestion(this);

    QPalette pal;
    pal.setColor(QPalette::Text, Qt::white);
    pal.setColor(QPalette::Base, QRgb(0x5a5a5a));
    //this->setAutoFillBackground(true);
    this->setPalette(pal);
    //this->setLineWrapMode(LineWrapMode::NoWrap);
    //this->setWordWrapMode(QTextOption::WordWrap);
    this->setLineWrapMode(LineWrapMode::WidgetWidth);

    connect(this, &QPlainTextEdit::blockCountChanged, this, &CodeEditor::onBlockCountChange);
    connect(this, &QPlainTextEdit::updateRequest, this, &CodeEditor::onUpdateRequest);
    connect(this, &QPlainTextEdit::cursorPositionChanged, this, &CodeEditor::onCursorMoved);
    connect(this, &QPlainTextEdit::textChanged,this, &CodeEditor::ontextchanged);
    connect(autocomplete, &Autocomplete::closingtag,this, &CodeEditor::insertclosingtag);
    connect(autocomplete, &Autocomplete::sendcursorpos,taghints,&Tagsuggestion::movelist);
    connect(autocomplete, &Autocomplete::hidelist,taghints,&Tagsuggestion::hidelist);

    connect(autocomplete, &Autocomplete::showlist,taghints,&Tagsuggestion::showlist);
    connect(this,&CodeEditor::sizechanged,taghints,&Tagsuggestion::parentchangedsize);
    connect(taghints,&Tagsuggestion::sendsuggestion,this,&CodeEditor::writesuggestion);
    connect(this, &CodeEditor::giveFileNameToSH, sh, &syntaxHighlighter::receivecurrentfilename);



    this->_linesInBlock.push_back(1);
    _selection.format.setBackground(QColor(QRgb(0x4a4a4a)));
    _selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    highlightCurrentLine();

}

//destruktor
CodeEditor::~CodeEditor()
{
    delete sh;
    delete taghints;
    delete autocomplete;
}

void CodeEditor::wheelEvent(QWheelEvent *event)
{
    //this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() - (event->angleDelta().y()/25));

    QPlainTextEdit::wheelEvent(event);
    if(GetAsyncKeyState(VK_LCONTROL) & 0x81)
    {
        QFont f = this->font();
        int size = f.pointSize();
        size += event->angleDelta().y()/25;
        if(size>5 && size < 50)
        {
            f.setPointSize(size);
            emit fontSizeChanged(size);
        }
        this->setFont(f);
        emit blockCountChanged(_linesInBlock.size());
    }
    else
    {
        emit scrolledTo(this->verticalScrollBar()->value());
    }

}

void  CodeEditor::onBlockCountChange(int count)
{
    _linesInBlock.resize(count);
    QTextBlock tb = this->firstVisibleBlock();

    for(int i=tb.firstLineNumber(); i < count; i++)
    {
        _linesInBlock[i] = tb.lineCount();
        tb = tb.next();
    }

    emit blockCountVector(&_linesInBlock);
    emit scrolledTo(this->verticalScrollBar()->value());
}

void CodeEditor::onUpdateRequest()
{
    emit scrolledTo(this->verticalScrollBar()->value());
    emit blockCountChanged(_linesInBlock.size());
}

void CodeEditor::onCursorMoved()
{
    emit scrolledTo(this->verticalScrollBar()->value());
    emit blockCountChanged(_linesInBlock.size());
    highlightCurrentLine();
}

void CodeEditor::highlightCurrentLine()
{
    if(!isReadOnly())
    {
        _selection.cursor = textCursor();
       // _selection.cursor.clearSelection();
        _extraSelections.clear();
        _extraSelections.append(_selection);
        setExtraSelections(_extraSelections);
    }
}

void CodeEditor::onSelectLine(int line)
{
    QTextBlock tb = this->firstVisibleBlock();
    while(tb.isValid() && tb.blockNumber() != line)
        tb = tb.next();

    //qDebug() << "Line: " << line;

    if(!tb.isValid())
    {
        //qDebug() << "Error! Block to select not valid!";
    }
    else
    {

        /*_selection.cursor = textCursor();
        this->_selection.cursor.setPosition(line);
        _extraSelections.append(_selection);
        setExtraSelections(_extraSelections);*/
        QTextCursor tc = this->textCursor();
        setTextCursorPosition(tc, line);
        tc.select(QTextCursor::BlockUnderCursor);
        this->setTextCursor(tc);
        this->setFocus();

    }
}

void CodeEditor::setTextCursorPosition(QTextCursor& tc, int blockNumber)
{
    int curBlockNum = tc.blockNumber();
    tc.movePosition(blockNumber > curBlockNum ?
    QTextCursor::NextBlock : QTextCursor::PreviousBlock,
    QTextCursor::MoveAnchor, abs(curBlockNum - blockNumber));
}

void CodeEditor::insertclosingtag(QString closingtag)
{
    QTextCursor cursor = this->textCursor();
    int cursorpos=cursor.position();
    this->blockSignals(true);
    this->textCursor().insertText(closingtag);
    this->blockSignals(false);
    cursor.setPosition(cursorpos);
    this->setTextCursor(cursor);
    //qDebug()<<this->textCursor().position();
}

void CodeEditor::ontextchanged()
{
    if(currentfilename.endsWith("html"))
    {
        autocomplete->runautocomplete(this->toPlainText(),this->textCursor(),this->cursorRect());
    }
}

void CodeEditor::resizeEvent(QResizeEvent *event)
{
    emit sizechanged(this->viewport());
    QPlainTextEdit::resizeEvent(event);
}

void CodeEditor::keyPressEvent(QKeyEvent *event)
{
    if((event->key()==Qt::Key_Down || event->key()==Qt::Key_Up || event->key()==Qt::Key_Tab) && !taghints->isHidden())
    {
        taghints->setFocus();
        taghints->keyPressEvent(event);
    }
    else
    {
        if(event->key()==Qt::Key_Escape)
            taghints->setVisible(false);
        QPlainTextEdit::keyPressEvent(event);
    }
}

void CodeEditor::writesuggestion(QString tag)
{
    QTextCursor cursor = this->textCursor();
    int cursorpos=cursor.position();
    while(this->toPlainText()[cursorpos-1]!='<')
    {
        this->textCursor().deletePreviousChar();
        cursorpos--;
    }
    this->blockSignals(true);
    this->textCursor().insertText(tag);
    this->blockSignals(false);
    taghints->setVisible(false);
    autocomplete->runautocomplete(this->toPlainText(),this->textCursor(),this->cursorRect());
}

void CodeEditor::setConfig(const std::shared_ptr<config> &conf)
{
    this->sh->setConfig(conf);
}

void CodeEditor::mousePressEvent(QMouseEvent *e)
{
    taghints->setVisible(false);
    QPlainTextEdit::mousePressEvent(e);
}

void CodeEditor::receivecurrentfilename(QString name)
{
    currentfilename = name;
    emit giveFileNameToSH(name);
}

void CodeEditor::receiveWordWrap(bool wordwrap)
{
    if(wordwrap)
        this->setLineWrapMode(LineWrapMode::WidgetWidth);
    else
        this->setLineWrapMode(LineWrapMode::NoWrap);
}
