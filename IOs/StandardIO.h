//
// Created by dansa97 on 1/12/23.
//

#ifndef KNN_SERVER_STANDARDIO_H
#define KNN_SERVER_STANDARDIO_H

#include "DefaultIO.h"

//StandardIO - interaction with the user using the console.
class StandardIO : public DefaultIO{
public:
    string  read() override;
    void write(string output) override;
};


#endif //KNN_SERVER_STANDARDIO_H
