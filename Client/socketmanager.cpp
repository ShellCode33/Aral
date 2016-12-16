#include "socketmanager.h"

SocketManager::SocketManager()
    :_send_sock {0}, _send_buffer {0}, _recv_sock {0}, _serv_sock {0}, _recv_buffer {0}
{
}

void SocketManager::init_socket() {

    // SEND SOCKET -----------------------------------------------------------
    if((_send_sock = socket(AF_INET , SOCK_STREAM, 0)) == -1) {
        cerr << "Could not create socket";
        exit(EXIT_FAILURE);
    }

    //Définition de la connexions : adresse du serveur, port, ipv4 ...
    _server.sin_addr.s_addr = inet_addr("127.0.0.1");
    _server.sin_family = AF_INET;
    _server.sin_port = PORT;

    //Connexion
    if(connect(_send_sock, (struct sockaddr *)&_server , sizeof(_server)) < 0) {
        cerr << "connect failed";
        exit(EXIT_FAILURE);
    }

    // -----------------------------------------------------------------------
}

void SocketManager::sendMessage(string msg)
{
    //Envoie des données
    if(send(_send_sock, msg.c_str(), BUFFER_SIZE, 0) < 0)
    {
        cerr << "send failed";
        exit(EXIT_FAILURE);
    }

    else
    {
        std::cout << "Send : " << msg << std::endl;
    }

    memset(_send_buffer, 0, BUFFER_SIZE);
}

string SocketManager::receive_data()
{
    while(recv(_serv_sock, _recv_buffer, BUFFER_SIZE, 0) != 0)
    {
        string str = _recv_buffer;
        memset(_recv_buffer, 0, BUFFER_SIZE);
        return str;
    }
    return nullptr;
}

void SocketManager::close_sockets()
{
    close(_recv_sock);
    close(_send_sock);
    close(_serv_sock);
}


