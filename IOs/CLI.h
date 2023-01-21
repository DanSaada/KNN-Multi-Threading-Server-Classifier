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
#include "../Classify/Database.h"
#include "../Distances/Distance.h"
#include "../Distances/Euclidean.h"
#include "../Distances/Manhattan.h"
#include "../Distances/Chebyshev.h"
#include "../Distances/Canberra.h"
#include "../Distances/Minkowski.h"
#include "cstring"
#include "SocketIO.h"
#include "../Server/Server.h"

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

};


#endif //KNN_SERVER_CLI_H
