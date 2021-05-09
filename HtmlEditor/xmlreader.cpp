#include "xmlreader.h"


#include <fstream>
#include <iostream>
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

void XMLReader::saveConfigToFile(const char *filename, std::shared_ptr<config>& config)
{
    rapidxml::xml_document<> document;
    rapidxml::xml_node<>* config_node = document.allocate_node(rapidxml::node_type::node_element, "config");
    addColors(config_node, document, config);

    //Tutaj dodac konfiguracje z innych zakladek w ten sam sposob

    document.append_node(config_node);

    std::cout << "\n" << (int)config_node->first_node()->first_node()->value()[0] << std::endl;

    std::ofstream file(filename);
   // std::cout << "Dokument:\n" << document << std::endl;
    file << document;
    file.close();
}

void XMLReader::addColors(rapidxml::xml_node<> *config_node, rapidxml::xml_document<> &document, std::shared_ptr<config>& config)
{
    rapidxml::xml_node<>* colors_node = document.allocate_node(rapidxml::node_type::node_element, "colors");
    for(auto& el: config->colors)
    {
        char *tmp1 = document.allocate_string(el.first.toStdString().c_str());
        char *tmp2 = document.allocate_string(el.second.toStdString().c_str());
        colors_node->append_node(document.allocate_node(rapidxml::node_type::node_element, //Typ elementu
                                                        tmp1, //Nazwa tagu
                                                        tmp2)); //zawartosc tagu(hex color)
    }

    config_node->append_node(colors_node);
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
