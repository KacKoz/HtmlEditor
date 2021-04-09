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
    void parsuj(QString text);
    void lackoftag(QString whichTag);
    Parser();
    void fillTree(Node<QString>* node);
    QTreeWidget parserTree;
    TagsList<QString> list;
private:
    TagsTree* _tags;
    QTreeWidgetItem* _currentTreeItem = nullptr;
};


#endif // PARSER_H
