//
// Created by dansa97 on 1/11/23.
//

#include "ClassifyDataCommand.h"

//constructor
 ClassifyDataCommand::ClassifyDataCommand(DefaultIO* defaultIo): Command(){
    setDescription("3. classify data\n");
    setDio(defaultIo);
}

/**
 * This function execute the ClassifyDataCommand command which basically classify al the unclassified vectors.
 * @param info - a struct holding relevant information for the communication between the commands.
 */
void ClassifyDataCommand::execute(Info *info) {
    //check that the user already uploaded the classified files
    if (!info->isUploaded){
        dio->write("please upload data\n");
        dio->write("$$$");
        if(this->dio->read() == "#####"){
            return;
        }
    }

    //classify each one of the unclassified vectors that the user sent.
    unsigned long testSize = info->database->getMTest()->size();
    auto *testVectors = info->database->getMTest();
    for (unsigned long i = 0; i < testSize; ++i) {
        testVectors->at(i).setName(info->database->findKNN(testVectors->at(i).getVector()));
    }
    //send a message that the classification is complete
    this->dio->write("classifying data complete\n");
    this->dio->write("$$$");
    if(this->dio->read() == "#####"){
        info->isClassified = true;
        return;
    }
}
