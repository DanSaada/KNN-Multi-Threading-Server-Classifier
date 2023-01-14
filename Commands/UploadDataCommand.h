//
// Created by dansa97 on 1/11/23.
//

#ifndef KNN_SERVER_UPLOADDATACOMMAND_H
#define KNN_SERVER_UPLOADDATACOMMAND_H

#include "Command.h"

class UploadDataCommand : public Command{
private:
public:
    explicit UploadDataCommand(DefaultIO* defaultIo): Command((string &) "1. upload an unclassified csv data file\n", defaultIo){}
    void execute(Info* info) override;
};


#endif //KNN_SERVER_UPLOADDATACOMMAND_H
