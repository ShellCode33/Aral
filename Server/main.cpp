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

    handler.receive_message();

    return 0;
}
