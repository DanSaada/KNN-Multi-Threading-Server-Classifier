//
// Created by tomer on 1/11/23.
//

#include "DisplayResultsCommand.h"

void DisplayResultsCommand::execute(Info *info) {
    if (!info->isUploaded){
        dio->write("please upload data\n");
        this->dio->write("$$$");
        if(this->dio->read() == "#####"){
            return;
        }
    }
    if(!info->isClassified){
        dio->write("please classify the data\n");
        this->dio->write("$$$");
        if(this->dio->read() == "#####"){
            return;
        }
    }

    unsigned long testSize = info->database->getMTest()->size();
    string output;
    for (unsigned long i = 0; i < testSize; ++i) {
        output = to_string(i + 1) + "\t" + info->database->getMTest()->at(i).getName() + "\n";
        dio->write(output);
    }
    dio->write("Done.\n");
    this->dio->write("$$$");
    if(this->dio->read() == "#####"){
        return;
    }
}
