//
// Created by dansa97 on 1/16/23.
//

#include "CLI.h"

/**
 * Constructor of CLI
 * @param dio Io will be used to communicate with client
 */
CLI::CLI(DefaultIO *dio) {
    setDio(dio);
    //creates all commands
    this->commands.push_back(new UploadDataCommand(this->dio));
    this->commands.push_back(new SettingsCommand(this->dio));
    this->commands.push_back(new ClassifyDataCommand(this->dio));
    this->commands.push_back(new DisplayResultsCommand(this->dio));
    this->commands.push_back(new DownloadResultsCommand(this->dio));
    this->commands.push_back(new ExitCommand(this->dio));
    info = new Info();
}

/**
 * Destructor of CLI, deletes all commands
 */
CLI::~CLI() {
    for(auto* command : this->commands){
        delete command;
    }
}

/**
 * getter for the CLI's dio (clientID).
 * @return dio
 * */
DefaultIO *CLI::getDio() const {
    return dio;
}

/**
 * setter for the CLI's dio (clientID).
 * @param dio
 */
void CLI::setDio(DefaultIO *dio) {
    this->dio = dio;
}


/**
 * This function sends the menu to the client.
 */
void CLI::printMenu(){
    this->dio->write("Welcome to the KNN Classifier Server. Please choose an option:\n");
    int size = (int) this->commands.size();

    for (int i=0; i< size; i++) {
        this->dio->write(commands.at(i)->getDescription());
    }
    this->dio->write("$$$");
}

/**
 * This function sends the menu to the client using an auxiliary function, receives an answer and execute the
 * proper command.
 */
void CLI::start() {
    string input;
    int userInput;

    do {
        input = "";
        //sends the menu to the client
        printMenu();

        //get user's choice
        input = this->dio->read();
        //check validation of input
        if(isPositiveInteger(input)){
           userInput = stoi(input);
        }else{
            //go to next iteration and print the menu again
            continue;
        }
        //execute
        if (userInput >= 1 && userInput <= 5) {
            this->commands.at(userInput - 1)->execute(info);
        }

    } while (userInput != 8);
    ///////delete all test and train vectors!!!!
    delete info->database;
    delete info;
}


