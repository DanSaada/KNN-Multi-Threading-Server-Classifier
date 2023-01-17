//
// Created by tomer on 1/11/23.
//

#include "DisplayResultsCommand.h"

void DisplayResultsCommand::execute(Info *info) {
    if (!info->isUploaded){
        dio->write("please upload data\n");
        return;
    }
    if(!info->isClassified){
        dio->write("please classify the data\n");
        return;
    }
    ///////size of test file!!!!!
    unsigned long testSize = info->database->getMTrain()->size();
    string output;
    for (unsigned long i = 0; i < testSize; ++i) {
        output = to_string(i) + "\t" + info->database->getMTrain()->at(i).getName() + "\n";
        dio->write(output);
    }
    dio->write("DONE.\n");
}
