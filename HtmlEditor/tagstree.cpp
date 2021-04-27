#include "tagstree.h"
#include <QDebug>

#include <utility>



TagsTree::TagsTree(const QString& fileName)
{
    if(!this->_readTagsFromFile(fileName))
    {
        throw std::runtime_error("Could not find: " + fileName.toStdString());
    }
    else
    {
        qDebug() << "Succesfully read tags from: " << fileName;
    }

    _returnNodes(_head);
    //qDebug()<<taglist;

}

TagsTree::~TagsTree()
{
    _deleteTree(_head);
}


void TagsTree::getFirstStartingWith(const QString& text)
{
    node* cur = _head;
    int found = -1;

    while(cur)
    {
        if(cur->tag.startsWith(text, Qt::CaseInsensitive))
        {

             found = cur->row;
        }

        if(QString::compare(text, cur->tag, Qt::CaseInsensitive) > 0)
        {
            cur = cur->right;
        }
        else
        {
            cur = cur->left;
        }

    }

    emit giverow(found);

}

bool TagsTree::isInTree(const QString& tagName)
{
    node* cur = _head;

    while(cur)
    {
        int res = QString::compare(tagName, cur->tag, Qt::CaseInsensitive);
        if(res == 0)
        {
            return true;
        }
        else
        {
            cur = res > 0 ? cur->right : cur->left;
        }
    }

    return false;
}

bool TagsTree::_readTagsFromFile(const QString& fileName)
{
    QFile f(fileName);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&f);
    QString line;
    std::vector<QString> v;
    for(int i=0; !in.atEnd(); i++)
    {
        line = in.readLine();
        line = line.simplified();
        v.push_back(line);
    }

    std::sort(v.begin(), v.end());
    _createOptimalFromSortedVector(v, 0, v.size() - 1);


    return true;
}

void TagsTree::_createOptimalFromSortedVector(const std::vector<QString> v, int l, int r)
{
    if(r-l < 2)
    {
        _addNode(v[l], l, &this->_head);
        _addNode(v[r], r, &this->_head);
        return;
    }

    _addNode(v[(l+r)/2], (l+r)/2, &this->_head);
    _createOptimalFromSortedVector(v, l, ((l+r)/2) - 1);
    _createOptimalFromSortedVector(v, ((l+r)/2) + 1, r);
}

void TagsTree::_addNode(const QString& tagName, int row, node** cur)
{
    if(*cur == nullptr)
    {
        *cur = new node{tagName, row, nullptr, nullptr};
        return;
    }

    if((*cur)->tag == tagName) return;

    if(QString::compare(tagName, (*cur)->tag) > 0)
    {
        this->_addNode(tagName, row, &((*cur)->right));
    }
    else
    {
        this->_addNode(tagName, row, &((*cur)->left));
    }
}

void TagsTree::_deleteTree(node* ptr)
{
    if(ptr->left) _deleteTree(ptr->left);
    if(ptr->right) _deleteTree(ptr->right);

    delete ptr;
}


void TagsTree::_returnNodes(node* treeNode)
{
    if(treeNode==NULL)
        return;
    _returnNodes(treeNode->left);
    //qDebug()<<treeNode->tag;
    taglist<<treeNode->tag;
    _returnNodes(treeNode->right);
}

//void TagsTree::givetaglist()
//{
//    emit sendtaglist(taglist);
//}


