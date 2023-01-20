//
// Created by tomer on 1/11/23.
//

#ifndef KNN_SERVER_EXITCOMMAND_H
#define KNN_SERVER_EXITCOMMAND_H

#include "Command.h"
class ExitCommand : public Command{
private:
public:
    explicit ExitCommand(DefaultIO* defaultIo);

    void execute(Info* info) override;
};


#endif //KNN_SERVER_EXITCOMMAND_H
