#include <stdlib.h>
#include <unistd.h>

#include <iostream>

#include "server.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

int main(int argc, char **argv)
{
	cout << "\nStarting echo-server main" << endl;

	int flags, opt;
	int port, tfnd;
	port = 0;
	tfnd = 0;
	flags = 0;
	while ((opt = getopt(argc, argv, "dp:")) != -1) 
	{
		cout << "opt == " << (char)opt << endl;
		switch (opt) 
		{
		case 'd':
		   flags = 1;
		   break;
		case 'p':
		   port = atoi(optarg);
		   tfnd = 1;
		   break;
		default: /* '?' */
		   fprintf(stderr, "Usage: %s [-p port] [-d]\n", argv[0]);
		   exit(EXIT_FAILURE);
	    }
	}
	printf("flags=%d; tfnd=%d; optind=%d\n", flags, tfnd, optind);

	if(tfnd == 0){port = 3000;}

    cout << "Start Port Number: " << port << endl;
    cout << "Verbosity == " << flags << endl;
    Server server = Server(port, flags);
    server.run();
}