#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#include "datareceiver.h"
#include "clienthandler.h"

using namespace std;

int main() {

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

    while(1) {

    }

    return 0;
}
