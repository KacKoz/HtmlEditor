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

<<<<<<< HEAD
=======

>>>>>>> Szymon
class TagsTree: public QObject
{
     Q_OBJECT

public slots:
    //void givetaglist();
    void getFirstStartingWith(const QString& text);

public:
    TagsTree(const QString& fileName = "");
    ~TagsTree();

    //int getFirstStartingWith(const QString& text);
    bool isInTree(const QString& tagName);
    QStringList taglist;
<<<<<<< HEAD
=======

signals:
    void giverow(int);
    void print(node* n = nullptr,int wc = 0);
>>>>>>> Szymon

signals:
    void giverow(int);

private:
    bool _readTagsFromFile(const QString& fileName);
    void _addNode(const QString& tagName, int row, node** cur);
    void _createOptimalFromSortedVector(const std::vector<QString> v, int l, int r);
    void _deleteTree(node *ptr);
<<<<<<< HEAD
=======

>>>>>>> Szymon
    void _returnNodes(node* treeNode);
    node* _head = nullptr;
//    node* _head = nullptr;
//    QStringList taglist;


};

#endif // TAGSTREE_H
