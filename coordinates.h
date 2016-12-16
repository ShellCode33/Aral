#ifndef COORDINATES_H
#define COORDINATES_H

#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

enum Cap {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

class Coordinates {

private:
    double _latitude;
    double _longitude;
    Cap _cap;
    std::string _time; // heure de l'envoi de la coordonnée
    std::string _owner_id;

public:
    Coordinates(double latitude, double longitude, Cap cap, std::string timee, std::string id);
    Coordinates(); // renvoie une coordonnée random -- utiles pour les tests

    double get_latitude() const;
    double get_longitude() const;
    Cap get_cap() const;
    unsigned int get_owner_id() const;

    std::string toString();
};

#endif // COORDINATES_H
