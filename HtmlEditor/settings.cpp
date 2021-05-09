#include "settings.h"
#include "xmlreader.h"

#include <QDebug>
#include <iostream>



Settings::Settings(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("Settings");


    layout = new QVBoxLayout();
    this->setLayout(layout);
    tab = new QTabWidget(this);
    layout->addWidget(tab);

    initPages();

    for(auto i: pages)
    {
        tab->addTab(i, i->name());
    }

    buttonsArea = new QWidget(this);
    apply = new QPushButton("Apply", buttonsArea);
    cancel = new QPushButton("Cancel", buttonsArea);

    layout->addWidget(buttonsArea);
    btnsLayout = new QHBoxLayout();

    buttonsArea->setLayout(btnsLayout);
    btnsLayout->addStretch();
    btnsLayout->addWidget(apply);
    btnsLayout->addWidget(cancel);

    connect(cancel, &QPushButton::clicked, this, &Settings::cancelClicked);
    connect(apply, &QPushButton::clicked, this, &Settings::applyClicked);

    try
    {
       conf = XMLReader::makeConfigFromFile("config.xml");
    }
    catch(std::exception& e)
    {
        qDebug() << "Blad parsowania XML";
        qDebug() << e.what();
        exit(-1);
    }

    setConfigToPages();
    std::cout << "Wskaznik przed: " << conf.get();
}

void Settings::initPages()
{
    pages.push_back(new TabPageColors(tab));
}

void Settings::setConfigToPages()
{
    for(auto& i: pages)
    {
        i->setConfig(this->conf);
    }
}

void Settings::applyClicked()
{
    for(const auto &i: pages)
    {
        i->getConfig(this->conf);
    }

    emit configChanged(conf);
}

void Settings::cancelClicked()
{
    setConfigToPages();

    this->hide();
}

void Settings::closeEvent(QCloseEvent *event)
{
    qDebug() << "Closing settings";
    setConfigToPages();

    QWidget::closeEvent(event);
}

Settings::~Settings()
{
    XMLReader::saveConfigToFile("config.xml", conf);

    delete layout;
    delete apply;
    delete cancel;


    for(auto i: pages)
    {

        delete i;
    }

    delete tab;
    delete btnsLayout;
    delete buttonsArea;

}
