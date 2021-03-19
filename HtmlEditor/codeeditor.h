#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include "autocomplete.h"
#include "tagsuggestion.h"

#include <QPlainTextEdit>

#include <vector>
#include <QPair>

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEditor();


signals:
    void fontSizeChanged(int size);
    void blockCountVector(std::vector<int>*);
    void scrolledTo(int offset);
    void sizechanged(QWidget* viewport);

public slots:
    void onSelectLine(int line);

private slots:
    void onBlockCountChange(int count);
    void onUpdateRequest();
    void onCursorMoved();
    void insertclosingtag(QString closingtag);
    void ontextchanged();

private:
    Autocomplete* autocomplete;
    Tagsuggestion* taghints;
    void resizeEvent(QResizeEvent *event);
    void wheelEvent(QWheelEvent *event);
    void highlightCurrentLine();
    void setTextCursorPosition(QTextCursor& tc, int line);

    std::vector<int> _linesInBlock;
    QTextEdit::ExtraSelection _selection;
    QList<QTextEdit::ExtraSelection> _extraSelections;


};

#endif // CODEEDITOR_H
