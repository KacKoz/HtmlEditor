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
    void handleFontSize(int size);

signals:

private:
    void wheelEvent(QWheelEvent *event);

};

#endif // LINENUMBERAREA_H
