#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <stack>
#include "tagslist.h"

class Parser
{

public:
    void parsuj(QString text);

private:
    TagsList<QString> list;

};


#endif // PARSER_H
