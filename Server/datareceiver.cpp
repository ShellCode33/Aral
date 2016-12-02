#include "datareceiver.h"

DataReceiver::DataReceiver()
    : _serv_addr {0}, _client_addr {0}, _buffer {0}
{
    _serv_addr.sin_family = AF_INET; //Domaine de communication (ipv4)
    _serv_addr.sin_port = htons(PORT); //Définition du port de communication du serveur
    _serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //On accepte toutes les connexions de n'importe quelle adresse entrante
                                                    //htonl = host to network long
    _data_recvd = "";
    _ssize = sizeof(_client_addr);

    _coordinates = vector<Coordinates*>(50);

    _serv_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //création du socket
    if (_serv_sock < 0) {
        cerr << "Can't create socket" << endl;
    }

    if(bind(_serv_sock, (struct sockaddr*)&_serv_addr, sizeof(_serv_addr)) < 0) { //relie _serv_addr et serv_sock
        cerr << "Can't create server" << endl;
    }

    cout << "bind ok" << endl;
}

string DataReceiver::receive_string() {
    int bytes_received = recvfrom(_serv_sock, _buffer, BUFFER_SIZE-1, 0, (struct sockaddr*)&_client_addr, &_ssize); //On essaye de lire BUFFER_SIZE octets sur le socket

    if(bytes_received > 0) {
        _data_recvd = "";
        _data_recvd.append(_buffer, _buffer + bytes_received); //On ajoute ce qu'on a recu dans le string "result"
    }

    else {
        cerr << "socket error" << endl;
        _data_recvd = "";
    }

    return _data_recvd;
}

void DataReceiver::close_socket() {
    close(_serv_sock);
}
