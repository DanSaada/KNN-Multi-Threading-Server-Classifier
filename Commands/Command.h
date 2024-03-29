//
// Created by tomer on 1/11/23.
//

#ifndef KNN_SERVER_COMMAND_H
#define KNN_SERVER_COMMAND_H

#include "../IOs/DefaultIO.h"
#include <string>
#include "../Classify/Database.h"

using namespace std;
class Command {
private:
    string description;
protected:
    DefaultIO* dio;

public:
    //destructor
    virtual ~Command() = default;

    virtual void execute(Info* info) =0;

    const string &getDescription() const;

    void setDescription(const string &description);

    void setDio(DefaultIO *dio);
};
#endif //KNN_SERVER_COMMAND_H
