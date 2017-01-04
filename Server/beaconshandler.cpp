#include "beaconshandler.h"

using namespace std;

BeaconsHandler::BeaconsHandler(ClientsHandler &clients_handler) : Server(UDP), _clients_handler(clients_handler)
{

}

string BeaconsHandler::receive_string()
{
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    struct sockaddr_in sender;
    memset(&sender, 0, sizeof(struct sockaddr_in));

    socklen_t c = sizeof(sender);
    int bytes_received = recvfrom(_serv_sock, buffer, BUFFER_SIZE-1, 0, (struct sockaddr*)&sender, &c); //On essaye de lire BUFFER_SIZE octets sur le socket

    if(bytes_received <= 0) {
        cerr << "socket error" << endl;
        return "";
    }

    return string(buffer);
}

void BeaconsHandler::run()
{
    cout << "BeaconsHandler looping..." << endl;

    while(true)
    {
        string boat_string = receive_string();

        if(boat_string.length() > 0)
        {
            Boat *boat_received = Boat::create(boat_string); //On crée un bateau à partir de la chaine de carac que l'on recoit
            Boat *boat_to_update = nullptr;

            for(Boat *boat : _boats)
            {
                if(boat->getName() == boat_received->getName())
                {
                    boat_to_update = boat;
                    break;
                }
            }


            if(boat_to_update != nullptr)
            {
                cout << boat_received->getName() << " updated" << endl;
                //update du bateau
                boat_to_update->setCap(boat_received->getVdirection(), boat_received->getHdirection());
                boat_to_update->setLocation(boat_received->getLatitude(), boat_received->getLongitude());
                boat_to_update->setTime("13h37");

                for(Client *client : _clients_handler.getClients())
                {
                    _clients_handler.send_packet_to(client, BOAT_UPDATED);
                    _clients_handler.send_string_to(client, boat_to_update->toString());
                }
            }

            else
            {
                _boats.push_back(boat_received);

                for(Client *client : _clients_handler.getClients())
                {
                    _clients_handler.send_packet_to(client, BOAT_CREATED);
                    _clients_handler.send_string_to(client, boat_received->toString());
                }
            }

        }
    }
}
