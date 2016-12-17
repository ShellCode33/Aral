#include "clientshandler.h"
#include "client.h"

using namespace std;

ClientsHandler::ClientsHandler() : Server(TCP)
{

}

Client* ClientsHandler::wait_new_client()
{
    cout << "Waiting a new client..." << endl;

    int client_sock;
    struct sockaddr_in client_addr;

    //On crée la socket associé au client
    socklen_t c = sizeof(struct sockaddr_in);
    if((client_sock = accept(_serv_sock, (struct sockaddr *)&client_addr, &c)) < 0){
        cerr << "accept error" << endl;
        exit(EXIT_FAILURE);
    }

    cout << "A new client is connected !" << endl;

    return new Client(client_sock, client_addr, *this);
}

Packet ClientsHandler::receive_packet_from(Client *client)
{
    Packet packet;
    size_t bytes_received = 0;

    while(bytes_received < sizeof(Packet))
    {
        int received = recv(client->getSocket(), &packet+bytes_received, sizeof(Packet)-bytes_received, 0);

        if(received == 0)
        {
            cerr << "receiving packet error !" << endl;
            exit(EXIT_FAILURE);
        }

        bytes_received += received;
    }

    return packet;
}

void ClientsHandler::start()
{
    cout << "ClientsHandler looping..." << endl;

    while(true) //On gère la connexion d'un client indéfiniement
    {
        Client *client = wait_new_client();
        _clients.push_back(client);
        client->manage();
    }
}

int ClientsHandler::receive_integer_from(Client *client)
{
    int i;
    size_t bytes_received = 0;

    while(bytes_received < sizeof(int))
    {
        int received = recv(client->getSocket(), &i+bytes_received, sizeof(int)-bytes_received, 0);

        if(received == 0)
        {
            cerr << "receiving packet error !" << endl;
            exit(EXIT_FAILURE);
        }

        bytes_received += received;
    }

    return i;
}

void ClientsHandler::send_integer_to(Client *client, int i)
{
    if(send(client->getSocket(), &i, sizeof(i), 0) < 0)
    {
        std::cout << "send failed" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void ClientsHandler::send_string_to(Client *client, string msg)
{
    size_t len = msg.length();

    //On envoie la taille de la chaine de carac
    if(send(client->getSocket(), &len, sizeof(len), 0) < 0)
    {
        cerr << "send failed";
        exit(EXIT_FAILURE);
    }

    //Envoie la chaine de carac
    if(send(client->getSocket(), msg.c_str(), msg.length(), 0) < 0)
    {
        cerr << "send failed";
        exit(EXIT_FAILURE);
    }
}

string ClientsHandler::receive_string_from(Client *client)
{
    size_t str_len = 0;
    size_t bytes_received = 0;

    //On recoit la taille de la chaine que l'on va devoir récupérer
    while(bytes_received < sizeof(str_len))
    {
        int received = recv(client->getSocket(), &str_len+bytes_received, sizeof(str_len)-bytes_received, 0);

        if(received == 0)
        {
            cerr << "Error while receiving size of string" << endl;
            exit(EXIT_FAILURE);
        }

        bytes_received += received;
    }

    bytes_received = 0;

    char *buffer = new char[str_len + 1];
    memset(buffer, 0, str_len+1);

    //On récupère la chaine
    while(bytes_received < str_len)
    {
        int received = recv(client->getSocket(), buffer+bytes_received, str_len-bytes_received, 0);

        if(received == 0)
        {
            cerr << "Error while receiving string" << endl;
            exit(EXIT_FAILURE);
        }

        bytes_received += received;
    }

    return string(buffer);
}

ClientsHandler::~ClientsHandler()
{
    for(Client* client : _clients)
        delete client;

    _clients.clear();
}
