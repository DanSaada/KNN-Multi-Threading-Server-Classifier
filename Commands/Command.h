//
// Created by tomer on 1/11/23.
//

#ifndef KNN_SERVER_COMMAND_H
#define KNN_SERVER_COMMAND_H

#include "../IO's/DefaultIO.h"
#include <string>
#include "../Classify/Database.h"

using namespace std;
class Command {
private:
    string description;
    DefaultIO* dio;
public:
    virtual void execute(Info* info) =0;

};


#endif //KNN_SERVER_COMMAND_H
