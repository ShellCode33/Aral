#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cstring>
#include <clienthandler.h>

using namespace std;

class RequestHandler {
private:
    vector<string>* _request;
    ClientHandler* _client;

public:
    RequestHandler(string request, ClientHandler* client);
    ~RequestHandler();

    vector<string>* split_request(string request);
    void treat_request();
};

#endif // REQUESTHANDLER_H
