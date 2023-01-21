//
// Created by Dansa on 31/12/2022.
//

#include "Server.h"

/**
 * Constructor of Server
 * @param port port of the server
 */
Server::Server(const string &port) {
    this->port = stoi(port);
    setSocket(socket(AF_INET, SOCK_STREAM, 0));
    initializeSocket();
}

/**
 * It returns the socket of the client.
 *
 * @return The client socket.
 */
int Server::getSocket() const {
    return this->sock;
}

/**
 * This function sets the clientSocket variable to the socket passed in as a parameter.
 *
 * @param socket The socket that the client is connected to.
 */
void Server::setSocket(int socket) {
    this->sock = socket;
}

/**
 * This function creates a socket and connects it to the server
 */
void Server::initializeSocket() {

    //checking creation succeed
    if (sock < 0) {
        exit(1);
    }

    //for sending a group of parameters and get them back we create a struct
    struct sockaddr_in sin;
    //nullify the struct
    memset(&sin, 0, sizeof(sin));
    //initialize the struct fields
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);

    //bind server to the port and check succeed
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        exit(1);
    }

    //setting to let up to 5 clients waiting
    if (listen(sock, 5) < 0) {
        exit(1);
    }

}

/**
 * This function implements a TCP socket connection protocol between a client and a server.
 */
void Server::tcpSocket() {
    vector<thread *> tVec;
    while (true) {
        //accept an incoming Client connection
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
        if (client_sock < 0) {
            break;
        }else{
            //////option 1:
            auto *client = new thread([client_sock]() {
                auto *ch = new ClientHandler(client_sock);
                ch->handle();
                close(client_sock);
            });
            tVec.push_back(client);
        }
    }

    //wait for all threads to finish their work and delete them
    for (auto client: tVec) {
        client->join();
        delete client;
    }
    //close the connection
    close(sock);
}

/**
 * The main function creates a Database object, and then get a new inserted vector.
 * It then finds the k nearest neighbors of that vector and classified the inserted vector
 * to be of the same classification as the biggest group inside the k nearest neighbors.
 * @param argc the number of arguments
 * @param argv the file and the port
 */
int main(int argc, char const *argv[]) {
    //checking validation of arguments.
    if (argc != 2) {
        exit(1);
    }
    //checking validation of port
    if (!isPositiveInteger(argv[1]) || stoi(argv[1]) <= 0 || stoi(argv[1]) > 65535) {
        exit(1);
    }
    //create a server and start a connection
    auto *server = new Server(argv[1]);
    server->tcpSocket();
    return 0;
}