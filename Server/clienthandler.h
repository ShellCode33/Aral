#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>

#define SEND_PORT 9477
#define RECV_PORT 9470
#define BUFFER_SIZE 1024

class ClientHandler
{
private:
    // partie envoie de données
    int _send_sock;
    struct sockaddr_in _client;
    char _send_buffer[BUFFER_SIZE];

    // partie réception de requêtes
    int _recv_sock, _client_sock;
    struct sockaddr_in _recv_addr, _client_addr;
    char _recv_buffer[BUFFER_SIZE];


public:
    ClientHandler();

    void init_send_socket();
    void init_receive_socket();

    std::string receive_request();
    void send_data(std::string data);

    void close_sockets();
};

#endif // CLIENTHANDLER_H
