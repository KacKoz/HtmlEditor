#ifndef TABPAGETEXT_H
#define TABPAGETEXT_H

#include "TabPageWidget.h"
//#include "choosecolorbutton.h"

#include <QGridLayout>
#include <map>
#include <utility>
#include <QLabel>
#include <QCheckBox>


class TabPageText : public TabPageWidget
{
public:
    explicit TabPageText(QWidget *parent = nullptr);
    ~TabPageText();

    QString name() override;
    void setConfig(std::shared_ptr<config>) override;
    void getConfig(std::shared_ptr<config>) override;

signals:

private:
    void createPairs();

    QGridLayout *gridl;
    std::map<QString, std::pair<QLabel*, QCheckBox*>> selections;

};

#endif // TABPAGETEXT_H
