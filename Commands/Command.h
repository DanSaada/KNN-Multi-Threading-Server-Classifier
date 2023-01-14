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
protected:
    DefaultIO* dio;
    Command(string& d,DefaultIO *defaultIo):description{d},dio(defaultIo){}
public:
    virtual void execute(Info* info) =0;

    const string &getDescription() const;
};


#endif //KNN_SERVER_COMMAND_H
