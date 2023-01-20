//
// Created by tomer on 1/11/23.
//

#include "DisplayResultsCommand.h"

void DisplayResultsCommand::execute(Info *info) {
    if (!info->isUploaded){
        dio->write("please upload data");
        this->dio->write("$$$");
        return;
    }
    if(!info->isClassified){
        dio->write("please classify the data");
        this->dio->write("$$$");
        return;
    }

    unsigned long testSize = info->database->getMTest()->size();
    string output;
    for (unsigned long i = 0; i < testSize; ++i) {
        output = to_string(i + 1) + "\t" + info->database->getMTest()->at(i).getName();
        dio->write(output);
    }
    dio->write("Done.");
    this->dio->write("$$$");
}
