#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */

#include "datasender.h"
#include "coordinates.h"
#include "clock.h"

using namespace std;

int main(int argc, char **argv) {

    if(argc < 2) {
       cerr << "Usage ./beacon [boat_id]";
       exit(EXIT_FAILURE);
    }

    string BOAT_ID = argv[1];

    DataSender* sender = new DataSender();

    Clock timer = Clock();
    timer.set_alarm(Moment(0, 0, 2, 0, 0));
    timer.start();

    while(1) {
        timer.check_time();
        if(timer.has_ticked()) {
            timer.reset();
            sender->send_string(BOAT_ID + "/" + Coordinates().toString());
        }
    }

    sender->close_socket();

    delete sender;
    return 0;
}

