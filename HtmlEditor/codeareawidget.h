#ifndef CODEAREAWIDGET_H
#define CODEAREAWIDGET_H

#include <QWidget>
#include "codeeditor.h"
#include "linenumberarea.h"
#include <QHBoxLayout>

class CodeAreaWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CodeAreaWidget(QWidget *parent = nullptr);
    ~CodeAreaWidget();

protected slots:
    void onCodeEditorTextChanged();


signals:
    void codeTextChanged();



private:
    CodeEditor* codeeditor;
    LineNumberArea* lna;
    QHBoxLayout* horizontallayout;
};

#endif // CODEAREAWIDGET_H
