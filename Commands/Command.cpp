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

/**
 * setter for the command's description.
 * @param description
 */
void Command::setDescription(const string &description) {
    Command::description = description;
}

/**
 * setter for the command's IO.
 * @param description
 */
void Command::setDio(DefaultIO *dio) {
    Command::dio = dio;
}

