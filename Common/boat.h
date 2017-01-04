#ifndef BOAT_H
#define BOAT_H

#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <iomanip>
#include <ctime>

enum VDirection {
    NORTH,
    SOUTH,
    V_NONE
};

enum HDirection{
    EAST,
    WEST,
    H_NONE
};

class Boat
{
public:
    Boat(std::string name);
    void setLocation(double latitude, double longitude);
    double getLatitude() const;
    double getLongitude() const;
    std::string toString() const;
    std::string getName() const;
    std::string capToString() const;

    VDirection getVdirection() const;
    void setVdirection(const VDirection &vdirection);

    HDirection getHdirection() const;
    void setHdirection(const HDirection &hdirection);
    void setCap(const VDirection &vdirection, const HDirection &hdirection);
    void setCap(const std::string & cap);

    std::string getLastTimeReceiving() const;
    void setTime(const std::string & time);
    static Boat * create(const std::string & boat_string);
    static void processBoatString(const std::string &boat_string, std::vector<std::string> & result);

private:
    std::string _name;
    VDirection _vdirection;
    HDirection _hdirection;
    std::pair<double, double> _location;
    std::vector<std::pair<double, double>> _location_history;
    std::string _last_time_receiving;
};

#endif // BOAT_H
