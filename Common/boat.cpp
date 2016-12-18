#include "boat.h"

using namespace std;

Boat::Boat(string name) : _name(name), _current_cap(NORTH)
{

}

void Boat::setLocation(double longitude, double latitude)
{
    _location.first = longitude;
    _location.second = latitude;
    _location_history.push_back(make_pair(longitude, latitude));
}

string Boat::getName() const
{
    return _name;
}

double Boat::getLatitude() const
{
    return _location.second;
}

double Boat::getLongitude() const
{
    return _location.first;
}

string Boat::toString() const
{
    string boat_string;
    boat_string.append(_name);
    boat_string.append(":");
    boat_string.append(to_string(getLongitude()));
    boat_string.append(":");
    boat_string.append(to_string(getLatitude()));
    boat_string.append(":");
    boat_string.append(_current_cap == NORTH ? "N" : (_current_cap == EAST ? "E" : (_current_cap == WEST ? "W" : "S")));
    boat_string.append(":");
    boat_string.append("4h20");
    return boat_string;
}

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
