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

string Boat::capToString() const
{
    return _current_cap == NORTH ? "NORTH" : (_current_cap == EAST ? "EAST" : (_current_cap == WEST ? "WEST" : "SOUTH"));
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
    std::cout << boat_string << std::endl;
    vector<string> result;
    processBoatString(boat_string, result);

    Boat *boat = new Boat(result.at(0));

    double lat, longi;
    istringstream i(result.at(1));
    i >> lat;

    istringstream i1(result.at(2));
    i1 >> longi;

/*
    QLocale c(QLocale::C); //Obligé de passer par la librairie de QT pour la conversion string -> double car en mode release le resultat n'est pas le même qu'en debug
    double lat = c.toDouble(result.at(1).c_str());
    double longi = c.toDouble(result.at(2).c_str());
*/
    boat->setLocation(lat, longi);
    boat->setCap(result.at(3) == "NORTH" ? NORTH : (result.at(3) == "EAST" ? EAST : (result.at(3) == "WEST" ? WEST : SOUTH)));
    boat->setTime(result.at(4));

    return boat;
}
#endif
