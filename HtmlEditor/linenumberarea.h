#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>
#include <QPlainTextEdit>

class LineNumberArea : public QPlainTextEdit//QWidget
{
    Q_OBJECT
public:
    explicit LineNumberArea(QWidget *parent = nullptr);

public slots:
    //void setFontSize(int size);

signals:

};

#endif // LINENUMBERAREA_H
