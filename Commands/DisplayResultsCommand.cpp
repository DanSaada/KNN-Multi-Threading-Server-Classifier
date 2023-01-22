//
// Created by tomer on 1/11/23.
//

#include "DisplayResultsCommand.h"

/**
 * constructor of DisplayResultsCommand
 * @param defaultIo Io used
 */
DisplayResultsCommand::DisplayResultsCommand(DefaultIO* defaultIo): Command(){
    setDescription("4. display results\n");
    setDio(defaultIo);
}

/**
 * This function execute the DisplayResultsCommand command which basically display the new classified vectors.
 * @param info - a struct holding relevant information for the communication between the commands.
 */
void DisplayResultsCommand::execute(Info *info) {
    //check that the user already uploaded the classified files
    if (!info->isUploaded){
        dio->write("please upload data\n$$$");
        this->dio->read();
        return;
//        if(this->dio->read() == "#####"){
//            return;
//        }
    }
    //check that the user already classified the data
    if(!info->isClassified){
        dio->write("please classify the data\n");
        this->dio->write("$$$");
        this->dio->read();
        return;
//        if(this->dio->read() == "#####"){
//            return;
//        }
    }

    //send a numbered list of the vectors classification
    unsigned long testSize = info->database->getMTest()->size();
    string output;
    for (unsigned long i = 0; i < testSize; ++i) {
        output = to_string(i + 1) + "\t" + info->database->getMTest()->at(i).getName() + "\n";
        dio->write(output);
    }
    dio->write("Done.\n$$$");
    this->dio->read();
//    if(this->dio->read() == "#####"){
//        return;
//    }
}
