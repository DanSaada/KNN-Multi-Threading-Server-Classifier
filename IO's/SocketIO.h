//
// Created by dansa97 on 1/12/23.
//

#ifndef KNN_SERVER_SOCKETIO_H
#define KNN_SERVER_SOCKETIO_H
#include "DefaultIO.h"

class SocketIO : public DefaultIO{
public:
    string  read() override;
    void write(string output) override;
};


#endif //KNN_SERVER_SOCKETIO_H
