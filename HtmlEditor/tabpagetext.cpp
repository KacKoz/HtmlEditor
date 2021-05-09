#include "tabpagetext.h"
#include <QCheckBox>
#include <QDebug>

TabPageText::TabPageText(QWidget *parent) : TabPageWidget(parent)
{
    gridl = new QGridLayout(this);
    this->setLayout(gridl);

    createPairs();

    int nr = 0;
    for(const auto& i: selections)
    {
        gridl->addWidget(i.second.first, nr, 0,Qt::AlignTop);
        gridl->addWidget(i.second.second, nr, 1,Qt::AlignTop);
        ++nr;
    }
}

QString TabPageText::name()
{
    return "Text";
}

void TabPageText::setConfig(std::shared_ptr<config> conf)
{
    if(conf == nullptr) {qDebug() << "SetConfig-Colors: Config == nullptr"; return;}
    for(auto &i: selections)
    {
        i.second.second ->setChecked(conf->text[i.first].toInt());
        //qDebug()<<conf->text["wordwrap"];
    }
}

void TabPageText::getConfig(std::shared_ptr<config> conf)
{
    if(conf == nullptr) {qDebug() << "GetConfig-Colors: Config == nullptr"; return;}
    for(auto &i: selections)
    {
        conf->text[i.first] = QString::number(i.second.second->isChecked());
    }
}

void TabPageText::createPairs()
{
    selections["wordwrap"] = std::make_pair<QLabel*, QCheckBox*>(new QLabel("Word Wrap", this), new QCheckBox(this));

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

TabPageText::~TabPageText()
{
    delete gridl;
    for(auto& i: selections)
    {
        delete i.second.first;
        delete i.second.second;
    }


}
