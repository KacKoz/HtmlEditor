#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include <QPlainTextEdit>

class Autocomplete : public QObject
{
    Q_OBJECT

public:
    Autocomplete(QPlainTextEdit* editor);
    //Autocomplete();
signals:
    void closingtag(QString closingtag);
public slots:
     void ontextchanged();

private:
    QPlainTextEdit* editor;
    bool islessthan=false;
    QString tag= "";

};

#endif // AUTOCOMPLETE_H
