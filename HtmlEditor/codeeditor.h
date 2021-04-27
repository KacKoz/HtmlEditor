#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include "autocomplete.h"
#include "tagsuggestion.h"
#include "syntaxhighlighter.h"


#include <QPlainTextEdit>

#include <vector>
#include <QPair>

#include "tagstree.h"
#include "Configuration.h"

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEditor();
    ~CodeEditor();

    void setConfig(const std::shared_ptr<config>&);

signals:
    void fontSizeChanged(int);
    void blockCountVector(std::vector<int>*);
    void scrolledTo(int);
    void sizechanged(QWidget*);


public slots:
    void onSelectLine(int line);
    void writesuggestion(QString tag);


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

    TagsTree* _tags = nullptr;
};

#endif // CODEEDITOR_H
