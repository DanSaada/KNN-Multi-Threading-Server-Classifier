//
// Created by dansa97 on 1/11/23.
//

#include "UploadDataCommand.h"

//constructor
UploadDataCommand::UploadDataCommand(DefaultIO* defaultIo): Command() {
    setDescription("1. upload an unclassified csv data file\n");
    setDio(defaultIo);
}

void UploadDataCommand::CatalogTrainMaker(Info* info, const string& toSplitString){
    string substring;
    char arr[toSplitString.size()];
    toSplitString.copy(arr, toSplitString.length(), 0);
    int sizeOfSplitString = (int) toSplitString.size();
    for (int i = 0; i < sizeOfSplitString; ++i) {
        if(arr[i] != '\n' && arr[i] != '\r'){
            substring += arr[i];
        }else{
            TrainCatalog *newCatalog = info->database->setTrainCatalog(substring);
            if (newCatalog != nullptr) {
                info->database->m_Train.push_back(*newCatalog);
            }
            substring = "";
        }
    }
}


void UploadDataCommand::CatalogTestMaker(Info* info, const string& toSplitString){
    string substring;
    char arr[toSplitString.size()];
    toSplitString.copy(arr, toSplitString.length(), 0);
    int sizeOfSplitString = (int) toSplitString.size();
    for (int i = 0; i < sizeOfSplitString; ++i) {
        if(arr[i] != '\n' && arr[i] != '\r'){
            substring += arr[i];
        }else{
            TestCatalog *newCatalog = info->database->setTestCatalog(substring);
            if (newCatalog != nullptr) {
                info->database->m_Test.push_back(*newCatalog);
            }
            substring = "";
        }
    }
}

/**
 * This function execute the SUploadDataCommand command which basically uploads the classified and the unclassified
 * files.
 * @param info - a struct holding relevant information for the communication between the commands.
 */
void UploadDataCommand::execute(Info *info) {
    //if the user uploads new files then the old database should be deleted
    info->isUploaded = false;
    //delete the old classified vectors file
    if(!info->database->m_Train.empty()){
        for (unsigned long i = info->database->m_Train.size() - 1; i > 0; --i) {
            info->database->m_Train.at(i).getVector().pop_back();
            info->database->m_Train.pop_back();
        }
    }
    //delete the old unclassified vectors file
    if(!info->database->m_Test.empty()){
        for (unsigned long i = info->database->m_Test.size() - 1; i > 0; --i) {
            info->database->m_Test.at(i).getVector().pop_back();
            info->database->m_Test.pop_back();
        }
    }
    this->dio->write("Please upload your local train CSV file.\n");
    this->dio->write("$$$");

    string csvTrainData;
    // "$$$" is a sign from the client that means end of file.
   // while (csvTrainData != "$$$") {
        //read CSV train data from the client
        // !!!!!! change according to edge cases of checking validation by implementing a function inside defaultIO
        csvTrainData = this->dio->read();
        csvTrainData += '\n';
        CatalogTrainMaker(info, csvTrainData);
        //check validation of the input and create a new TrainCatalog based on the information passed

//        TrainCatalog *newCatalog = info->database->setTrainCatalog(csvTrainData);
//        //insert the new TrainCatalog inside the database
//        if (newCatalog != nullptr) {
//            info->database->m_Train.push_back(*newCatalog);
//        }
    //}
    this->dio->write("Upload complete.\n");

    //read CSV test data from the client
    string csvTestData;

    this->dio->write("Please upload your local test CSV file.\n");
    this->dio->write("$$$");
//    while(csvTestData != "$$$"){
    csvTestData = this->dio->read();
    csvTestData += '\n';
    CatalogTestMaker(info, csvTestData);
       // TestCatalog *newCatalog = info->database->setTestCatalog(csvTestData);
//        if(newCatalog != nullptr){
//            info->database->m_Test.push_back(*newCatalog);
//        }
    //}

    this->dio->write("Upload complete.\n");
    this->dio->write("$$$");
    info->isUploaded = true;
    info->isClassified = false;
}


