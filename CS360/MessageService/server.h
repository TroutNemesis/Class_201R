#pragma once

#include <sstream>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Message.h"
#include <iostream>
#include <cmath>

#include <vector>
#include <string>
#include <map>

using namespace std;

class Server {
public:
    Server(int port, int verbose);
    ~Server();
    void run();
    
private:
    void create();
    void close_socket();
    void serve();
    void handle(int);
    string get_request(int);
    //bool send_response(int, string);
    //Message parse_request(string request);
    bool handle_message(int client);
    //void get_value(int client, Message &message);
    string readMessage(int socket, int length);


    map<string, vector<Message>> users;
    vector<Message> messages;
    int port_;
    int server_;
    int buflen_;
    char* buf_;
    int verbose_;
    string response;
};