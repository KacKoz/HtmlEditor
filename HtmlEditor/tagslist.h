#ifndef TAGSLIST_H
#define TAGSLIST_H

#include <QString>
#include <QObject>
#include <QDebug>

template<typename T>
class Node{
public:
    Node(T _data,Node* _sibling=nullptr,Node* _child=nullptr,Node* _parent=nullptr):data(_data),sibling(_sibling),child(_child),parent(_parent){};
    T data;
    Node *sibling,*child,*parent;
};


template<typename T>
class TagsList //: public QObject
{
public:

//    class Node{
//    public:
//        Node(T _data,Node* _sibling=nullptr,Node* _child=nullptr,Node* _parent=nullptr):data(_data),sibling(_sibling),child(_child),parent(_parent){};
//        T data;
//        Node *sibling,*child,*parent;
//    };

//private:
    TagsList(){head=nullptr;}
    ~TagsList(){}
    Node<T>* head;
    void print(Node<T>* node, int x)
    {
        if(!node)
            return;
        QString tab ="";
        for(int i =0;i<x;i++)
            tab+=' ';
        //qDebug()<<tab+node->data;
        print(node->child,++x);
        x--;
        print(node->sibling,x);
    }
    void deleteTagsList(Node<T>* node)
    {
        if(!node)
            return;
        //qDebug()<<"lalalala";
        //qDebug()<<node->data;
        deleteTagsList(node->child);
        deleteTagsList(node->sibling);
        //qDebug()<<node->data;
        delete node;
    }
};

#endif // TAGSLIST_H
