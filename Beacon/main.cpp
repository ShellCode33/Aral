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

    Clock timer = Clock();
    DataSender* sender = new DataSender();
    timer.set_alarm(Moment(0, 0, 1, 0, 0));
    timer.start();

    while(1) {
        timer.check_time();
        if(timer.has_ticked()) {
            timer.reset();
            sender->send_string(Coordinates().toString());
        }
    }

    delete sender;
    return 0;
}

