#include "boat.h"

using namespace std;

Boat::Boat(string name) : _name(name)
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
    return _name + ":" + to_string(getLongitude()) + ":" + to_string(getLatitude()) + ":" + to_string(_current_cap) + ":" + "4h20";
}
