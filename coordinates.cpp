#include "coordinates.h"

Coordinates::Coordinates(double latitude, double longitude, Cap cap, string timee, string id)
    : _latitude{latitude}, _longitude{longitude}, _cap{cap}, _time {}, _owner_id{id}
{
    srand(time(NULL));
}

Coordinates::Coordinates()
{
    time_t date_time = time(0);
    _latitude = rand() % 181; // 0 -- 180
    (rand() % 2 == 0 ? _latitude *= -1 : _latitude);
    _longitude = rand() % 181; // 0 -- 180
    (rand() % 2 == 0 ? _longitude *= -1 : _longitude);
    _cap = NORTH;
    _time = asctime(localtime(&date_time));
    _time = _time.substr(11, 8);
}

double Coordinates::get_latitude() const {
    return this->_latitude;
}

double Coordinates::get_longitude() const{
    return this->_longitude;
}

Cap Coordinates::get_cap() const{
    return this->_cap;
}

unsigned int Coordinates::get_owner_id() const {
    return stoi(this->_owner_id);
}

string Coordinates::toString() {
    string str =  to_string(_latitude) + ","
            + to_string(_longitude) + ";";
    if(this->_cap == NORTH)
        str += "N";
    else if(this->_cap == EAST)
        str += "E";
    else if(this->_cap == SOUTH)
        str += "S";
    else if(this->_cap == WEST)
        str += "W";
    str += "/" + _time;
    return str;
}
