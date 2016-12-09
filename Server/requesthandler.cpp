#include "requesthandler.h"

RequestHandler::RequestHandler(string request, ClientHandler* client)
    : _client {client}
{
    _request = split_request(request);
    treat_request();
}

RequestHandler::~RequestHandler() {
    delete _request;
}


vector<string>* RequestHandler::split_request(string request) {
    vector<string>* buf = new vector<string>();
    char* rq_cpy = strdup(request.c_str());
    char* delim = " ";
    char* token = strtok(rq_cpy, delim);

    while(token != NULL) {
        buf->push_back(string(token));
        token = strtok(NULL, delim);
    }

    delete rq_cpy;
    delete delim;
    delete token;

    return buf;
}

void RequestHandler::treat_request() {
    if (_request->size() < 1)  {

        return;
    }

    if(_request->at(0) == "get") {

    }

    else {

    }
}
