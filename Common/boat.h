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
    void setLocation(double latitude, double longitude);
    double getLatitude() const;
    double getLongitude() const;
    std::string toString() const;
    std::string getName() const;
    Cap getCap() const;
    std::string capToString(Cap cap) const;
    void setCap(Cap cap);
#ifndef BEACON
    std::string getLastTimeReceiving() const;
    void setTime(const std::string & time);
    static Boat * create(const std::string & boat_string);
#endif
private:
    std::string _name;
    Cap _current_cap;
    std::pair<double, double> _location;

#ifndef BEACON
    std::vector<std::pair<double, double>> _location_history;
    std::string _last_time_receiving;
    static void processBoatString(const std::string &boat_string, std::vector<std::string> & result);
#endif
};

#endif // BOAT_H
