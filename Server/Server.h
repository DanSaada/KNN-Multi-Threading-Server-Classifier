//
// Created by Dansa on 31/12/2022.
//

#ifndef PROJECT_SERVER_H
#define PROJECT_SERVER_H

#include "../Classify/Database.h"
#include "../Distances/Distance.h"
#include "../Distances/Euclidean.h"
#include "../Distances/Manhattan.h"
#include "../Distances/Chebyshev.h"
#include "../Distances/Canberra.h"
#include "../Distances/Minkowski.h"
#include "cstring"
#include "iostream"
#include <sys/socket.h>
#include <stdio.h>
#include "netinet/in.h"
#include "arpa/inet.h"
#include "unistd.h"
#include "string.h"
#include "../Commands/SettingsCommand.h"
#include "../Commands/Command.h"
#include <thread>
#include "ClientHandler.h"
#include <queue>
#include <cstdio>
#include <unistd.h>
#include <condition_variable>



class Server {
private:
    Database* database;
    int port;
    int sock;
public:

    int getSocket() const;

    void setSocket(int socket);

    void initializeSocket();

    explicit Server(const string& port);

    void tcpSocket();

    static void handleQueue();

    static void clientHandler(int client_sock);

};

bool isPositiveInteger(const string &s);


#endif //PROJECT_SERVER_H
