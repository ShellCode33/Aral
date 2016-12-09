#include <iostream>
#include "serverhandler.h"

using namespace std;

int main()
{
    ServerHandler handler = ServerHandler();

    handler.send_message("Coucou serveur!");

    return 0;
}
