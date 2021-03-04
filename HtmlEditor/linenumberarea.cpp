#include "linenumberarea.h"


LineNumberArea::LineNumberArea(QWidget *parent) : QPlainTextEdit/*QWidget*/(parent)
{
    QSizePolicy sp;
    sp.setHorizontalPolicy(QSizePolicy::Fixed);
    sp.setVerticalPolicy(QSizePolicy::Expanding);
    this->setSizePolicy(sp);
    this->setMaximumSize(20, 10000);
    QPalette pal;
    pal.setColor(QPalette::Text, Qt::green);
    pal.setColor(QPalette::Base, QRgb(0x5a5a5a));
    this->setPalette(pal);
    this->setReadOnly(true);
    this->setTextInteractionFlags(Qt::NoTextInteraction);
    this->appendPlainText("1\n");

}