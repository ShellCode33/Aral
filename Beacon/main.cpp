#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <utility>

#include "datasender.h"


#define BEACON //On se définit comme étant une balise afin de ne pas compiler ce qui ne nous concerne pas dans boat.h et boat.cpp
#include "../Common/boat.h"

const int MIN_LAT = 44.414753;
const int MAX_LAT = 45.522321;
const int MIN_LNG = 59.427795;
const int MAX_LNG = 59.878235;

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
    }

    switch (b.getHdirection()) {
    case EAST:
        lng += rand()/(RAND_MAX * 10.);
        break;
    case WEST:
        lng -= rand()/(RAND_MAX * 10.);
        break;
    }

    b.setLocation(lat, lng);

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
            b.setVdirection(static_cast<VDirection>(rand()%3 + 1));
            break;
        }
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
            b.setHdirection(static_cast<HDirection>(rand()%3 + 1));
            break;
        }
    }
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
    boat.setHdirection(static_cast<HDirection>(rand() % 3 + 1));
    boat.setVdirection(static_cast<VDirection>(rand() % 3 + 1));

    //position aléatoire dans le golf du mexique
    //45.522321 59.427795
    //44.414753 59.878235
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

