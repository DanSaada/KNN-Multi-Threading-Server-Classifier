//
// Created by dansa97 on 1/11/23.
//

#ifndef KNN_SERVER_SETTINGSCOMMAND_H
#define KNN_SERVER_SETTINGSCOMMAND_H

#include "Command.h"
#include "../Classify/Database.h"
#include "../Distances/Distance.h"
#include "../Distances/Euclidean.h"
#include "../Distances/Manhattan.h"
#include "../Distances/Chebyshev.h"
#include "../Distances/Canberra.h"
#include "../Distances/Minkowski.h"
#include "cstring"
#include "../Server/Server.h"

class SettingsCommand : public Command{
private:
public:
    explicit SettingsCommand(DefaultIO* defaultIo);

    void execute(Info* info) override;
};


#endif //KNN_SERVER_SETTINGSCOMMAND_H