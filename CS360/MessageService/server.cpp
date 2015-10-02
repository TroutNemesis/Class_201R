#include "server.h"

Server::Server(int port, int verbose) {
    // setup variables
    port_ = port;

    buflen_ = 1024;
    buf_ = new char[buflen_+1];
    verbose_ = verbose;
}

Server::~Server() {
    delete buf_;
}

void Server::run() {
    // create and run the server
    		cout << "\nentering create" << endl;

    create();
    		cout << "entering serve" << endl;
    		
    serve();
}

void Server::create() {
    struct sockaddr_in server_addr;

    // setup socket address structure
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // create socket
    server_ = socket(PF_INET,SOCK_STREAM,0);
    if (!server_) {
        perror("socket");
        exit(-1);
    }

    // set socket to immediately reuse port when the application closes
    int reuse = 1;
    if (setsockopt(server_, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("setsockopt");
        exit(-1);
    }

    // call bind to associate the socket with our local address and
    // port
    if (bind(server_,(const struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) {
        perror("bind");
        exit(-1);
    }

    // convert the socket to listen for incoming connections
    if (listen(server_,SOMAXCONN) < 0) {
        perror("listen");
        exit(-1);
    }
}

void Server::close_socket() {
    close(server_);
}

void Server::serve() {
    // setup client
    cout << "-start serve" << endl;
    int client;
    struct sockaddr_in client_addr;
    socklen_t clientlen = sizeof(client_addr);
    cout << "-In serve about to while" << endl;
      // accept clients
    while ((client = accept(server_,(struct sockaddr *)&client_addr,&clientlen)) > 0) 
    {
    	cout << "-serve while" << endl;
        handle(client);
    }
    cout << "-In serving leaving while about to close" << endl;
    close_socket();
}

void Server::handle(int client) 
{
    		cout << "--START___Handle___START--\n" << endl;
    int count = 0;		
    while (1) 
    {
        		cout << "--START___WHILE___START---------------------------------------------------------------------" << endl;
        
        string request = get_request(client);

        if (request.empty())
        {
        	cout << "request.empty() is empty" << endl;
            continue;
            //break;
        }

        bool success = handle_message(client);
        cout << "handle_message success == " << success << endl;

        		cout << "\n--END___WHILE___END---------------------------------------------------------------------" << endl;
    }

    		cout << "--END____Handle___END--" << endl;

    close(client);
}

string Server::readMessage(int client, int length)
{ 
	int count = length;
	int readChars = 0;
	string builder = "";

	while(1)
    {
    	if(count >= 1024)
    	{
    		readChars = 1024;
    	}
    	else
    	{
    		readChars = count;
    	}
        int n = recv(client,buf_, readChars,0);
        count -= n;
        if(count < 0){cout << "COUNT < 0: " << count << endl; return "";}
        char c = buf_[0];
        if (n < 0) 
        {
            if (errno == EINTR)
            {
                // the socket call was interrupted -- try again
                cout << "4: errno == EINTR" << endl;
                continue;
            }
            else
            {
                // an error occurred, so break out
                cout << "4: errno != EINTR" << endl;
                return "";
            }
        } 
        else if (n == 0) 
        {
            // the socket is closed
            cout << "4: socket is closed" << endl;
            return "";
        }
        builder.append(buf_,n);
        if(count == 0){break;}
    }
    return builder;
}

string Server::get_request(int client) 
{
    		cout << "-------START___get_request___START-------" << endl;
        
    Message message;
    int n;
    string builder = "";
    vector<string> params;
    string newline = "";
    int counter = 0;
    int current = 0;
    while(1)
    {
    			cout << "------1 WHILE START" << endl;

        int n = recv(client,buf_,1,0);
        char c = buf_[0];
        cout << "c == " << c << endl;
        if (n < 0) 
        {
            if (errno == EINTR)
            {
                // the socket call was interrupted -- try again
            	cout << "error 1: errno == EINTR" << endl; 
            	response = "error 1: errno == EINTR\n";
                continue;
            }
            else
            {
                // an error occurred, so break out
                cout << "error 1: errno != EINTR" << endl;
                response = "error 1: errno != EINTR\n"; 
                return "";
            }
        } 
        else if (n == 0) 
        {
            // the socket is closed
            cout << "error 1: socket is closed" << endl;
            response = "error 1: socket is closed\n";
            return "";
        }
        if(c == '\\')
        {
        	current = counter;
        	newline = "\\";
        	counter++;
        	continue;
        }
        if(newline == "\\" && c == 'n')
        {
        	if(counter - current == 1)
        	{
        		params.push_back(builder);
        		break;
        	}
        	else
        	{
        		newline = "";
        	}
        }
        if(c == ' ')
        {
        	params.push_back(builder);
        	builder = "";
        	counter++;
        	continue;
        }
        builder.append(buf_,n);
        counter++;
        cout << "------2 builder == " << builder << endl;
    }

    cout << "DONE PARSING THE INTERTUBES" << endl;

    if(params.size() == 0)
    {
    	cout << "error No comamand received" << endl;
    	response = "error No comamand received\n";
    	return ""; 
    }
	else if(params[0] == "put")
    {
    	if(params.size() != 4)
    	{
    		cout << "error Invalid put request. Expected 4 parms but were " << params.size() << endl;
    		response = "error Invalid put request. Expected 4 parms but were 4 " + params.size() + string("\n");
    		return "";
    	}
    	string command = params[0];
    	string name = params[1];
    	string subject = params[2];
    	string length = params[3];
    	string mess = readMessage(client, stoi(length));
    	message.setCommand(command);
    	message.setParams(subject, length);
    	message.setValue(mess);
    	if (users.find(name) == users.end()) 
    	{
    		vector<Message> empty;
		  	users[name] = empty;
		}
		users[name].push_back(message);
    	response = "OK\n";
    }
    else if(params[0] == "list")
    {
		if(params.size() != 2)
    	{
    		cout << "error Invalid list request. Expected 2 parms but were 2" << endl;
    		response = "error Invalid list request. Expected 2 parms but were 2\n";
    		return "";
    	}
    	string name = params[1];
    	if (users.find(name) == users.end())
    	{
    		cout << "error name " << name << " doesn't exist" << endl;
    		response = "error name " + name +" doesn't exist\n";
    		return "";
    	}
    	char buff[33];
    	response = "list " + users[name].size() + '\n'; 
    	for(int i = 1; i < users[name].size()+1; i++)
    	{
    		response += sprintf(buff,"%d",i) + " " + users[name][i-1].getParams()[0] + "\n";
    	}
    }
    else if(params[0] == "get")
    {
    	if(params.size() != 3)
    	{
    		cout << "error Invalid get request. Expected 3 parms but were 3" << endl;
    		response = "error Invalid get request. Expected 3 parms but were 3\n";
    		return "";
    	}
    	string name = params[1];
    	if (users.find(name) == users.end())
    	{
    		cout << "error name " << name << " doesn't exist" << endl;
    		response = "error name " + name +" doesn't exist\n";
    		return "";
    	}
    	int sizeOfVec = users[name].size();
    	int givenIndex = stoi(params[2])-1;
    	int plus1 = givenIndex+1;
    	char buff[33];
		if (sizeOfVec <= givenIndex || givenIndex < 0)
    	{
    		cout << "error index " << givenIndex + 1 << " doesn't exist" << endl;
    		response = "error index " + sprintf(buff,"%d",plus1) + string(" doesnt exist\n");
    		return "";
    	}
    	response = "message " + users[name][givenIndex].getParams()[0] + ' ' + users[name][givenIndex].getParams()[1] + '\n' + users[name][givenIndex].getValue();
    	//NOW IT IS SAFE TO GET AND FORMAT THE RESPONSE

    }
    else if(params[0] == "reset")
    {
    	if(params.size() != 1)
    	{
    		cout << "error Invalid reset request. Expected 1 parms but were 1" << endl;
    		response = "error Invalid get request. Expected 1 parms but were 1\n";
    		return "";
    	}
    	users.clear();
    }
    else
    {
    	cout << "error Invalid command request: " << params[0] << endl;
    	response = "error Invalid command request: " + params[0] + "\n";
    	return "";
    }
    		cout << "-------END___get_request___END-------" << endl;
    
    return "TRUE";
}

bool Server::handle_message(int client)
{
 // prepare to send response
    const char* ptr = response.c_str();
    int nleft = response.length();
    int nwritten;
    // loop to be sure it is all sent
    while (nleft) 
    {
        if ((nwritten = send(client, ptr, nleft, 0)) < 0) 
        {
            if (errno == EINTR) 
            {
                // the socket call was interrupted -- try again
                continue;
            } 
            else 
            {
                // an error occurred, so break out
                perror("write");
                return false;
            }
        } 
        else if (nwritten == 0) 
        {
            // the socket is closed
            return false;
        }
        nleft -= nwritten;
        ptr += nwritten;
    }
    return true;
}


// bool Server::send_response(int client, string response) 
// {
//     // prepare to send response
//     const char* ptr = response.c_str();
//     int nleft = response.length();
//     int nwritten;
//     // loop to be sure it is all sent
//     while (nleft) 
//     {
//         if ((nwritten = send(client, ptr, nleft, 0)) < 0) 
//         {
//             if (errno == EINTR) 
//             {
//                 // the socket call was interrupted -- try again
//                 continue;
//             } 
//             else 
//             {
//                 // an error occurred, so break out
//                 perror("write");
//                 return false;
//             }
//         } 
//         else if (nwritten == 0) 
//         {
//             // the socket is closed
//             return false;
//         }
//         nleft -= nwritten;
//         ptr += nwritten;
//     }
//     return true;
// }