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
    void openFileFromTree(QString path);

protected:
    //void contextMenuEvent(QContextMenuEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent * event);

public slots:
    void changefileDirectory(QString name);
    void changeDirectory(QString name);
    void on_actionNapiszcos_triggered();
    void customMenuRequested(const QPoint &pos);
    //void on_treeView_doubleClicked(const QModelIndex &index);

private:
    QFileSystemModel *model;
    QAction* newAct;
    QPoint contextmenucords;

};

#endif // DIRTREE_H
