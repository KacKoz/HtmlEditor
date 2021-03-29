#ifndef DIRTREE_H
#define DIRTREE_H

#include <QTreeWidget>
#include <QFileSystemModel>

class DirTree : public QTreeView
{
    Q_OBJECT

public:
    DirTree();


signals:
    void openFileFromTree(QString);
    void askforcurrentfilename();
    void filedeleted(bool);
    void currentfilenamechanged(QString);
    void currentdirpath(QString);

protected:
    //void contextMenuEvent(QContextMenuEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent * event);
    int deleteInfo();

public slots:
    void changefileDirectory(QString name);
    void changeDirectory(QString name);
    void on_actioncontextopen_triggered();
    void on_actioncontextdelete_triggered();
    void on_actioncontextrename_triggered();
    void customMenuRequested(const QPoint &pos);
    void receivecurrentfilename(QString name);
    void givecurrentdir();
    //void on_treeView_doubleClicked(const QModelIndex &index);

private:
    QFileSystemModel *model;
    QAction* contextdelete;
    QAction* contextopen;
    QAction* contextrename;
    QPoint contextmenucords;
    QString currentfile="";
    QString currentdir="";
    char forbiddennames[9] = {'/','\\','"','?',':','*','|','<','>'};

};

#endif // DIRTREE_H
