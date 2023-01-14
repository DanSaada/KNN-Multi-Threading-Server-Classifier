//
// Created by dansa97 on 1/11/23.
//

#include "SettingsCommand.h"

void SettingsCommand::execute(Info *info) {
    this->dio->write("The current KNN parameters are: K = " + to_string(info->database->getK())
                           + ", distance metric = " + info->database->getMDistanceString() + "\n");
    string str;
    string newK;
    string newDis;
    int i = 0;
    str = this->dio->read();
    if(str.length() == 0){
        return;
    } else{
        while(str[i]!=' ' && str[i]!='\0'){
            newK += str[i];
            ++i;
        }
        if(isPositiveInteger(newK)){
            info->database->setK(stoi(newK));
        }else{
            this->dio->write("invalid value for K\n");
        }
        ++i;
        if(str.length() > i){
            while(str[i]!='\0'){
                newDis += str[i];
            }
        }
        if(newDis != "AUC" || newDis != "CHB" || newDis != "MAN" || newDis != "MIN" || newDis != "CAN"){
            this->dio->write("invalid value for metric\n");
        }else{
            info->database->setMDistanceString(newDis);
            info->database->setMDistance(newDis);
        }

    }
}
