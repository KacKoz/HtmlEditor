#include "parser.h"
#include <QDebug>
#include <ctype.h>

void Parser::parsuj(QString text)
{
    list.head=nullptr;
    Node<QString> *current= nullptr;//, *parent=nullptr;
    bool isLessThan = false, wasSpace=false, wasQuotation=false, wasClosing = false;
    QString tag="";
    for(int i=0;i<text.length();i++)
    {
//        if(text[i]=='"')
//        {
//            wasQuotation=!wasQuotation;
//            continue;
//        }
//        else
//        {
//            if(wasQuotation)
//                continue;
//        }
        if(text[i]=='<')
        {
            isLessThan = true;
            wasSpace=false;
            tag="";
            continue;
        }
        if(isLessThan and text[i]==' ')
        {
            wasSpace=true;
            continue;
        }
        if(isLessThan and text[i]=='>')
        {
            if(tag[0]=='/')
            {
                //wasClosing = true;
                if(current and current->parent)
                    current = current->parent;
                else
                {
                    qDebug()<<"Koniec";
//                    return;
                }
            }
            else
            {
                if(list.head==nullptr)
                {
                    list.head = new Node<QString>(tag);
                    current = list.head;
                }
                else
                {
                    if(!current->child)
                    {
                        current->child = new Node<QString>(tag,nullptr,nullptr,current);
                        current = current->child;
                    }
                    else
                    {
                        current->child->sibling = new Node<QString>(tag,current->child->sibling,nullptr,current);
                        current = current->child->sibling;
                    }
                }
            }
            isLessThan=false;
            wasSpace=false;
            tag="";
            continue;
        }
        if(isLessThan and !wasSpace)
        {
            tag+=text[i];
            if(tag[0]=='!')
            {
                isLessThan=false;
                wasSpace=false;
                tag="";
            }
        }
    }
    if(current)
        qDebug()<<"Zly kod";
    list.print(list.head);
}
