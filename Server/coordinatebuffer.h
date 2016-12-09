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

    static vector<Coordinates *> get_boat_coordinates(unsigned int boat_id);

    static void save_coordinates(Coordinates *coord);

};

#endif // COORDINATEBUFFER_H
