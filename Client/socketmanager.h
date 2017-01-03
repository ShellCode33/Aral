#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include "../Common/packet.h"

#define PORT 1337
#define BUFFER_SIZE 1024

using namespace std;

class SocketManager {
private:
    int _sock;
    struct sockaddr_in _server;

public:
    SocketManager();
    ~SocketManager();

    void send_packet(Packet packet);
    void send_string(string msg);
    string receive_string();
    void close_sockets();
    int receive_integer();
    void tryConnect();
    Packet receive_packet();
};

#endif // SERVERHANDLER_H
