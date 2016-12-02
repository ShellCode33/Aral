#include "datasender.h"

DataSender::DataSender()
    : _serv_addr {0}, _message {}
{
    _serv_addr.sin_port = htons(PORT);
    _serv_addr.sin_family = AF_INET;

    if (inet_aton(SERV_ADDR, &_serv_addr.sin_addr)==0) {
        cerr << "inet_aton failed" << endl;
    }

    _serv_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //création du socket
    if (_serv_sock < 0) {
        cerr << "Can't create socket" << endl;
    }
}

void DataSender::send_string(string coordinates) {
    if(sendto(_serv_sock, coordinates.c_str(), coordinates.length(), 0, (struct sockaddr *)&_serv_addr, sizeof(struct sockaddr_in)) < 0) //On envoie un paquet contenant la chaine de caractères
        cerr << "socket error" << endl;
}

void DataSender::close_socket() {
    close(_serv_sock);
}
