#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <thread>

#include "beaconshandler.h"
#include "clientshandler.h"
#include "client.h"

using namespace std;

int main() {

    BeaconsHandler beacon_handler;
    ClientsHandler client_handler;

    //On démarre la gestion des balises dans un thread séparé
    //thread beacon_th(&BeaconsHandler::start, beacon_handler);
    //beacon_th.detach();
    //On démarre la gestion des clients dans le thread principal
    client_handler.start();

    return 0;
}
