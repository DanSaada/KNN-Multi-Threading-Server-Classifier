//
// Created by dansa97 on 1/11/23.
//

#include "SettingsCommand.h"

/**
 * Constructor of SettingsCommand
 * @param defaultIo Io used
 */
SettingsCommand::SettingsCommand(DefaultIO* defaultIo): Command(){
    setDescription("2. algorithm settings\n");
    setDio(defaultIo);
}

/**
 * This function execute the SettingsCommand command which basically set a K and a distance metric.
 * @param info - a struct holding relevant information for the communication between the commands.
 */
void SettingsCommand::execute(Info *info) {
    this->dio->write("The current KNN parameters are: K = " + to_string(info->database->getK())
                           + ", distance metric = " + info->database->getMDistanceString() + "\n");
    this->dio->write("$$$");

    int i = 0;
    string str, newK, newDis;
    bool correctDis = true, correctK = true;

    str = this->dio->read();
    //if the user didn't enter new K and distance metric than live it as is
    if(str.length() == 0){
        this->dio->write("$$$");
        this->dio->read();
        return;
    } else{
        //extract K
        while(str[i]!=' ' && str[i]!='\0'){
            newK += str[i];
            ++i;
        }
        ++i;
        //check that there is also a distance metric besides the K
        if((int) str.length() > i){
            //extract the metric distance
            while(str[i]!='\0'){
                newDis += str[i];
                i++;
            }
        }

        //check validation of K
        if(!isPositiveInteger(newK)){
            this->dio->write("invalid value for K\n");
            correctK = false;
        }

        //check validation of the metric distance
        if(newDis != "AUC" && newDis != "CHB" && newDis != "MAN" && newDis != "MIN" && newDis != "CAN"){
            this->dio->write("invalid value for metric\n");
            correctDis = false;
        }

        this->dio->write("$$$");
        if(correctK && correctDis){
            //changing the distance and k
            info->database->setK(stoi(newK));
            info->database->setMDistanceString(newDis);
            info->database->setMDistance(newDis);
        }
        this->dio->read();
    }
}
