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
    void directorychanged(QString name);

public slots:
    void receivecurrentdir(QString path);
    void makedir();
    void makefile();
    void movetoparent();

private:
    void infofirstopen(QString fileordir);
    void infoinvalidname(QString fileordir);
    QString currentdir="";
    char forbiddennames[9] = {'/','\\','"','?',':','*','|','<','>'};

};

#endif // BUTTON_H
