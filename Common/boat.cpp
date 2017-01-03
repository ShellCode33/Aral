#include "boat.h"

#include <sstream>

using namespace std;

Boat::Boat(string name) : _name{name}
{}

void Boat::setLocation(double latitude, double longitude)
{
    _location.first = latitude;
    _location.second = longitude;
    _location_history.push_back(make_pair(latitude, longitude));
}

string Boat::getName() const
{
    return _name;
}

string Boat::capToString() const
{
    string cap = "";

    switch (_vdirection) {
    case NORTH:
        cap += "NORTH";
        break;
    case SOUTH:
        cap += "SOUTH";
        break;
    }

    cap += " ";

    switch (_hdirection) {
    case EAST:
        cap += "EAST";
        break;
    case WEST:
        cap += "WEST";
        break;
    }

    return cap;
}

double Boat::getLatitude() const
{
    return _location.first;
}

double Boat::getLongitude() const
{
    return _location.second;
}

string Boat::toString() const
{
    string boat_string;
    boat_string.append(_name);
    boat_string.append(":");
    boat_string.append(to_string(getLatitude()));
    boat_string.append(":");
    boat_string.append(to_string(getLongitude()));
    boat_string.append(":");
    boat_string.append(capToString());
    boat_string.append(":");
    boat_string.append("4h20");
    return boat_string;
}

string Boat::getLastTimeReceiving() const
{
    return _last_time_receiving;
}

#ifndef BEACON
//static
void Boat::processBoatString(const string & boat_string, vector<string> & result)
{
    string current;

    for(int i = 0; i < (int)boat_string.length(); i++)
    {
        char c = boat_string.at(i);

        if(c != ':')
            current += c;

        else
        {
            result.push_back(current);
            current.clear();
        }
    }

    result.push_back(current);
}

void Boat::setTime(const string & time)
{
    _last_time_receiving = time;
}

Boat* Boat::create(const string &boat_string)
{
    std::cout << boat_string << std::endl;
    vector<string> result;
    processBoatString(boat_string, result);

    Boat *boat = new Boat(result.at(0));

    std::istringstream ilat{result.at(1)};
    double lat;
    if (!(ilat >> lat))
        lat = 0;

    std::istringstream ilongi{result.at(2)};
    double longi;
    if (!(ilongi>> longi))
        longi = 0;

    boat->setLocation(lat, longi);
    //boat->setCap(result.at(3) == "NORTH" ? NORTH : (result.at(3) == "EAST" ? EAST : (result.at(3) == "WEST" ? WEST : SOUTH)));
    boat->setTime(result.at(4));

    return boat;
}

VDirection Boat::getVdirection() const
{
    return _vdirection;
}

void Boat::setVdirection(const VDirection &vdirection)
{
    _vdirection = vdirection;
}

HDirection Boat::getHdirection() const
{
    return _hdirection;
}

void Boat::setHdirection(const HDirection &hdirection)
{
    _hdirection = hdirection;
}
#endif
