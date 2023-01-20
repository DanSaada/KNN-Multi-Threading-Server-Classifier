//
// Created by dansa97 on 1/11/23.
//

#ifndef KNN_SERVER_SETTINGSCOMMAND_H
#define KNN_SERVER_SETTINGSCOMMAND_H

#include "Command.h"
#include "../Classify/ClassificationLogic.h"

class SettingsCommand : public Command{
private:
public:
    explicit SettingsCommand(DefaultIO* defaultIo);

    void execute(Info* info) override;
};


#endif //KNN_SERVER_SETTINGSCOMMAND_H