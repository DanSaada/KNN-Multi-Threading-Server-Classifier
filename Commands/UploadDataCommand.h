//
// Created by dansa97 on 1/11/23.
//

#ifndef KNN_SERVER_UPLOADDATACOMMAND_H
#define KNN_SERVER_UPLOADDATACOMMAND_H

#include "Command.h"

class UploadDataCommand : public Command{
private:
public:
    void execute() override;
};


#endif //KNN_SERVER_UPLOADDATACOMMAND_H
