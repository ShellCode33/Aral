#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cstring>
#include <clienthandler.h>
#include <coordinatebuffer.h>
#include <../coordinates.h>

class RequestHandler {
private:
    vector<string>* _request;
    ClientHandler* _client;

public:
    RequestHandler(std::string request, ClientHandler &client);
    ~RequestHandler();

    std::vector<string>* split_request(std::string request);
    void treat_request();
};

#endif // REQUESTHANDLER_H
