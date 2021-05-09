#ifndef XMLREADER_H
#define XMLREADER_H

#include "Configuration.h"
#include "RapidXML/rapidxml-1.13/rapidxml.hpp"
#include "RapidXML/rapidxml-1.13/rapidxml_print.hpp"


#include <string>
#include <memory>


class XMLReader
{
public:

    static std::shared_ptr<config> makeConfigFromFile(const char* filename);
    static void saveConfigToFile(const char* filename, std::shared_ptr<config>&);

private:
    static std::shared_ptr<char[]> fileToChar(const char* filename);
    static void getColors(std::shared_ptr<config>&, rapidxml::xml_node<>*);
    static void addColors(rapidxml::xml_node<>*, rapidxml::xml_document<>&, std::shared_ptr<config>&);
};

#endif // XMLREADER_H
