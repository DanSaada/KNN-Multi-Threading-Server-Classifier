//
// Created by dansa97 on 1/17/23.
//

#ifndef KNN_SERVER_CLIENTHANDLER_H
#define KNN_SERVER_CLIENTHANDLER_H

#include "IO's/SocketIO.h"
#include "IO's/CLI.h"


class ClientHandler {
public:
    void handle(int clientID);
};


#endif //KNN_SERVER_CLIENTHANDLER_H
