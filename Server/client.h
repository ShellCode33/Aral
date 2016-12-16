#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>
#include <thread>
#include <vector>
#include "../Common/packet.h"
#include "../Common/boat.h"
#include "socketmanager.h"

class Client
{
public:
    Client(int sock, sockaddr_in addr, SocketManager socketManager);
    void manage(std::vector<Boat> *boats);
    int getSocket();
    struct sockaddr_in getAddr();

private:
    int _sock;
    sockaddr_in _addr;
    SocketManager _socketManager;
    void t_process_requests(std::vector<Boat> *boats);
};

#endif // CLIENT_H
