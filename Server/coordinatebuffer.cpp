#include "coordinatebuffer.h"

vector<Coordinates*> CoordinateBuffer::_buffer = vector<Coordinates*>();

CoordinateBuffer::CoordinateBuffer()
{

}

CoordinateBuffer::~CoordinateBuffer() {
    for(auto c : _buffer)
        delete c;
}

void CoordinateBuffer::save_coordinates(Coordinates* coord) {
    if(_buffer.size() < 100)
        _buffer.push_back(coord);
}

vector<Coordinates*> CoordinateBuffer::get_boat_coordinates(unsigned int boat_id) {
    vector<Coordinates*> buf = vector<Coordinates*>();
    for(auto c : _buffer) {
        if(c->get_owner_id() == boat_id)
            buf.push_back(c);
    }
    return buf;
}
