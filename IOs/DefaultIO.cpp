//
// Created by dansa97 on 1/11/23.
//

#include "DefaultIO.h"

string DefaultIO::read() {
    return std::string();
}

void DefaultIO::write(string output) {

}

int DefaultIO::getId(){
    return clientId;
}

void DefaultIO::setId(int id) {
    DefaultIO::clientId = id;
}