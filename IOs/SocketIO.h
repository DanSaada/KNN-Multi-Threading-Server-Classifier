//
// Created by dansa97 on 1/12/23.
//

#ifndef KNN_SERVER_SOCKETIO_H
#define KNN_SERVER_SOCKETIO_H
#include "DefaultIO.h"
#include "iostream"
#include <sys/socket.h>
#include <stdio.h>
#include "netinet/in.h"
#include "arpa/inet.h"
#include "unistd.h"
#include "string.h"
#include <mutex>
#include <thread>

class SocketIO : public DefaultIO{
private:
    mutex writeMutex;
public:
    explicit SocketIO(int id);

    string  read() override;

    void write(string toSend) override;
};


#endif //KNN_SERVER_SOCKETIO_H
