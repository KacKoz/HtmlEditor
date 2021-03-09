#include "codeeditor.h"
#include <QPalette>
#include <windows.h>
#include <winuser.h>
#include <QDebug>
#include <QTextBlock>
#include <QScrollBar>

#include <iostream>

CodeEditor::CodeEditor()
{
    QPalette pal;
    pal.setColor(QPalette::Text, Qt::white);
    pal.setColor(QPalette::Base, QRgb(0x5a5a5a));
    //this->setAutoFillBackground(true);
    this->setPalette(pal);
    //this->setLineWrapMode(LineWrapMode::NoWrap);

    connect(this, &QPlainTextEdit::blockCountChanged, this, &CodeEditor::onBlockCountChange);
    connect(this, &QPlainTextEdit::updateRequest, this, &CodeEditor::onUpdateRequest);
    connect(this, &QPlainTextEdit::cursorPositionChanged, this, &CodeEditor::onCursorMoved);

}

void CodeEditor::wheelEvent(QWheelEvent *event)
{
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() - (event->angleDelta().y()/25));
    emit scrolledTo(this->verticalScrollBar()->value());

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
}

void CodeEditor::onCursorMoved()
{
    emit blockCountChanged(_linesInBlock.size());
}
