#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <stack>
#include <QTreeWidget>
#include "tagslist.h"
#include "tagstree.h"

class Parser
{

public:
    Parser();
    ~Parser();
    void parsuj(QString text);
    void lackoftag(QString whichTag);
    void fillTree(Node<QString>* node);
    QTreeWidget parserTree;
    TagsList<QString> list;
private:
    TagsTree* _tags;
    QTreeWidgetItem* _currentTreeItem = nullptr;
};


#endif // PARSER_H
