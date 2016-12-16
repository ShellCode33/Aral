#include "requesthandler.h"

RequestHandler::RequestHandler(string request, ClientHandler &client)
{
    _client = &client;
    _request = split_request(request);
    treat_request();
}

RequestHandler::~RequestHandler() {
    delete _request;
    delete _client;
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
        _client->init_send_socket();
        _client->send_data(":ERR:too_few_args");
        _client->close_sockets();
        return;
    }

    if(_request->at(0) == "get") {
        vector<Coordinates*> buf;

        if(stoi(_request->at(1)) != -1) {
            buf = CoordinateBuffer::get_all_coordinates_of(stoi(_request->at(1)));
            _client->init_send_socket();
            for(auto c : buf)
                _client->send_data(c->toString());
            _client->close_sockets();
        }

        else {
            _client->init_send_socket();
            _client->send_data(":ERR:invalid_arg");
            _client->close_sockets();
        }
    }

    else {
        _client->init_send_socket();
        _client->send_data(":ERR:undefined_request");
        _client->close_sockets();
    }
}
