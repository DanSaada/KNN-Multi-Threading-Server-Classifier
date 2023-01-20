//
// Created by tomer on 1/11/23.
//

#include "DownloadResultsCommand.h"

void DownloadResultsCommand::execute(Info *info) {
    if (!info->isUploaded){
        dio->write("please upload data");
        return;
    }
    if(!info->isClassified){
        dio->write("please classify the data");
        return;
    }
    unsigned long testSize = info->database->getMTest()->size();
    string output;
    for (unsigned long i = 0; i < testSize; ++i) {
        output = to_string(i) + "\t" + info->database->getMTest()->at(i).getName();
        dio->write(output);
    }
}
