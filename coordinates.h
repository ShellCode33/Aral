#ifndef COORDINATES_H
#define COORDINATES_H

#include<string>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

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
    string _time; // heure de l'envoi de la coordonnée
    string _owner_id;

public:
    Coordinates(double latitude, double longitude, Cap cap, string timee, string id);
    Coordinates(); // renvoie une coordonnée random -- utiles pour les tests

    double get_latitude();
    double get_longitude();
    Cap get_cap();

    string toString();
};

#endif // COORDINATES_H
