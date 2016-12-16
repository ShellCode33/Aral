#include "mainwindow.h"
#include "serverhandler.h"
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

    SocketManager handler = SocketManager();
    string buffer;

    /*
     *
        while(1) {
            handler.init_send_socket();
            handler.send_request(fgets((char*)buffer.c_str(), BUFFER_SIZE - 1 , stdin));

            handler.close_sockets();
            handler.init_receive_socket();
            buffer = handler.receive_data();
            while(buffer != ":END:")
                cout << buffer << endl;
            handler.close_sockets();
        }
    */

    return a.exec();
}
