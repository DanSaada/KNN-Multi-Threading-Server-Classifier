//
// Created by dansa97 on 1/11/23.
//

#include "ClassifyDataCommand.h"

void ClassifyDataCommand::execute(Info *info) {
    if (!info->isUploaded){
        dio->write("please upload data");
        dio->write("$$$");
        return;
    }
    unsigned long testSize = info->database->getMTest()->size();
    auto *testVectors = info->database->getMTest();
    for (unsigned long i = 0; i < testSize; ++i) {
        testVectors->at(i).setName(info->database->findKNN(testVectors->at(i).getVector()));
    }
    dio->write("classifying data complete");
    this->dio->write("$$$");
    info->isClassified = true;
}
