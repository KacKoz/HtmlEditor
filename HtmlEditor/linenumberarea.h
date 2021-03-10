#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>
#include <QPlainTextEdit>

#include <vector>

#include <QDebug>

class LineNumberArea : public QPlainTextEdit//QWidget
{
    Q_OBJECT
public:
    explicit LineNumberArea(QWidget *parent = nullptr);

public slots:
    void handleFontSize(int size);
    void onShouldChangeSize();
    void onBlockCountVector(std::vector<int>*);
    void onScrolledTo(int offset);


signals:
    void shouldChangeSize();
    void selectLine(int line);

private:
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    QString _lineNumbers = "01\n";
    int _lines = 1;
};

#endif // LINENUMBERAREA_H
