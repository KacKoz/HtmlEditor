#include "tagsuggestion.h"
#include <QDebug>

Tagsuggestion::Tagsuggestion(QPlainTextEdit* parent)
{
    this->setParent(parent);
    this->addItem("html");
    this->addItem("body");
    this->addItem("div");
    this->setFixedSize(100,100);
    QPalette pal;
    pal.setColor(QPalette::Text, Qt::black);
    pal.setColor(QPalette::Base, Qt::white);
    //this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->show();
    this->setVisible(false);
    parentviewport = parent->viewport();
}

void Tagsuggestion::movelist(QRect point)
{
    int x=0,y=0;
    QFont f = this->font();
    int size = f.pointSize();
    if(point.bottomRight().y()>parentviewport->size().height()/2)
    {
        y=-100-size;
    }
    if(point.bottomRight().x()>parentviewport->size().width()/2)
    {
        x=-100;
    }
    QPoint* additionalpoint = new QPoint(x,y);
    this->move(point.bottomRight()+*additionalpoint);
    this->setVisible(true);
}

void Tagsuggestion::hidelist()
{
    this->setVisible(false);
}

void Tagsuggestion::parentchangedsize(QWidget* viewport)
{
    parentviewport = viewport;
}
