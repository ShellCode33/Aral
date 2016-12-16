#include "client.h"

using namespace std;

Client::Client(int sock, sockaddr_in addr, SocketManager socketManager) : _sock(sock), _addr(addr), _socketManager(socketManager)
{

}

//Lance un thread qui va gérer toutes les demandes du client
void Client::manage(vector<Boat> * boats)
{
    thread t(&Client::t_process_requests, this, boats);
}

void Client::t_process_requests(vector<Boat> * boats)
{
    while(true)
    {
        Packet packet = _socketManager.receive_packet_from(this);

        switch(packet)
        {
        case GET_ALL_BOATS:
            _socketManager.send_integer_to(this, boats->size()); //On envoit le nombre de bateaux à réceptionner

            for(int i = 0; i < (int)boats->size(); i++)
                _socketManager.send_string_to(this, (*boats)[i].toString());

            break;

        case GET_BOAT:
            string name = _socketManager.receive_string_from(this); //On récupère le nom demandé par le client

            for(const Boat & boat : *boats)
            {
                if(boat.getName() == name) //On le trouve
                {
                    _socketManager.send_string_to(this, boat.toString()); //Et on l'envoie
                    break;
                }
            }

            break;
        }
    }
}

int Client::getSocket()
{
    return _sock;
}

sockaddr_in Client::getAddr()
{
    return _addr;
}
