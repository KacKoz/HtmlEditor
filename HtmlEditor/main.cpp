#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    qDebug() << "Szymon to gupek";
    w.show();
    return a.exec();
}
