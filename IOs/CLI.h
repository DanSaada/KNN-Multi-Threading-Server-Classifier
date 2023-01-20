//
// Created by dansa97 on 1/16/23.
//

#ifndef KNN_SERVER_CLI_H
#define KNN_SERVER_CLI_H

#include "../Commands/Command.h"
#include "../Commands/UploadDataCommand.h"
#include "../Commands/SettingsCommand.h"
#include "../Commands/ClassifyDataCommand.h"
#include "../Commands/DisplayResultsCommand.h"
#include "../Commands/DownloadResultsCommand.h"
#include "../Commands/ExitCommand.h"
#include "../Classify/ClassificationLogic.h"
#include "SocketIO.h"

using namespace std;

class CLI {
private:
    DefaultIO* dio;
    vector<Command*> commands;
    Info* info;
public:
    //constructor
    CLI(DefaultIO* dio);

    //starts the interaction with the client
    void start();

    //destructor
    virtual ~CLI();

    DefaultIO *getDio() const;

    void setDio(DefaultIO *dio);

    void printMenu();

    void TEST();

    bool breakBuffer(char *buffer, string* brokeBuffer);

    string getClassifiction(string* brokeBuffer);
};


#endif //KNN_SERVER_CLI_H
