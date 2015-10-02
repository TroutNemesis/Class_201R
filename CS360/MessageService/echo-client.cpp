#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

#include "client.h"

using namespace std;

int main(int argc, char **argv)
{
    int flagH, opt;
    int port, flagP;
    string host;

    port = 0;
    flagP = 0;
    flagH = 0;
    while ((opt = getopt(argc, argv, "hp:")) != -1) {
        switch (opt) {
        case 'h':
            flagH = 1;
            host = optarg;
            break;
        case 'p':
            port = atoi(optarg);
            flagP = 1;
            break;
        default: /* '?' */
            fprintf(stderr, "client [-h host] [-p port]\n");
        }
    }

    printf("flagH=%d; flagP=%d; optind=%d\n", flagH, flagP, optind);

    if(flagP == 0 && flagH ==0){port = 3000; host = "localhost";}
    cout << "Enter client constructor" << endl;
    Client client = Client(host, port);
    cout << "client.run()" << endl;
    client.run();
}