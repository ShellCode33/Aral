#include "mainwindow.h"
#include "socketmanager.h"
#include <QApplication>
#include <QtWebEngine/qtwebengineglobal.h>
#include <QStyleFactory>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion")); //Style des fenêtres
    QtWebEngine::initialize();

    MainWindow w;
    w.show();

    return a.exec();
}
