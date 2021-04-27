#ifndef CODEEDITORAREA_H
#define CODEEDITORAREA_H

#include <QWidget>
#include <QHBoxLayout>
#include <QMainWindow>
#include "codeeditor.h"
#include "linenumberarea.h"
#include "Configuration.h"

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
    void giveCurrentFileNameMiddle(QString);
    void giveWordWrap(bool);

public slots:

    void onTextChanged();
    void receiveCurrentFileNameMiddle(QString);
    void receiveWordWrapMiddle(bool);
    void onConfigChanged(const std::shared_ptr<config>&);


private:



    QHBoxLayout* hlayout;
    CodeEditor* codeeditor;
    LineNumberArea* lna;
    QMainWindow* parent;
};

#endif // CODEEDITORAREA_H
