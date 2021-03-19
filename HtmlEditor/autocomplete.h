#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include <QPlainTextEdit>
#include <QListWidget>

class Autocomplete : public QWidget
{
    Q_OBJECT

public:
    void runautocomplete(QString editortext,QTextCursor editorcursor,QRect editorcursorpos);
    //Autocomplete();
signals:
    void closingtag(QString closingtag);
    void sendcursorpos(QRect point);
    void hidelist();
public slots:


private:
    bool islessthan=false;
    QString tag= "";
    //int previouslength =0;
    //QStringList listoftags = {"html","body","div"};
    //QListWidget* taglist;

};

#endif // AUTOCOMPLETE_H
