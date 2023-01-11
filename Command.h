//
// Created by tomer on 1/11/23.
//

#ifndef KNN_SERVER_COMMAND_H
#define KNN_SERVER_COMMAND_H

#include "DefaultIO.h"
#include <string>

using namespace std;
class Command {
private: string description;
         DefaultIO dio;
public: virtual void execute();
};


#endif //KNN_SERVER_COMMAND_H
