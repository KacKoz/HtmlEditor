#ifndef TABPAGEWIDGET_H
#define TABPAGEWIDGET_H

#include <QWidget>
#include <memory>

#include "Configuration.h"

class TabPageWidget : public QWidget
{
protected:
    TabPageWidget(QWidget *parent = nullptr) : QWidget(parent)
    { }
public:
    virtual QString name() =0;
    virtual void setConfig(std::shared_ptr<config>) =0;
    virtual void getConfig(std::shared_ptr<config>) =0;
};

#endif // TABPAGEWIDGET_H
