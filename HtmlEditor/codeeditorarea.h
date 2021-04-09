#ifndef CODEEDITORAREA_H
#define CODEEDITORAREA_H

#include <QWidget>
#include <QHBoxLayout>
#include "codeeditor.h"
#include "linenumberarea.h"

class CodeEditorArea : public QWidget
{
    Q_OBJECT

public:
    CodeEditorArea();
    ~CodeEditorArea();

    void setText(const QString& text);
    QString getText();

    void Cut();
    void Copy();
    void Paste();
    void Delete();
    void Undo();

signals:

    void codeTextChanged();
    void newText(const QString& s);

public slots:

    void onTextChanged();


private:



    QHBoxLayout* hlayout;
    CodeEditor* codeeditor;
    LineNumberArea* lna;
};

#endif // CODEEDITORAREA_H
