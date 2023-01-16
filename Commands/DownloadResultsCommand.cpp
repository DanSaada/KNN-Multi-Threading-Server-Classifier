//
// Created by tomer on 1/11/23.
//

#include "DownloadResultsCommand.h"

void DownloadResultsCommand::execute(Info *info) {
    if (!info->isUploaded){
        dio->write("please upload data\n");
        return;
    }
    if(!info->isClassified){
        dio->write("please classify the data\n");
        return;
    }
    ///////size of test file!!!!!
    unsigned long testSize = info->database->getMData()->size();
    string output;
    for (unsigned long i = 0; i < testSize; ++i) {
        output = to_string(i) + "\t" + info->database->getMData()->at(i).getName() + "\n";
        dio->write(output);
    }
}
