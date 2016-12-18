#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */

#include "datasender.h"

#define BEACON //On se définit comme étant une balise afin de ne pas compiler ce qui ne nous concerne pas dans boat.h et boat.cpp
#include "../Common/boat.h"

using namespace std;

int main(int argc, char **argv)
{
    if(argc < 2)
    {
       cerr << "Usage : " << argv[0] << " [boat_name]" << endl;
       exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    Boat boat(argv[1]);
    boat.setCap(static_cast<Cap>(rand() % 4 + 1));

    //position aléatoire dans l'océan pacifique
    //latitude de 30 à 14
    //longitude de 123 à 150
    double latitude = 14 + ( rand() % ( 30 - 14 + 1 ) );
    double longitude = 123 + ( rand() % ( 150 - 123 + 1 ) );
    boat.setLocation(latitude, longitude);


    DataSender sender;

    while(1)
    {
        sender.send_string(boat.toString());
        sleep(1);
    }

    return 0;
}

