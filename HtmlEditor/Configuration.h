#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>
#include <map>

typedef struct
{
    std::map<QString, QString> colors;
    std::map<QString, QString> text;

} config;

#endif // CONFIGURATION_H
