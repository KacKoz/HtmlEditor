#include "choosecolorbutton.h"

#include <QColorDialog>
#include <QDebug>

ChooseColorButton::ChooseColorButton(QWidget *parent)
    : QPushButton(parent)
{
    connect(this, &QPushButton::clicked, this, &ChooseColorButton::onClick);
}

void ChooseColorButton::setColor(const QString &hexCol)
{
    this->setText(hexCol);

    QPixmap px(20,20);
    QColor col;

    col.setNamedColor(hexCol);
    px.fill(col);
    this->setIcon(QIcon(px));
}

QString ChooseColorButton::getColor()
{
    return this->text();
}

void ChooseColorButton::onClick()
{
    _isOpen = true;

    QColor col;
    col.setNamedColor(this->text());
    col = QColorDialog::getColor(col);

    this->setColor(col.name());

}
