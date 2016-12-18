#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include <iostream>
#include <cstdlib>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <cstring> //memset
#include <algorithm> //find in vector

#include "server.h"
#include "../Common/packet.h"

class Client;

class ClientsHandler : public Server
{
public:
    ClientsHandler();
    ~ClientsHandler();
    void run() override;
    int receive_integer_from(Client *client);
    void send_integer_to(Client *client, int i);
    std::string receive_string_from(Client *client);
    void send_string_to(Client *client, std::string msg);
    Packet receive_packet_from(Client *client);
    void removeClient(Client *client);

private:
    std::vector<Client*> _clients;
    Client* wait_new_client();

};

#endif // SOCKETMANAGER_H
