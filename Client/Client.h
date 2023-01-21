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
#include <thread>

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

    int getSocket() const;

    void setSocket(int socket);

    static void downloadData(string route, string data);

    void uploadDataCommandClientSide();

    void settingCommandClientSide();

    void classifyAndDisplayCommandsClientSide();

    void downloadResultsCommandClientSide();
};



#endif //PROJECT_CLIENT_H