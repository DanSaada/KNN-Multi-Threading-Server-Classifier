//
// Created by dansa97 on 1/11/23.
//

#ifndef KNN_SERVER_CLASSIFYDATACOMMAND_H
#define KNN_SERVER_CLASSIFYDATACOMMAND_H

#include "Command.h"

class ClassifyDataCommand : public Command{
private:
public:
    explicit ClassifyDataCommand(DefaultIO* defaultIo);

    void execute(Info* info) override;
};


#endif //KNN_SERVER_CLASSIFYDATACOMMAND_H
