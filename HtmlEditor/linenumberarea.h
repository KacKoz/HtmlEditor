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

private:
    void wheelEvent(QWheelEvent *event);
    QString _lineNumbers = "1\n";
    int _lines = 1;
};

#endif // LINENUMBERAREA_H
