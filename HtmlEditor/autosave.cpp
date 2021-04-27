#include "autosave.h"
#include <QDebug>

void Autosave::run(){
    int i;
    while(!isThreadStopped)
    {
        emit runsave();
        i=0;
        while(!isThreadStopped and i<200)
        {
            msleep(100);
            i++;
        }
    }
}

void Autosave::stopthread(bool stopped)
{
    isThreadStopped = stopped;
}

