//
// Created by dansa97 on 1/11/23.
//

#include "DefaultIO.h"

/**
 * This function reads a string.
 * @return string
 * */
string DefaultIO::read() {
    return std::string();
}

/**
 * This function writes a string.
 * @return string
 * */
void DefaultIO::write(string output) {

}

/**
 * getter for the clientId/
 * @return clientId
 * */
int DefaultIO::getId(){
    return clientId;
}

/**
 * setter for the clientId.
 * @param id
 */
void DefaultIO::setId(int id) {
    DefaultIO::clientId = id;
}
