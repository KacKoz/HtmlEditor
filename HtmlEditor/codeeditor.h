#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include "autocomplete.h"
#include "tagsuggestion.h"
#include "syntaxhighlighter.h"


#include <QPlainTextEdit>

#include <vector>
#include <QPair>

#include "tagstree.h"

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEditor();
    QString currentfilename ="";

signals:
    void fontSizeChanged(int);
    void blockCountVector(std::vector<int>*);
    void scrolledTo(int);
    void sizechanged(QWidget*);
    void giveFileNameToSH(QString);

public slots:
    void onSelectLine(int line);
    void writesuggestion(QString tag);
    void receivecurrentfilename(QString name);
    void receiveWordWrap(bool);

private slots:
    void onBlockCountChange(int count);
    void onUpdateRequest();
    void onCursorMoved();
    void insertclosingtag(QString closingtag);
    void ontextchanged();

private:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *e);
    Autocomplete* autocomplete;
    Tagsuggestion* taghints;
    void resizeEvent(QResizeEvent *event);
    void wheelEvent(QWheelEvent *event);
    void highlightCurrentLine();
    void setTextCursorPosition(QTextCursor& tc, int line);

    std::vector<int> _linesInBlock;
    QTextEdit::ExtraSelection _selection;
    QList<QTextEdit::ExtraSelection> _extraSelections;
    syntaxHighlighter* sh;

};

#endif // CODEEDITOR_H
