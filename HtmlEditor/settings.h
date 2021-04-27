#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QColorDialog>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QLabel>
#include <vector>

#include "TabPageWidget.h"
#include "tabpagecolors.h"
#include "Configuration.h"

class Settings : public QWidget
{
    Q_OBJECT
public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

    void emitSettings() {emit configChanged(conf);}


signals:
    void configChanged(const std::shared_ptr<config>&);





private:

    void initPages();
    void setConfigToPages();

    void applyClicked();
    void cancelClicked();
    void closeEvent(QCloseEvent *event) override;

    QVBoxLayout *layout;
    QHBoxLayout *btnsLayout;
    QTabWidget *tab;
    QWidget *buttonsArea;
    QPushButton *apply, *cancel;

    std::vector<TabPageWidget*> pages;

    std::shared_ptr<config> conf;
};

#endif // SETTINGS_H
