#include <iostream>
#include "serverhandler.h"

using namespace std;

int main()
{
    ServerHandler handler = ServerHandler();

    handler.init_send_socket();
    handler.send_request("Coucou serveur!");
    handler.close_sockets();

    handler.init_receive_socket();
    handler.receive_data();
    handler.receive_data();
    handler.close_sockets();
    handler.init_receive_socket();
    handler.receive_data();
    handler.close_sockets();

    return 0;
}
