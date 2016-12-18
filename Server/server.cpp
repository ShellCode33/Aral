#include "server.h"

using namespace std;

vector<Boat*> Server::_boats; //On mentionne juste l'existance de cet attribut static au cpp

Server::Server(Mode mode)
{
    //Création du socket server
    if(mode == UDP)
        _serv_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //création du socket
    else if(mode == TCP)
        _serv_sock = socket(AF_INET, SOCK_STREAM, 0);

    if(_serv_sock < 0)
    {
        cerr << "socket() error : " << errno << endl;
        exit(EXIT_FAILURE);
    }

    //Définition des informations du socket ipv4, on accepte toutes les adresses, on définit le port
    _serv_addr.sin_family = AF_INET;
    _serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    _serv_addr.sin_port = htons(mode == TCP ? PORT_TCP : PORT_UDP);

    //On bind la socket avec la structure contenant les informations
    if(bind(_serv_sock, (struct sockaddr*)&_serv_addr, sizeof(_serv_addr)) < 0)
    {
        cerr << "bind() error : " << errno << endl;
        exit(EXIT_FAILURE);
    }

    if(mode == TCP)
    {
        //La socket server va écouter les connexions
        listen(_serv_sock, 10); //10 clients max
        cout << "PORT " << PORT_TCP << " : TCP";
    }

    else
        cout << "PORT " << PORT_UDP << " : UDP";

    cout << " server started !" << endl;
}

std::vector<Boat *> &Server::getBoats()
{
    return _boats;
}

Server::~Server()
{    
    cout << "Stopping server..." << endl;

    delete _run_thread;

    for(Boat *boat : _boats)
        delete boat;

    _boats.clear();
    close(_serv_sock);
}

void Server::start()
{
    //On appelle la methode abstraite dans un nouveau thread
    _run_thread = new thread(&Server::run, this);
    _run_thread->detach();
}

void Server::startAndJoin()
{
    run();
}

