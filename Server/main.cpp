#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#include "datareceiver.h"

using namespace std;

int main(int argc, char **argv) {

    DataReceiver receiver = DataReceiver();
    string received = "";

    while(1) {
        received = receiver.receive_string();
        cout << "Received: " << received << endl;
        received = "";
    }
}
