#include "tagsuggestion.h"
#include <QDebug>

<<<<<<< HEAD
=======

>>>>>>> Szymon
Tagsuggestion::Tagsuggestion(QPlainTextEdit* giveparent,QStringList taglist)
{
    parent = giveparent;
    this->setParent(parent);
    //emit askfortaglist();
    //receivetaglist(taglist);
    this->addItems(taglist);
    this->setFixedSize(100,107);
<<<<<<< HEAD
=======

>>>>>>> Szymon
    QPalette pal;
    pal.setColor(QPalette::Text, Qt::black);
    pal.setColor(QPalette::Base, Qt::white);
    //this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->show();
    this->setVisible(false);
    parentviewport = parent->viewport();

    connect(this,&Tagsuggestion::itemClicked,this,&Tagsuggestion::onListItemClicked);
}

void Tagsuggestion::movelist(QRect point,int tagrow)
<<<<<<< HEAD
=======

>>>>>>> Szymon
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
<<<<<<< HEAD
    delete additionalpoint;
    //this->setVisible(true);//sprawdzic jak dziala to w vs code czyli klikniecie esc plus nie wyszukuje u!!!!!
    movetoitem(tagrow);
=======

    delete additionalpoint;
    //this->setVisible(true);//sprawdzic jak dziala to w vs code czyli klikniecie esc plus nie wyszukuje u!!!!!
    movetoitem(tagrow);

>>>>>>> Szymon
}

void Tagsuggestion::hidelist()
{
    this->setVisible(false);
}
void Tagsuggestion::showlist()
{
    this->setVisible(true);
}

void Tagsuggestion::showlist()
{
    this->setVisible(true);
}


void Tagsuggestion::parentchangedsize(QWidget* viewport)
{
    parentviewport = viewport;
}

void Tagsuggestion::movetoitem(int row)
{
    //qDebug()<<row;
    //qDebug()<<this->count();
    QListWidgetItem* scrollto;
    if(row>=0)
    {
        if(selectedrow>row)
        {
             scrollto = this->item(row);
        }
        else
        {
            if((row+5)<this->count())
            {
                scrollto = this->item(row+5);
            }
            else
            {
                scrollto = this->item(this->count()-1);
            }
        }
        QListWidgetItem* select = this->item(row);
        select->setSelected(true);
        this->scrollToItem(scrollto);
        selectedrow=row;
    }
    else
    {
        this->setVisible(false);
    }

    //this->scroll(0,4);
}

void Tagsuggestion::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Down)
    {
        if(selectedrow<this->count()-1)
        {
            QListWidgetItem* select = this->item(selectedrow+1);
            selectedrow++;
            select->setSelected(true);
            this->scrollToItem(select);
        }
    }
    else if(event->key()==Qt::Key_Up)
    {
        if(selectedrow>=1)
        {
            QListWidgetItem* select = this->item(selectedrow-1);
            selectedrow--;
            select->setSelected(true);
            this->scrollToItem(select);
        }
    }
    else if(event->key()==Qt::Key_Tab)
    {
        if(selectedrow>-1)
        {
            emit sendsuggestion(this->selectedItems()[0]->text());
        }
    }
    parent->setFocus();
}

void Tagsuggestion::onListItemClicked(QListWidgetItem* item)
{
    emit sendsuggestion(item->text());
}

<<<<<<< HEAD
=======

>>>>>>> Szymon
