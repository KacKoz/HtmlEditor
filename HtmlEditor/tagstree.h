#ifndef TAGSTREE_H
#define TAGSTREE_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <vector>


struct node
{
    QString tag;
    int row;

    node* left;
    node* right;
};

class TagsTree
{
public:
    TagsTree(const QString& fileName = "");
    ~TagsTree();

    int getFirstStartingWith(const QString& text);
    bool isInTree(const QString& tagName);


private:
    bool _readTagsFromFile(const QString& fileName);
    void _addNode(const QString& tagName, int row, node** cur);
    void _createOptimalFromSortedVector(const std::vector<QString> v, int l, int r);
    void _deleteTree(node *ptr);
    node* _head = nullptr;


};

#endif // TAGSTREE_H
