//
// Created by dansa97 on 1/11/23.
//

#include "ClassifyDataCommand.h"

void ClassifyDataCommand::execute(Info *info) {
    if (!info->isUploaded){
        dio->write("please upload data\n");
        return;
    }
    ///////// testSize of test!!!!! need to change!!!
    unsigned long testSize = info->database->getMTrain()->size();
    auto *vec = info->database->getMTrain();
    for (unsigned long i = 0; i < testSize; ++i) {
        info->database->setTrainCatalog(info->database->findKNN(vec->at(i).getVector()));
    }
    dio->write("classifying data complete\n");
    info->isClassified = true;
}
