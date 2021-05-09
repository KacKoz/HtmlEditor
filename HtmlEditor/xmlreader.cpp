#include "xmlreader.h"

#include <fstream>
#include <QDebug>
#include <stdexcept>


std::shared_ptr<config> XMLReader::makeConfigFromFile(const char* filename)
{
    std::shared_ptr<char[]> xmlContext;

    try
    {
        xmlContext = fileToChar(filename);
    }
    catch(std::exception& e)
    {
        qDebug() << "Blad czytania pliku XML";
        qDebug() << e.what();
        return nullptr;
    }

    rapidxml::xml_document<> document;



    try
    {
        document.parse<0>(xmlContext.get());
    }
    catch (const rapidxml::parse_error& e)
    {
         qDebug() << "Blad parsowania";
         qDebug() << e.what() << " in: " << e.where<char>();
         return nullptr;
    }


    rapidxml::xml_node<>* n;
    n = document.first_node();

    if(!strcmp(n->name(), "config"))
    {
        n = n->first_node();
    }
    else
    {
        throw std::runtime_error("No config tag");
    }

    std::shared_ptr<config> conf = std::make_shared<config>();


    getColors(conf, n);

//    if(!strcmp(n->name(), "colors"))
//    {
//        n = n->first_node();
//        qDebug()<<n->name();
//    }
//    else
//    {
//        throw std::runtime_error("No colors tag");
//    }

    getText(conf, n->next_sibling());

    return conf;
}

void XMLReader::getColors(std::shared_ptr<config>& conf,
                          rapidxml::xml_node<>* node)
{
    node = node->first_node();
    if(!node)
    {
        throw std::runtime_error("No colors tag in XML");
    }
    while(node)
    {
        conf->colors[node->name()] = node->value();
        node = node->next_sibling();
    }
}

void XMLReader::getText(std::shared_ptr<config>& conf,
                          rapidxml::xml_node<>* node)
{
    node = node->first_node();
    if(!node)
    {
        throw std::runtime_error("No text tag in XML");
    }

    while(node)
    {
        conf->text[node->name()] = node->value();
        node = node->next_sibling();
    }
}

std::shared_ptr<char[]> XMLReader::fileToChar(const char* filename)
{
    std::ifstream file(filename);
    if(!file)
    {
        throw std::runtime_error(std::string(filename) + " not found!");
    }

    file.seekg(0, file.end);
    const std::streampos fileSize = file.tellg();
    file.seekg(0);

    std::shared_ptr<char[]> fileContext(new char[fileSize + static_cast<std::streampos>(1)]);
    file.read(fileContext.get(), fileSize);
    file.close();

    return fileContext;
}
