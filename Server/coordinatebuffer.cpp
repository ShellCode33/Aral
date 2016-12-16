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
    _buffer.insert(_buffer.cbegin(), coord);
    if(_buffer.size() >= 100)
        _buffer.pop_back();
}

vector<Coordinates*> CoordinateBuffer::get_all_coordinates_of(unsigned int boat_id) {
    vector<Coordinates*> buf = vector<Coordinates*>();
    for(auto c : _buffer) {
        if(c->get_owner_id() == boat_id)
            buf.push_back(c);
    }
    return buf;
}

Coordinates* CoordinateBuffer::get_last_coordinate_of(unsigned int boat_id) {
    for(auto c : _buffer)
        if(c->get_owner_id() == boat_id)
            return c;
    return nullptr;
}
