//
// Created by dansa97 on 1/11/23.
//

#include "ClassifyDataCommand.h"

void ClassifyDataCommand::execute(Info *info) {
    if (!info->isUploaded){
        dio->write("please upload data\n");
        dio->write("$$$");
        if(this->dio->read() == "#####"){
            return;
        }
    }
    unsigned long testSize = info->database->getMTest()->size();
    auto *testVectors = info->database->getMTest();
    for (unsigned long i = 0; i < testSize; ++i) {
        testVectors->at(i).setName(info->database->findKNN(testVectors->at(i).getVector()));
    }
    this->dio->write("classifying data complete\n");
    this->dio->write("$$$");
    if(this->dio->read() == "#####"){
        info->isClassified = true;
        return;
    }
}
