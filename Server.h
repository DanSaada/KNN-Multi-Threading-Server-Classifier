//
// Created by Dansa on 31/12/2022.
//

#ifndef PROJECT_SERVER_H
#define PROJECT_SERVER_H

#include "Classify/ClassificationLogic.h"
#include "iostream"
#include <sys/socket.h>
#include <stdio.h>
#include "netinet/in.h"
#include "arpa/inet.h"
#include "unistd.h"
#include "string.h"
#include "Commands/SettingsCommand.h"
#include "Commands/Command.h"

class Server {
private:
    Database* database;
    int port;
    int sock;
public:
    int getSocket() const;
    void setSocket(int socket);
    void initializeSocket();
    explicit Server(Database* database, const string& port);
    string getClassifiction(string* brokeBuffer);
    void tcpSocket();
    bool breakBuffer(char *buffer, string* brokeBuffer);

};



#endif //PROJECT_SERVER_H
