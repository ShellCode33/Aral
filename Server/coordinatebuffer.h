#ifndef COORDINATEBUFFER_H
#define COORDINATEBUFFER_H

#include <vector>
#include <iostream>
#include <string>

#include "../coordinates.h"

using namespace std;

class CoordinateBuffer
{
private:
    static vector<Coordinates*> _buffer;

public:
    CoordinateBuffer();
    ~CoordinateBuffer();

    static vector<Coordinates *> get_all_coordinates_of(unsigned int boat_id);
    static Coordinates* get_last_coordinate_of(unsigned int boat_id);

    static void save_coordinates(Coordinates *coord);
    static void clear_coordinates();

};

#endif // COORDINATEBUFFER_H
