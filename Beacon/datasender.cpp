#include "datasender.h"

DataSender::DataSender()
    : serv_addr {0}, message {}
{
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_family = AF_INET;

    if (inet_aton(SERV_ADDR, &serv_addr.sin_addr)==0) {
        cerr << "inet_aton failed" << endl;
    }

    serv_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //création du socket
    if (serv_sock < 0)
    {
        cerr << "Can't create socket" << endl;
    }
}

void DataSender::send_string(string coordinates) {
    if(sendto(serv_sock, coordinates.c_str(), coordinates.length(), 0, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in)) < 0) //On envoie un paquet contenant la chaine de caractères
        cerr << "socket error" << endl;
}
