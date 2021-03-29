#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include <QPlainTextEdit>
#include <QListWidget>
#include "tagstree.h"

#include "tagstree.h"


class Autocomplete : public QWidget
{
    Q_OBJECT

public:
    void runautocomplete(QString editortext,QTextCursor editorcursor,QRect editorcursorpos);
<<<<<<< HEAD
=======

>>>>>>> Szymon
    Autocomplete();
signals:
    void closingtag(QString closingtag);
    void sendcursorpos(QRect point,int tagrow);
    void hidelist();
    void showlist();
    void askforrow(QString tag);
public slots:
    void receiverow(int row);
<<<<<<< HEAD
=======




>>>>>>> Szymon

private:
    bool islessthan=false;
    QString tag= "";
<<<<<<< HEAD
    int rowoftag;
    TagsTree* _tags;
    //int previouslength =0;
    //QStringList listoftags = {"html","body","div"};
    //QListWidget* taglist;
=======

    int rowoftag;
    TagsTree* _tags;

>>>>>>> Szymon

};

#endif // AUTOCOMPLETE_H
