#include "client.h"
#include "clientshandler.h"

using namespace std;

int Client::_current_id = 0;

Client::Client(int sock, sockaddr_in addr, ClientsHandler &clients_handler) : _client_id(_current_id++), _sock(sock), _addr(addr), _clients_handler(clients_handler)
{

}

//Lance un thread qui va gérer toutes les demandes du client
void Client::manage()
{
    thread t(&Client::process_requests, this);
    t.detach();
}

void Client::process_requests()
{
    cout << "Thread of client " << _client_id << " is beginning" << endl;

    vector<Boat*> boats = _clients_handler.getBoats();

    while(true)
    {
        Packet packet = _clients_handler.receive_packet_from(this);

        switch(packet)
        {
        case GET_ALL_BOATS:
            cout << "Client " << _client_id << " asks GET_ALL_BOATS !" << endl;
            _clients_handler.send_integer_to(this, boats.size()); //On envoit le nombre de bateaux à réceptionner

            cout << "sending the " << boats.size() << " boats" << endl;

            for(int i = 0; i < (int)boats.size(); i++)
                _clients_handler.send_string_to(this, boats.at(i)->toString());

            break;

        case GET_BOAT:
            cout << "Client " << _client_id << " asks GET_BOATS !" << endl;
            string name = _clients_handler.receive_string_from(this); //On récupère le nom demandé par le client

            for(Boat * boat : boats)
            {
                if(boat->getName() == name) //On le trouve
                {
                    _clients_handler.send_string_to(this, boat->toString()); //Et on l'envoie
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
