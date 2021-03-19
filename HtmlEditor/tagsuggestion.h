#ifndef TAGSUGGESTION_H
#define TAGSUGGESTION_H

#include <QPlainTextEdit>
#include <QListWidget>

class Tagsuggestion : public QListWidget
{
    Q_OBJECT

public:
    Tagsuggestion(QPlainTextEdit* parent);
public slots:
    void movelist(QRect point);
    void hidelist();
    void parentchangedsize(QWidget* viewport);

signals:

private:
    QWidget* parentviewport;

};


#endif // TAGSUGGESTION_H
