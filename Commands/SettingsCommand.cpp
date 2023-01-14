//
// Created by dansa97 on 1/11/23.
//

#include "SettingsCommand.h"

void SettingsCommand::execute(Info *info) {
    string str;
    string newK;
    int i = 0;
    str = this->dio->read();
    if(str.length() == 0){
        str = "The current KNN parameters are: K = " + to_string(info->database->getK())
                + ", distance metric = " + info->database->getMDistanceString() + "\n";
    } else{
        while(str[i]!=' ' && str[i]!='\0'){
            newK += str[i];
            ++i;
        }
        if()
    }
    this->dio->write(str);
}
