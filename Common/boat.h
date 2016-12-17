#ifndef BOAT_H
#define BOAT_H

#include <iostream>
#include <vector>

enum Cap {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

class Boat
{
public:
    Boat(std::string name);
    void setLocation(double longitude, double latitude);
    double getLatitude() const;
    double getLongitude() const;
    std::string toString() const;
    std::string getName() const;
private:
    std::string _name;
    Cap _current_cap;
    std::pair<double, double> _location;
    std::vector<std::pair<double, double>> _location_history;
    std::string _last_time_receiving;
};

#endif // BOAT_H
