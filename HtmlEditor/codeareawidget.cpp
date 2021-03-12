#include "codeareawidget.h"

CodeAreaWidget::CodeAreaWidget(QWidget *parent) : QWidget(parent)
{
    codeeditor = new CodeEditor();
    lna = new LineNumberArea();

    horizontallayout = new QHBoxLayout;
    horizontallayout->addWidget(codeeditor);
    horizontallayout->addWidget(lna);

    connect(codeeditor, &CodeEditor::blockCountVector, lna, &LineNumberArea::onBlockCountVector);
    connect(codeeditor, &CodeEditor::scrolledTo, lna, &LineNumberArea::onScrolledTo);
    connect(lna,&LineNumberArea::selectLine ,codeeditor , &CodeEditor::onSelectLine);
    connect(codeeditor, &CodeEditor::fontSizeChanged, lna, &LineNumberArea::handleFontSize);

    this->setLayout(horizontallayout);
}

CodeAreaWidget::~CodeAreaWidget()
{
    delete lna;
    delete codeeditor;
}
