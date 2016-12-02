#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>

#define PORT 25600
#define BUFFER_SIZE 4096

using namespace std;

class DataReceiver {

private:
    struct sockaddr_in _serv_addr;
    struct sockaddr_in _client_addr;
    int _serv_sock;
    char _buffer[BUFFER_SIZE];
    string _data_recvd;
    socklen_t _ssize;

public:
    DataReceiver();

    string receive_string();
};

#endif // DATARECEIVER_H
