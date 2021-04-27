#ifndef XMLREADER_H
#define XMLREADER_H

#include "Configuration.h"
#include "RapidXML/rapidxml-1.13/rapidxml.hpp"

#include <string>
#include <memory>


class XMLReader
{
public:

    static std::shared_ptr<config> makeConfigFromFile(const char* filename);

private:
    static std::shared_ptr<char[]> fileToChar(const char* filename);
    static void getColors(std::shared_ptr<config>&, rapidxml::xml_node<>*);
};

#endif // XMLREADER_H
