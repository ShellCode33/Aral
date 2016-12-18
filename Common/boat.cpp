#include "boat.h"

using namespace std;

Boat::Boat(string name) : _name(name), _current_cap(NORTH)
{

}

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

Cap Boat::getCap() const
{
    return _current_cap;
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
    boat_string.append(_current_cap == NORTH ? "N" : (_current_cap == EAST ? "E" : (_current_cap == WEST ? "W" : "S")));
    boat_string.append(":");
    boat_string.append("4h20");
    return boat_string;
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

void Boat::setCap(Cap cap)
{
    _current_cap = cap;
}

void Boat::setTime(const string & time)
{
    _last_time_receiving = time;
}

Boat* Boat::create(const string &boat_string)
{
    vector<string> result;
    processBoatString(boat_string, result);

    Boat *boat = new Boat(result.at(0));
    boat->setLocation(stod(result.at(1)), stod(result.at(2)));
    boat->setCap(result.at(3) == "N" ? NORTH : (result.at(3) == "E" ? EAST : (result.at(3) == "W" ? WEST : SOUTH)));
    boat->setTime(result.at(4));

    return boat;
}
#endif
