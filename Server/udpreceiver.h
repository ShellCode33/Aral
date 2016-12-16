#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <vector>

#include "client.h"

#define BEACON_PORT 25700
#define COORDINATES_STORED 100

class UdpReceiver {

private:
    struct sockaddr_in _serv_addr;
    struct sockaddr_in _client_addr;
    int _serv_sock;
    char _buffer[BUFFER_SIZE];
    std::string _data_recvd;
    socklen_t _ssize;

public:
    UdpReceiver();

    std::string receive_string();
    void save_coordinate(std::string coord);

    void close_socket();
};

#endif // DATARECEIVER_H
