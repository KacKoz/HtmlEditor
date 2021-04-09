#ifndef BROWSERVIEW_H
#define BROWSERVIEW_H

#include <QWidget>
#include <QTextBrowser>


class BrowserView : public QTextBrowser
{
    Q_OBJECT
public:
    BrowserView( QWidget* parent = nullptr );
    ~BrowserView();


public slots:
    void onNewText(const QString& s);


};

#endif // BROWSERVIEW_H
