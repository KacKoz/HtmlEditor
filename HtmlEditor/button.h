#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class Button : public QPushButton
{
    Q_OBJECT

public:
    Button(QString text);

signals:
    void askforcurrentdir();

public slots:
    void receivecurrentdir(QString path);
    void makedir();
    void makefile();

private:
    QString currentdir="";

};

#endif // BUTTON_H
