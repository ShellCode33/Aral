#include <iostream>
#include "serverhandler.h"

using namespace std;

int main()
{
    ServerHandler handler = ServerHandler();
    string buffer;

    while(1) {
        handler.init_send_socket();
        handler.send_request(fgets((char*)buffer.c_str(), BUFFER_SIZE - 1 , stdin));

        handler.close_sockets();
        handler.init_receive_socket();
        buffer = handler.receive_data();
        while(buffer != ":END:")
            cout << buffer << endl;
        handler.close_sockets();
    }

    return 0;
}
