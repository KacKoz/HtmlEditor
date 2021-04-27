#include "codeeditorarea.h"

CodeEditorArea::CodeEditorArea()
{
    this->codeeditor = new CodeEditor();
    this->lna = new LineNumberArea();

    connect(codeeditor, &CodeEditor::fontSizeChanged, lna, &LineNumberArea::handleFontSize);
    connect(codeeditor, &CodeEditor::blockCountVector, lna, &LineNumberArea::onBlockCountVector);
    connect(codeeditor, &CodeEditor::scrolledTo, lna, &LineNumberArea::onScrolledTo);
    connect(lna,&LineNumberArea::selectLine ,codeeditor , &CodeEditor::onSelectLine);
    connect(codeeditor,&QPlainTextEdit::textChanged, this , &CodeEditorArea::onTextChanged);

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
    qDebug() << "Received settings";
    this->codeeditor->setConfig(conf);
}
