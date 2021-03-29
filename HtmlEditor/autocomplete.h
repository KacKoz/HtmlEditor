#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include <QPlainTextEdit>
#include <QListWidget>
#include "tagstree.h"

class Autocomplete : public QWidget
{
    Q_OBJECT

public:
    void runautocomplete(QString editortext,QTextCursor editorcursor,QRect editorcursorpos);
    Autocomplete();
signals:
    void closingtag(QString closingtag);
    void sendcursorpos(QRect point,int tagrow);
    void hidelist();
    void showlist();
    void askforrow(QString tag);
public slots:
    void receiverow(int row);

private:
    bool islessthan=false;
    QString tag= "";
    int rowoftag;
    TagsTree* _tags;
    //int previouslength =0;
    //QStringList listoftags = {"html","body","div"};
    //QListWidget* taglist;

};

#endif // AUTOCOMPLETE_H
