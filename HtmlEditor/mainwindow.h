#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "codeeditor.h"
#include "linenumberarea.h"

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
    //void closeEvent(QCloseEvent *event);
    int saveInfo();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();



    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionDelete_triggered();

    void on_actionUndo_triggered();

    void on_plainTextEdit_textChanged();

private:
    Ui::MainWindow *ui;
    LineNumberArea* lna;
    CodeEditor *codeeditor;

    QString currentFile="";
};
#endif // MAINWINDOW_H
