#include "socketmanager.h"
#include "client.h"

using namespace std;

SocketManager::SocketManager()
{
}

void SocketManager::init() {
    // RECV SOCKET-----------------------------------------------------------

    //Création du socket server
    if((_serv_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        cerr << "socket error";
        exit(EXIT_FAILURE);
    }

    //Définition des informations du socket ipv4, on accepte toutes les adresses, on définit le port
    _serv_addr.sin_family = AF_INET;
    _serv_addr.sin_addr.s_addr = INADDR_ANY;
    _serv_addr.sin_port = PORT;

    //On bind la socket avec la structure contenant les informations
    if(bind(_serv_sock, (struct sockaddr*)&_serv_addr, sizeof(_serv_sock)) < 0){
        cerr << "bind error, use another port" << endl;
        exit(EXIT_FAILURE);
    }

    //La socket server va écouter les connexions
    listen(_serv_sock, 1000);
}

Client* SocketManager::wait_new_client()
{
    int client_sock;
    struct sockaddr_in client_addr;

    //On crée la socket associé au client
    int c = sizeof(struct sockaddr_in);
    if((client_sock = accept(_serv_sock, (struct sockaddr *)&client_addr, (socklen_t*)&c)) < 0){
        cerr << "accept error, tell admin";
        exit(EXIT_FAILURE);
    }

    return new Client(client_sock, client_addr, *this);
}

Packet SocketManager::receive_packet_from(Client *client)
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

int SocketManager::receive_integer_from(Client *client)
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
}

void SocketManager::send_integer_to(Client *client, int i)
{
    if(send(client->getSocket(), &i, sizeof(i), 0) < 0)
    {
        std::cout << "send failed" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void SocketManager::send_string_to(Client *client, string msg)
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

string SocketManager::receive_string_from(Client *client)
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

    char *buffer = new char[str_len];

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

SocketManager::~SocketManager()
{
    close(_serv_sock);
}
