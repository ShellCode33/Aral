#include "boat.h"

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
    default: break;
    }

    if(cap.length() > 0)
        cap += " ";

    switch (_hdirection) {
    case EAST:
        cap += "EAST";
        break;
    case WEST:
        cap += "WEST";
        break;
    default:
        cap.erase(cap.begin() + cap.length(), cap.end()); //On enlève l'espace de la fin
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
    //current time
    auto t = time(nullptr);
    auto tm = *localtime(&t);

    std::ostringstream oss;
    oss << put_time(&tm, "%d-%m-%Y %H-%M-%S");
    string time = oss.str();


    string boat_string;
    boat_string.append(_name);
    boat_string.append(":");
    boat_string.append(to_string(getLatitude()));
    boat_string.append(":");
    boat_string.append(to_string(getLongitude()));
    boat_string.append(":");
    boat_string.append(capToString());
    boat_string.append(":");
    boat_string.append(time);
    return boat_string;
}

string Boat::getLastTimeReceiving() const
{
    return _last_time_receiving;
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

    boat->setLocation(lat, longi);
    boat->setCap(result.at(3));
    boat->setTime(result.at(4));

    return boat;
}

VDirection Boat::getVdirection() const
{
    return _vdirection;
}

void Boat::setCap(const VDirection &vdirection, const HDirection &hdirection)
{
    _vdirection = vdirection;
    _hdirection = hdirection;
}

//permet de définir le cap à partir d'une chaine de caractère, exemple : "NORTH EAST"
void Boat::setCap(const string & cap)
{
    _vdirection = V_NONE;
    _hdirection = H_NONE;

    if(cap.length() <= 0)
        return;

    string part1, part2;

    unsigned int i;
    for(i = 0; i < cap.length() && cap[i] != ' '; i++)
        part1 += cap[i];

    for(i++; i < cap.length(); i++)
        part2 += cap[i];

    if(part1 == "NORTH")
        _vdirection = NORTH;
    else if(part1 == "SOUTH")
        _vdirection = SOUTH;

    if(part1 == "EAST" || part2 == "EAST")
        _hdirection = EAST;
    else if(part1 == "WEST" || part2 == "WEST")
        _hdirection = WEST;
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
