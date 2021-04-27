#ifndef TABPAGECOLORS_H
#define TABPAGECOLORS_H

#include "TabPageWidget.h"
#include "choosecolorbutton.h"

#include <QGridLayout>
#include <map>
#include <utility>
#include <QLabel>


class TabPageColors : public TabPageWidget
{
public:
    explicit TabPageColors(QWidget *parent = nullptr);
    ~TabPageColors();

    QString name() override;
    void setConfig(std::shared_ptr<config>) override;
    void getConfig(std::shared_ptr<config>) override;

signals:

private:
    void createPairs();

    QGridLayout *gridl;
    std::map<QString, std::pair<QLabel*, ChooseColorButton*>> selections;

};

#endif // TABPAGECOLORS_H
