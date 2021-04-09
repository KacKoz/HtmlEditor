#include "browserview.h"
#include <QDebug>



BrowserView::BrowserView(QWidget* parent) : QTextBrowser(parent)
{

}

BrowserView::~BrowserView()
{

}

 void BrowserView::onNewText(const QString& text)
 {
    if(this->isVisible())
        this->setHtml(text);
 }

