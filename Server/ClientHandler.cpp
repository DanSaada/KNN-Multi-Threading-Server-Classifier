//
// Created by dansa97 on 1/17/23.
//

#include "ClientHandler.h"

/**
 * Constructor of ClientHandler
 * @param id the socket of the client
 */
ClientHandler::ClientHandler(int id) {
    this->clientID = id;
}

/**
 * This function handle a specific client's orders.
 * */
void ClientHandler::handle() {
    auto* io = new SocketIO(clientID);
    CLI* cli = new CLI(io);
    cli->start();

    delete cli;
    delete io;
}

