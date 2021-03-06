#ifndef TAGSUGGESTION_H
#define TAGSUGGESTION_H

#include <QPlainTextEdit>
#include <QListWidget>
#include "tagstree.h"

class Tagsuggestion : public QListWidget
{
    Q_OBJECT

public:

    Tagsuggestion(QPlainTextEdit* parent);
    ~Tagsuggestion();
    void keyPressEvent(QKeyEvent *event);
public slots:
    void movelist(QRect point,int tagrow);
    void hidelist();
    void showlist();
    void parentchangedsize(QWidget* viewport);
    //void receivetaglist(QStringList taglist);
private slots:
    void onListItemClicked(QListWidgetItem* item);

signals:
    void sendsuggestion(QString);
private:
    void movetoitem(int row);
    QWidget* parentviewport;
    QPlainTextEdit* parent;
    QStringList taglist;
    int selectedrow=-1;
    TagsTree* _tags = nullptr;

};


#endif // TAGSUGGESTION_H
