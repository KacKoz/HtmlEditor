#ifndef CODEEDITOR_H
#define CODEEDITOR_H

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


private slots:
    void onBlockCountChange(int count);

private:
    void wheelEvent(QWheelEvent *event);

    std::vector<int> _linesInBlock;

};

#endif // CODEEDITOR_H
