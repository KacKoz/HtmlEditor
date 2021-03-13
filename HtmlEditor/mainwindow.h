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

    void givecurrentfilename();

    void newcurrentfilename(QString name);

public slots:
    void on_actionOpen_from_tree(QString path);
    //void on_treeView_doubleClicked(const QModelIndex &index);

signals:
    void filechanged(QString name);
    void directorychanged(QString name);
    void currentfilename(QString name);


private:
    QString currentFile="";
    Ui::MainWindow *ui;
    CodeEditor *codeeditor;
    LineNumberArea *lna;
    DirTree *dirtree;
    Button *btndir;
    Button *btnfile;
    Button *btnparent;
    QVBoxLayout *verticallayout;
    QHBoxLayout *horizontallayoutbuttons;
    QHBoxLayout *horizontallayoutmain;
    QWidget *window;
    QWidget *dirmenu;
    bool hasChanged = false;
};
#endif // MAINWINDOW_H
