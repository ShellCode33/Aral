#ifndef SERVER_H
#define SERVER_H

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <vector>
#include <thread>
#include "../Common/boat.h"
#include <cstring> //memset

#define BUFFER_SIZE 1024
#define PORT_TCP 1337
#define PORT_UDP (PORT_TCP+1)

enum Mode
{
    TCP,
    UDP
};

class Server
{
public:
    Server(Mode mode);
    ~Server();
    void start();
    void startAndJoin();
    virtual void run() = 0;
    static std::vector<Boat*>& getBoats();

protected:
    int _serv_sock;
    sockaddr_in _serv_addr;
    static std::vector<Boat*> _boats;

private:
    std::thread *_run_thread;
};

#endif // SERVER_H
