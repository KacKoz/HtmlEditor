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
    Node<T>* head;
    void print(Node<T>* node)
    {
        if(!node)
            return;
        qDebug()<<node->data;
        print(node->child);
        Node<T>* p = node->sibling;
        while(p)
        {
            print(p);
            p=p->sibling;
        }
    }
};

#endif // TAGSLIST_H
