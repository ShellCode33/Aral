#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#include "datareceiver.h"
#include "clienthandler.h"

using namespace std;

int main(int argc, char **argv) {

    /*
    DataReceiver receiver = DataReceiver();
    string received = "";

    while(1) {
        received = receiver.receive_string();
        cout << "Received: " << received << endl;
        received = "";
    }

    receiver.close_socket();
    */

    ClientHandler handler = ClientHandler();

    handler.init_receive_socket();
    handler.receive_request();
    handler.close_sockets();

    handler.init_send_socket();
    handler.send_data("Premier envoi!");
    handler.send_data("Deuxième envoi!");
    handler.close_sockets();

    // Il faut attendre quelques secondes avant de rebind le socket, sinon crash
    for(int i = 0 ; i < 1000000000 ; i++)
        i = i;

    handler.init_send_socket();
    handler.send_data("Troisième envoi!");
    handler.close_sockets();

    return 0;
}
