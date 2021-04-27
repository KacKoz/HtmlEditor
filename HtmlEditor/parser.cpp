#include "parser.h"
#include <QDebug>
#include <ctype.h>
#include <QMessageBox>
#include "tagslist.h"

Parser::Parser()
{
    parserTree.setColumnCount(1);
    parserTree.setBaseSize(300,300);
    parserTree.setWindowTitle("DOM Tree");
    parserTree.setHeaderHidden(true);

}

void Parser::parsuj(QString text)
{
    list.head=nullptr;
    try
    {
        _tags = new TagsTree("selfclosing.txt");
    }
    catch (QString s)
    {
        qDebug() << s;
        return;
    }

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
                if(current)
                    current = current->parent;
                else
                {
//                    qDebug()<<"Koniec";
//                    break;
                    throw 0;
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
                    if(!current)
                    {
                        list.head->sibling = new Node<QString>(tag);
                        current = list.head->sibling;
                    }
                    else
                    {
                        if(current->data!="script"){
                            if(!current->child)
                            {
                                current->child = new Node<QString>(tag,nullptr,nullptr,current);
                                if(!_tags->isInTree(tag))
                                    current = current->child;
                            }
                            else
                            {
    //                            current->child->sibling = new Node<QString>(tag,current->child->sibling,nullptr,current);
    //                            if(!_tags->isInTree(tag))
    //                                current = current->child->sibling;;
                               current = current->child;
                               while(current->sibling)
                               {
                                    current=current->sibling;
                               }
                               current->sibling = new Node<QString>(tag,nullptr,nullptr,current->parent);
                               if(!_tags->isInTree(tag))
                                   current = current->sibling;
                               else
                                   current = current->parent;
                            }
                        }
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
        throw 1;
        //qDebug()<<"Zly kod";
    //list.print(list.head);
    //qDebug()<<"/////////////////////////";
}

void Parser::fillTree(Node<QString>* node)
{
    if(!node)
        return;
    _currentTreeItem = new QTreeWidgetItem(_currentTreeItem);
    _currentTreeItem->setText(0,node->data);
    if(_currentTreeItem->parent()==nullptr)
    {
        //qDebug()<<node->data;
        parserTree.addTopLevelItem(_currentTreeItem);
        //qDebug()<<node->data;
    }
    fillTree(node->child);
    _currentTreeItem = _currentTreeItem->parent();
    fillTree(node->sibling);
//    _currentTreeItem = new QTreeWidgetItem();
//    qDebug()<<node->data;
//    _currentTreeItem->setText(0,node->data);
//    _parserTree.addTopLevelItem(_currentTreeItem);
}

void Parser::lackoftag(QString whichTag)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("Tag is missing");
    msgBox.setText(whichTag+" tag is missing");
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
}

