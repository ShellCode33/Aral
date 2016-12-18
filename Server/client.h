#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>
#include <thread>
#include <vector>
#include "../Common/packet.h"
#include "../Common/boat.h"
#include "clientshandler.h"

class Client
{
public:
    Client(int sock, sockaddr_in addr, ClientsHandler &clients_handler);
    ~Client();
    void manage();
    int getSocket();
    struct sockaddr_in getAddr();
    int getId();

private:
    static int _current_id;
    int _client_id;
    int _sock;
    sockaddr_in _addr;
    ClientsHandler & _clients_handler;
    void process_requests();
    std::thread _job;
    bool _job_active;
};

#endif // CLIENT_H
