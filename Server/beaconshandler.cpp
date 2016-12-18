#include "beaconshandler.h"

using namespace std;

BeaconsHandler::BeaconsHandler() : Server(UDP)
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
            Boat *boat_to_update = nullptr;

            for(Boat *boat : _boats)
            {
                if(boat->toString() == boat_string)
                {
                    boat_to_update = boat;
                    break;
                }
            }

            Boat *boat = Boat::create(boat_string); //On crée un bateau à partir de la chaine de carac que l'on recoit

            if(boat_to_update != nullptr)
            {
                //update du bateau
                boat_to_update->setCap(boat->getCap());
                boat_to_update->setLocation(boat->getLatitude(), boat->getLongitude());
                boat_to_update->setTime("13h37");
            }

            else
            {
                _boats.push_back(boat);
            }
        }
    }
}
