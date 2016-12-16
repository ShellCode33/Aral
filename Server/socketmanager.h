#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>

#include "../Common/packet.h"

#define PORT 1337
#define BUFFER_SIZE 1024

class Client;

class SocketManager
{
private:
    // partie envoie de données
    int _serv_sock;
    struct sockaddr_in _serv_addr;

public:
    SocketManager();
    ~SocketManager();

    void init();

    std::string receive_request();
    int receive_integer_from(Client *client);
    void send_integer_to(Client *client, int i);
    std::string receive_string_from(Client *client);
    void send_string_to(Client *client, std::string msg);
    void send_data(std::string data);

    void close_sockets();
    Client* wait_new_client();

    Packet receive_packet_from(Client *client);
};

#endif // SOCKETMANAGER_H
