#include "codeeditorarea.h"
#include "mainwindow.h"

CodeEditorArea::CodeEditorArea()
{
    this->codeeditor = new CodeEditor();
    this->lna = new LineNumberArea();

    connect(codeeditor, &CodeEditor::fontSizeChanged, lna, &LineNumberArea::handleFontSize);
    connect(codeeditor, &CodeEditor::blockCountVector, lna, &LineNumberArea::onBlockCountVector);
    connect(codeeditor, &CodeEditor::scrolledTo, lna, &LineNumberArea::onScrolledTo);
    connect(lna,&LineNumberArea::selectLine ,codeeditor , &CodeEditor::onSelectLine);
    connect(codeeditor,&QPlainTextEdit::textChanged, this , &CodeEditorArea::onTextChanged);
    connect(this, &CodeEditorArea::giveCurrentFileNameMiddle, codeeditor, &CodeEditor::receivecurrentfilename);
    connect(this, &CodeEditorArea::giveWordWrap, codeeditor, &CodeEditor::receiveWordWrap);

    hlayout = new QHBoxLayout;
    hlayout->addWidget(lna);
    hlayout->addWidget(codeeditor);

    this->setLayout(hlayout);


}

CodeEditorArea::~CodeEditorArea()
{
    delete this->lna;
    delete this->codeeditor;
}

void CodeEditorArea::onTextChanged()
{
    emit codeTextChanged();
    emit newText(this->getText());
}

void CodeEditorArea::receiveCurrentFileNameMiddle(QString name)
{
    emit giveCurrentFileNameMiddle(name);
}

void CodeEditorArea::receiveWordWrapMiddle(bool wordwrap)
{
    emit giveWordWrap(wordwrap);
}

void CodeEditorArea::setText(const QString& text)
{
    this->codeeditor->setPlainText(text);
}

QString CodeEditorArea::getText()
{
    return this->codeeditor->toPlainText();
}

void CodeEditorArea::Cut()
{
    codeeditor->cut();
}

void CodeEditorArea::Copy()
{
    codeeditor->copy();
}

void CodeEditorArea::Paste()
{
    codeeditor->paste();
}

void CodeEditorArea::Delete()
{
    QTextCursor cur = codeeditor->textCursor();
    cur.removeSelectedText();
}

void CodeEditorArea::Undo()
{
    codeeditor->undo();
}

void CodeEditorArea::onConfigChanged(const std::shared_ptr<config>& conf)
{
    this->codeeditor->setConfig(conf);
}
