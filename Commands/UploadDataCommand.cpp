//
// Created by dansa97 on 1/11/23.
//

#include "UploadDataCommand.h"

/**
 * Constructor of UploadDataCommand
 * @param defaultIo Io used
 */
UploadDataCommand::UploadDataCommand(DefaultIO *defaultIo) : Command() {
    setDescription("1. upload an unclassified csv data file\n");
    setDio(defaultIo);
}

/**
 * It takes a string, splits it into substrings, and then adds each substring to a vector
 *
 * @param info a pointer to the Info class, which contains the database and the socket.
 * @param toSplitString The string to be split.
 */
void UploadDataCommand::CatalogTrainMaker(Info *info, const string &toSplitString) {
    string substring;
    char arr[toSplitString.size()];
    toSplitString.copy(arr, toSplitString.length(), 0);
    int sizeOfSplitString = (int) toSplitString.size();
    for (int i = 0; i < sizeOfSplitString; ++i) {
        if (arr[i] != '\n' && arr[i] != '\r') {
            substring += arr[i];
        } else {
            TrainCatalog *newCatalog = info->database->setTrainCatalog(substring);
            if (newCatalog != nullptr) {
                info->database->getMTrain()->push_back(*newCatalog);
            }
            substring = "";
        }
    }
}


/**
 * This function takes a string and splits it into substrings based on the newline character
 *
 * @param info a pointer to the Info class, which contains all the information about the server.
 * @param toSplitString The string to split.
 */
void UploadDataCommand::CatalogTestMaker(Info *info, const string &toSplitString) {
    string substring;
    char arr[toSplitString.size()];
    toSplitString.copy(arr, toSplitString.length(), 0);
    int sizeOfSplitString = (int) toSplitString.size();
    for (int i = 0; i < sizeOfSplitString; ++i) {
        if (arr[i] != '\n' && arr[i] != '\r') {
            substring += arr[i];
        } else {
            //EOF
            if(substring.empty()){
                break;
            }
            //adds ',' to last number
            substring += ',';
            TestCatalog *newCatalog = info->database->setTestCatalog(substring);
            if (newCatalog != nullptr) {
                info->database->getMTest()->push_back(*newCatalog);
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
    if (!info->database->getMTrain()->empty()) {
        for (long i = (long) info->database->getMTrain()->size() - 1; i >= 0; --i) {
            info->database->getMTrain()->at(i).getVector().pop_back();
            info->database->getMTrain()->pop_back();
        }
    }
    //delete the old unclassified vectors file
    if (!info->database->getMTest()->empty()) {
        for (long i = (long) info->database->getMTest()->size() - 1; i >= 0; --i) {
            info->database->getMTest()->at(i).getVector().pop_back();
            info->database->getMTest()->pop_back();
        }
    }
    this->dio->write("Please upload your local train CSV file.\n$$$");

    string csvTrainData;
    // "$$$" is a sign from the client that means end of file.

    //read CSV train data from the client
    // !!!!!! change according to edge cases of checking validation by implementing a function inside defaultIO
    csvTrainData = this->dio->read();
    //the train file didn't open properly in the client
    if(csvTrainData == "#"){
        return;
    }
    csvTrainData += '\n';
    CatalogTrainMaker(info, csvTrainData);

    //check that the train data isn't empty
    if(info->database->getMTrain()->empty()){
        this->dio->write("invalid input\n$$$");
        return;
    }
    //check validation of the input and create a new TrainCatalog based on the information passed

    this->dio->write("Upload complete.\n");

    //read CSV test data from the client
    string csvTestData;

    this->dio->write("Please upload your local test CSV file.\n$$$");

    csvTestData = this->dio->read();
    //the test file didn't open properly in the client
    if(csvTestData == "#"){
        if (!info->database->getMTrain()->empty()) {
            for (long i = (long) info->database->getMTrain()->size() - 1; i >= 0; --i) {
                info->database->getMTrain()->at(i).getVector().pop_back();
                info->database->getMTrain()->pop_back();
            }
        }
        return;
    }
    csvTestData += '\n';
    CatalogTestMaker(info, csvTestData);


    this->dio->write("Upload complete.\n$$$");
    info->isUploaded = true;
    info->isClassified = false;
    this->dio->read();
}


