//
// Created by tomer on 1/11/23.
//

#include "DownloadResultsCommand.h"

//constructor
DownloadResultsCommand::DownloadResultsCommand(DefaultIO* defaultIo): Command(){
    setDescription("5. download results\n");
    setDio(defaultIo);
}

/**
 * This function execute the DownloadResultsCommand command which basically downloads the results of the new classified
 * vectors into a file.
 * @param info - a struct holding relevant information for the communication between the commands.
 */
void DownloadResultsCommand::execute(Info *info) {
    //check that the user already uploaded the classified files
    if (!info->isUploaded){
        dio->write("please upload data\n");
        return;
    }
    //check that the user already classified the data
    if(!info->isClassified){
        dio->write("please classify the data\n");
        return;
    }

    //send a numbered list of the vectors classification
    unsigned long testSize = info->database->getMTest()->size();
    string output;
    for (unsigned long i = 0; i < testSize; ++i) {
        output = to_string(i) + "\t" + info->database->getMTest()->at(i).getName() + "\n";
        dio->write(output);
    }
}
