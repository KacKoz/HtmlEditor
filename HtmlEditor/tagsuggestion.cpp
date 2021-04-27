#include "tagsuggestion.h"
#include <QDebug>
#include <QPlainTextEdit>
#include <exception>
#include <QMessageBox>


Tagsuggestion::Tagsuggestion(QPlainTextEdit* giveparent)
{
    try
    {
        _tags =new TagsTree("tags.txt");
        this->addItems(_tags->taglist);
    }
    catch(std::exception &e)
    {
        qDebug()<<e.what();
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Error");
        msgBox.setText(e.what());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        switch (ret)
        {
          case QMessageBox::Ok:
              msgBox.close();
              break;
          default:
              msgBox.close();
              break;
        }
        exit(-1);
    }

    parent = giveparent;
    this->setParent(parent);
    //emit askfortaglist();
    //receivetaglist(taglist);
    //this->addItems(_tags->taglist);
    this->setFixedSize(100,107);

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

Tagsuggestion::~Tagsuggestion()
{
    delete _tags;
}

void Tagsuggestion::movelist(QRect point,int tagrow)

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

    delete additionalpoint;
    //this->setVisible(true);//sprawdzic jak dziala to w vs code czyli klikniecie esc plus nie wyszukuje u!!!!!
    movetoitem(tagrow);

}

void Tagsuggestion::hidelist()
{
    this->setVisible(false);
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


