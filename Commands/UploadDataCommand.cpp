//
// Created by dansa97 on 1/11/23.
//

#include "UploadDataCommand.h"

void UploadDataCommand::execute(Info *info) {
    this->dio->write("Please upload your local train CSV file.\n");

    //read CSV train data from the client
    //!!!!!! change according to edge cases of checking validation by implementing a function inside defaultIO
    string csvTrainData = this->dio->read();

    // "$$$" is a sign from the client that means end of file.
    while (csvTrainData != "$$$") {
        //check validation of the input and create a new Catalog based on the information passed
        Catalog *newCatalog = info->database->setCatalog(csvTrainData);
        //insert the new Catalog inside the database
        if (newCatalog != nullptr) {
            info->database->m_data.push_back(*newCatalog);
        }
    }
    this->dio->write("Upload complete.\n");

    //read CSV test data from the client
    string csvTestData = this->dio->read();



}
