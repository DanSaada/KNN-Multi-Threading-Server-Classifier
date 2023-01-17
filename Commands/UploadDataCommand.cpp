//
// Created by dansa97 on 1/11/23.
//

#include "UploadDataCommand.h"

void UploadDataCommand::execute(Info *info) {
    this->dio->write("Please upload your local train CSV file.\n");


    string csvTrainData;
    // "$$$" is a sign from the client that means end of file.
    while (csvTrainData != "$$$") {
        //read CSV train data from the client
        //!!!!!! change according to edge cases of checking validation by implementing a function inside defaultIO
        csvTrainData = this->dio->read();
        //check validation of the input and create a new TrainCatalog based on the information passed
        TrainCatalog *newCatalog = info->database->setTrainCatalog(csvTrainData);
        //insert the new TrainCatalog inside the database
        if (newCatalog != nullptr) {
            info->database->m_Train.push_back(*newCatalog);
        }
    }
    this->dio->write("Upload complete.\n");

    //read CSV test data from the client
    string csvTestData;

    this->dio->write("Please upload your local test CSV file.\n");
    while(csvTestData != "$$$"){
        csvTestData = this->dio->read();
        TestCatalog *newCatalog = info->database->setTestCatalog(csvTestData);
        if(newCatalog != nullptr){
            info->database->m_Test.push_back(*newCatalog);
        }
    }

    this->dio->write("Upload complete.\n");
    info->isUploaded = true;
}
