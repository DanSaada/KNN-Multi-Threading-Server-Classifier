//
// Created by dansa97 on 1/17/23.
//

#ifndef KNN_SERVER_CLIENTHANDLER_H
#define KNN_SERVER_CLIENTHANDLER_H

#include "../IOs/SocketIO.h"
#include "../IOs/CLI.h"


class ClientHandler {
private: int clientID;
public:
    ClientHandler(int id);
    void handle();
};


#endif //KNN_SERVER_CLIENTHANDLER_H
