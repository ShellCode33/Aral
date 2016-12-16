#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <thread>

#include "datareceiver.h"
#include "clienthandler.h"
#include "requesthandler.h"

using namespace std;

void catch_beacon_data() {
    DataReceiver receiver = DataReceiver();
    string received = "";

    while(1) {
        received = receiver.receive_string();
        cout << "Received: " << received << endl;
    }

    receiver.close_socket();
}

void treat_client_requests() {
    ClientHandler handler = ClientHandler();
    RequestHandler* rqhandler;

    while(1) {
        sleep(1);
        handler.init_receive_socket();
        rqhandler = new RequestHandler(handler.receive_request(), handler);
    }

    delete rqhandler;
    handler.close_sockets();
}

int main() {

    thread* beacon_th;
    thread* client_th;

    beacon_th = new thread(catch_beacon_data);
    client_th = new thread(treat_client_requests);

    beacon_th->join();
    client_th->join();

    delete beacon_th;
    delete client_th;

    return 0;
}
