#include "beaconshandler.h"

using namespace std;

BeaconsHandler::BeaconsHandler() : Server(UDP)
{
    //On créait de faux bateaux pour les test
    for(int i = 0; i < 10; i++)
        _boats.push_back(new Boat("Boat " + to_string(i)));
}

string BeaconsHandler::receive_string()
{
    char *buffer = new char[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    socklen_t c = sizeof(struct sockaddr);
    struct sockaddr sender;
    int bytes_received = recvfrom(_serv_sock, buffer, BUFFER_SIZE-1, 0, (struct sockaddr*)&sender, &c); //On essaye de lire BUFFER_SIZE octets sur le socket

    string str(buffer);

    if(bytes_received <= 0)
        cerr << "socket error" << endl;

    return str;
}

Boat* BeaconsHandler::create_boat(const string & beacon_string) const
{
    Boat *boat = new Boat(beacon_string);

    //parse boat_string

    /*
    string id = coord.substr(0, coord.find_first_of("="));
    double latitude = atof(coord.substr(coord.find_first_of("="), 9).c_str());
    double longitude = atof(coord.substr(coord.find_first_of(","), 9).c_str());
    Cap cap;
    string capstr = coord.substr(coord.find_first_of(";"), 1);
    if(capstr == "N")
        cap = NORTH;
    else if(capstr == "E")
        cap = EAST;
    else if(capstr == "S")
        cap = SOUTH;
    else
        cap = WEST;
    string time = coord.substr(coord.find_first_of("/"), 8);

    // on ne stocke que COORDINATES_STORED coordonnées maximum
    //CoordinateBuffer::save_coordinates(new Coordinates(latitude, longitude, cap, time, id));
    */

    return boat;
}

void BeaconsHandler::start()
{
    cout << "BeaconsHandler looping..." << endl;

    while(true)
    {
        cout << "Received: " << receive_string() << endl;
    }
}
