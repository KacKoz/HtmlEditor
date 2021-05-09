#include "tabpagecolors.h"

#include <QDebug>

TabPageColors::TabPageColors(QWidget *parent) : TabPageWidget(parent)
{
    gridl = new QGridLayout(this);
    this->setLayout(gridl);

    createPairs();

    int nr = 0;
    for(const auto& i: selections)
    {
        gridl->addWidget(i.second.first, nr, 0);
        gridl->addWidget(i.second.second, nr, 1);
        ++nr;
    }
}

QString TabPageColors::name()
{
    return "Colors";
}

void TabPageColors::setConfig(std::shared_ptr<config> conf)
{
    if(conf == nullptr) {qDebug() << "SetConfig-Colors: Config == nullptr"; return;}
    for(auto &i: selections)
    {
        i.second.second->setColor(conf->colors[i.first]);
    }
}

void TabPageColors::getConfig(std::shared_ptr<config> conf)
{
    if(conf == nullptr) {qDebug() << "GetConfig-Colors: Config == nullptr"; return;}
    for(auto &i: selections)
    {
        conf->colors[i.first] = i.second.second->text();
    }
}

void TabPageColors::createPairs()
{
    selections["tag"] = std::make_pair<QLabel*, ChooseColorButton*>(new QLabel("Tags Color", this), new ChooseColorButton(this));
    selections["string"] = std::make_pair<QLabel*, ChooseColorButton*>(new QLabel("String Color", this), new ChooseColorButton(this));
    selections["attribute"] = std::make_pair<QLabel*, ChooseColorButton*>(new QLabel("Attribute Color", this), new ChooseColorButton(this));
    selections["comment"] = std::make_pair<QLabel*, ChooseColorButton*>(new QLabel("Comment Color", this), new ChooseColorButton(this));
    selections["base"] = std::make_pair<QLabel*, ChooseColorButton*>(new QLabel("Base Color", this), new ChooseColorButton(this));

    for(auto& i: selections)
    {
        i.second.second->setStyleSheet("Text-align:left");
    }
}

/*void TabPageColors::adjustColors()
{
    QPixmap px(20,20);
    QColor col;

    for(auto& i: selections)
    {
        col.setNamedColor(i.second.second->text());
        px.fill(col);

        i.second.second->setIcon(QIcon(px));
    }
}*/

TabPageColors::~TabPageColors()
{
    qDebug() << "Destruktor;";
    for(auto& i: selections)
    {
        delete i.second.first;
        delete i.second.second;
    }

    delete gridl;

}
