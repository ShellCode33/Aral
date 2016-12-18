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

    MainWindow mainWindow;

    SocketManager socket_manager;
    socket_manager.tryConnect();
    socket_manager.send_packet(GET_ALL_BOATS); //On fait la demande de récupérer tous les bateaux
    int boats_count = socket_manager.receive_integer(); //On récupère le nombre de bateaux

    for(int i = 0; i < boats_count; i++)
        mainWindow.create_boat(socket_manager.receive_string());

    mainWindow.map_refresh();

    mainWindow.show();
    return a.exec();
}
