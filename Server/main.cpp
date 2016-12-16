#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <thread>

#include "udpreceiver.h"
#include "socketmanager.h"
#include "client.h"

using namespace std;

void catch_beacon_data(vector<Boat> * boats) {
    UdpReceiver receiver = UdpReceiver();
    string received = "";

    while(true)
    {
        received = receiver.receive_string();
        cout << "Received: " << received << endl;
    }

    receiver.close_socket();
}

void process_clients(vector<Boat> * boats) {

    SocketManager socketManager;
    vector<Client*> clients;

    while(true) //On gère la connexion d'un client indéfiniement
    {
        Client *client = socketManager.wait_new_client();
        clients.push_back(client);
        client->manage(boats);
    }

    for(Client* client : clients)
        delete client;

    clients.clear();
}

int main() {

    vector<Boat> boats;
    thread beacon_th(catch_beacon_data, &boats);
    thread client_th(process_clients, &boats);

    beacon_th.join();
    client_th.join();

    return 0;
}
