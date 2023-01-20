//
// Created by tomer on 1/3/23.
//

#ifndef PROJECT_CLIENT_H
#define PROJECT_CLIENT_H

/* It's a class that represents a client that connects to a server and sends messages to it. */

#include <string>
#include "Client.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "fstream"
#include "../IOs/DefaultIO.h"
#include "../IOs/SocketIO.h"
#include "../IOs/StandardIO.h"

using namespace std;
class Client{
private:
    int clientSocket;
    int serverPort;
    const char *serverIpAddr;
    DefaultIO *dio;
    DefaultIO *printer;
public:
    explicit Client(const string& port, const char* ipAddr);
    bool uploadData(string route);
    void initializeSocket();
    void communicate();
    void Send(string toSend);
    void receive();

    int getSocket() const;

    void setSocket(int socket);
};



#endif //PROJECT_CLIENT_H