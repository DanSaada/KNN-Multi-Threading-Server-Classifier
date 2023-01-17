//
// Created by dansa97 on 1/17/23.
//

#include "ClientHandler.h"

void ClientHandler::handle(int clientID) {
    auto* io = new SocketIO(clientID);
    CLI* cli = new CLI(io);
    cli->start();

    delete cli;
    delete io;
}
