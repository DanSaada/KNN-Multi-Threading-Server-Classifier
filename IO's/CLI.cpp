//
// Created by dansa97 on 1/16/23.
//

#include "CLI.h"

//constructor
CLI::CLI(DefaultIO *dio) {
    setDio(dio);
    this->commands.push_back(new UploadDataCommand(this->dio));
    this->commands.push_back(new SettingsCommand(this->dio));
    this->commands.push_back(new ClassifyDataCommand(this->dio));
    this->commands.push_back(new DisplayResultsCommand(this->dio));
    this->commands.push_back(new DownloadResultsCommand(this->dio));
    this->commands.push_back(new ExitCommand(this->dio));

}

CLI::~CLI() {
    for(auto* command : this->commands){
        delete command;
    }
}

DefaultIO *CLI::getDio() const {
    return dio;
}

void CLI::setDio(DefaultIO *dio) {
    CLI::dio = dio;
}

void CLI::start() {
    Info* info = new Info();
    string input;
    int userInput;

    do {
        this->dio->write("Welcome to the KNN Classifier Server. Please choose an option:\n");
        int size = this->commands.size();

        //print the menu
        for (int i=0; i< size; i++) {
            this->dio->write(commands.at(i)->getDescription());
        }

        //get user's choice
        input = this->dio->read();
        //check validation of input
        if(isPositiveInteger(input)){
           userInput = stoi(input);
        }else{
            break;
        }
        //execute
        if (userInput >= 1 && userInput <= 5) {
            this->commands.at(userInput - 1)->execute(info);
        }

    } while (userInput != 8);
    delete info;
}


