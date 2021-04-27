#ifndef CHOOSECOLORBUTTON_H
#define CHOOSECOLORBUTTON_H

#include <QPushButton>
#include <QWidget>

class ChooseColorButton : public QPushButton
{
    Q_OBJECT
public:
    ChooseColorButton(QWidget *parent);

    void setColor(const QString &hexCol);
    QString getColor();

private slots:
    void onClick();

private:
    bool _isOpen = false;
};

#endif // CHOOSECOLORBUTTON_H
