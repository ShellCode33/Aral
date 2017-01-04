#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <utility>

#include "datasender.h"
#include "../Common/boat.h"

const double MIN_LAT = 44.414753;
const double MAX_LAT = 45.522321;
const double MIN_LNG = 59.427795;
const double MAX_LNG = 59.878235;

using namespace std;

double random_range(double min, double max)
{
    return min + (double)rand() / RAND_MAX * (max - min);
}

void updateBoat(Boat &b)
{
    double lat = b.getLatitude();
    double lng = b.getLongitude();

    switch (b.getVdirection()) {
    case NORTH:
        lat -= rand()/(RAND_MAX * 10.);
        break;
    case SOUTH:
        lat += rand()/(RAND_MAX * 10.);
        break;
    default: break;
    }

    switch (b.getHdirection()) {
    case EAST:
        lng += rand()/(RAND_MAX * 10.);
        break;
    case WEST:
        lng -= rand()/(RAND_MAX * 10.);
        break;
    default: break;
    }

    bool is_allowed_position = true;

    if(lat < MIN_LAT || lat > MAX_LAT)
    {
        switch (b.getVdirection()) {
        case NORTH:
            b.setVdirection(SOUTH);
            break;
        case SOUTH:
            b.setVdirection(NORTH);
            break;
        default:
            b.setVdirection(static_cast<VDirection>(rand()%3));
            break;
        }

        is_allowed_position = false;
    }

    if(lng < MIN_LNG || lng > MAX_LNG)
    {
        switch (b.getHdirection()) {
        case EAST:
            b.setHdirection(WEST);
            break;
        case WEST:
            b.setHdirection(EAST);
            break;
        default:
            b.setHdirection(static_cast<HDirection>(rand()%3));
            break;
        }

        is_allowed_position = false;
    }

    if(is_allowed_position)
        b.setLocation(lat, lng);
}

int main(int argc, char **argv)
{
    if(argc < 2)
    {
       cerr << "Usage : " << argv[0] << " [boat_name]" << endl;
       exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    Boat boat(argv[1]);
    boat.setHdirection(static_cast<HDirection>(rand() % 3));

    if(boat.getHdirection() == H_NONE) //Si HDirection est à NONE, on ne permet pas que Vdirection le soit
        boat.setVdirection(static_cast<VDirection>(rand() % 2));

    else
        boat.setVdirection(static_cast<VDirection>(rand() % 3));

    boat.setLocation(random_range(MIN_LAT, MAX_LAT), random_range(MIN_LNG, MAX_LNG));

    DataSender sender;

    while(1)
    {
        sender.send_string(boat.toString());

        updateBoat(boat);

        sleep(1);
    }

    return 0;
}

