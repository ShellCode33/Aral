#include "clienthandler.h"

ClientHandler::ClientHandler()
    :_send_sock {0}, _send_buffer {0}, _recv_sock {0}, _client_sock {0}, _recv_buffer {0}
{
    //Création du socket server
    if((_recv_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        cerr << "socket error";
        exit(EXIT_FAILURE);
    }

    //Définition des informations du socket ipv4, on accepte toutes les adresses, on définit le port
    _recv_addr.sin_family = AF_INET;
    _recv_addr.sin_addr.s_addr = INADDR_ANY;
    _recv_addr.sin_port = PORT;

    //On bind la socket avec la structure contenant les informations
    if(bind(_recv_sock, (struct sockaddr*)&_recv_addr, sizeof(_recv_addr)) < 0){
        cerr << "bind error, use another port" << std::endl;
        exit(EXIT_FAILURE);
    }

    //La socket server va écouter les connexions
    listen(_recv_sock, 1);

    //On crée la socket associé au client
    int c = sizeof(struct sockaddr_in);
    if((_client_sock = accept(_recv_sock, (struct sockaddr *)&_client_addr, (socklen_t*)&c)) < 0){
        cerr << "accept error, tell admin";
        exit(EXIT_FAILURE);
    }
}

void ClientHandler::receive_message() {
    //On lit ce qu'on reçoit depuis le client
    while(recv(_client_sock, _recv_buffer, BUFFER_SIZE, 0) != 0)
    {
        std::cout << "Received : "<< _recv_buffer << std::endl;
        memset(_recv_buffer, 0, BUFFER_SIZE);
    }
}
