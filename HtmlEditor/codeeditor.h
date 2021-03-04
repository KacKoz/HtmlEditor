#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEditor();


signals:
    void fontSizeChanged(int size);


private slots:
    void on_CodeEditor_textChanged();

private:
    void wheelEvent(QWheelEvent *event);
};

#endif // CODEEDITOR_H
