//
// Created by tomer on 1/11/23.
//

#include "Command.h"

/**
 * getter for the command's description.
 * @return description
 * */
const string &Command::getDescription() const {
    return description;
}

void Command::setDescription(const string &description) {
    Command::description = description;
}

void Command::setDio(DefaultIO *dio) {
    Command::dio = dio;
}

