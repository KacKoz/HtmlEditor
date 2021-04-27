#ifndef AUTOSAVE_H
#define AUTOSAVE_H

#include <QWidget>
#include <QThread>


class Autosave : public QThread
{
    Q_OBJECT
signals:
    void runsave();
public slots:
    void stopthread(bool);
protected:
    void run();
private:
    bool isThreadStopped = false;

};

#endif // AUTOSAVE_H
