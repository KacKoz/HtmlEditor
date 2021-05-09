#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>


#include "codeeditor.h"
#include "linenumberarea.h"
#include "dirtree.h"
#include "button.h"
#include "codeeditorarea.h"
#include "parser.h"
#include "browserview.h"
#include "autosave.h"
#include "settings.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event);
    void closeEvent(QCloseEvent *event);
    int saveInfo();
    void onlyhtml(QString func);
    //void autosave();

private slots:

    void on_actionNew_triggered(bool deletedintree = false);

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();



    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionDelete_triggered();

    void on_actionUndo_triggered();

    void on_plainTextEdit_textChanged();

    void on_actionOpen_directory_triggered();

    void newcurrentfilename(QString name);

    void on_actionParsuj_triggered();

    void on_actionShow_hide_preview_triggered();

    void on_actionAutosave_toggled(bool arg1);

    void on_actionWord_wrap_toggled(bool arg1);

    void fileChangedSlot(QString);
    void on_actionAdvanced_settings_triggered();

public slots:
    void on_actionOpen_from_tree(QString path);
    void givecurrentfilename();
    void autosaveRequest();
    //void on_treeView_doubleClicked(const QModelIndex &index);

signals:
    void filechanged(QString);
    void directorychanged(QString);
    void currentfilename(QString);
    void stopthread(bool);
    //void wordWrapChanged(bool);

private:
    QString currentFile="";
    Ui::MainWindow *ui;
    DirTree *dirtree;
    Button *btndir;
    Button *btnfile;
    Button *btnparent;
    QVBoxLayout *verticallayout;
    QHBoxLayout *horizontallayoutbuttons;
    QHBoxLayout *horizontallayoutmain;
    QWidget *window;
    QWidget *dirmenu;
    Parser *parser;
    bool hasChanged = false;
    bool autosaveon = false;
    BrowserView *browser;
    Settings* settings;
    CodeEditorArea* cda;
    Autosave* autosave;
};
#endif // MAINWINDOW_H
