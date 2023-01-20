//
// Created by dansa97 on 1/16/23.
//

#include "CLI.h"

//constructor
CLI::CLI(DefaultIO *dio) {
    setDio(dio);
    this->commands.push_back(new UploadDataCommand(this->dio));
    this->commands.push_back(new SettingsCommand(this->dio));
    this->commands.push_back(new ClassifyDataCommand(this->dio));
    this->commands.push_back(new DisplayResultsCommand(this->dio));
    this->commands.push_back(new DownloadResultsCommand(this->dio));
    this->commands.push_back(new ExitCommand(this->dio));
    info = new Info();
}

//destructor
CLI::~CLI() {
    for(auto* command : this->commands){
        delete command;
    }
}

/**
 * getter for the CLI's dio (clientID).
 * @return dio
 * */
DefaultIO *CLI::getDio() const {
    return dio;
}

/**
 * setter for the CLI's dio (clientID).
 * @param dio
 */
void CLI::setDio(DefaultIO *dio) {
    this->dio = dio;
}

//void CLI::TEST(){
//    while (true) {
//        //set a buffer to hold the incoming data
//        char buffer[4096] = {0};
//        string classification;
//        int expected_data_len = sizeof(buffer);
//        long read_bytes = recv(dio->getId(), buffer, expected_data_len, 0);
//        if (read_bytes == 0) {
//            break;
//        } else if (read_bytes < 0) {
//            exit(1);
//        } else {
//            //buffer stores the received data! (vector, distance, k)
//        }
//        // convert buffer into array of 3 strings and send it to getClassification
//        auto *brokeBuffer = new string[3];
//        //check if the client wants to close the connection
//        if(brokeBuffer[0] == "-1" && brokeBuffer->length() == 2){
//            break;
//        }
//        if(breakBuffer(buffer, brokeBuffer)){
//            //getting the classification of the new vector
//            classification = getClassifiction(brokeBuffer);
//        }else{
//            classification = "invalid input";
//        }
//
//        delete[] brokeBuffer;
//        char sendBuffer[4096] = {0};
//        //moving the classification back to buffer for to send it back to the Client
//        for (unsigned int i = 0; i < classification.length(); ++i) {
//            sendBuffer[i] = classification.at(i);
//        }
//        //adding '\0' to the end of the string
//        sendBuffer[classification.length()] = '\0';
//        long send_bytes = send(dio->getId(), sendBuffer, classification.length(), 0);
//        if (send_bytes < 0) {
//            exit(1);
//        }
//    }
//}

/**
 * This function gets the data sent from the client and returns a classification of the new vector
 * brokeBuffer[0] = vector
 * brokeBuffer[1] = distance
 * brokeBuffer[2] = k
 * @param brokeBuffer - an array storing the data received from the client
 * @return a string storing the classification
 */
//string CLI::getClassifiction(string* brokeBuffer) {
    //when the database is created it has a default of k=1
    //this->info->database->setK(stoi(brokeBuffer[2]));

    //choose the distance algorithm
    //char* disAlg = new char[brokeBuffer[1].length() + 1];
    //brokeBuffer[1].copy(disAlg, brokeBuffer[1].length(), 0);
    //disAlg[brokeBuffer[1].length()] = '\0';
    //checking which distance algorithm to use
    //Distance *dis = chooseDis(disAlg);
    //checking the validation of the new distance object
//    if (dis == nullptr){
//        delete[] disAlg;
//        return "invalid input";
//    }
//    delete[] disAlg;

    //return  a new classified vector
//    return newVectorClassification(this->info->database, dis, brokeBuffer[0]);

//}

/**
 * This function divide and extract relevant data from the client message and store it in an array
 * @param brokeBuffer - the array to store the divided data
 * @param buffer - the data
 * @return true if there were no problems with the client message and false otherwise
 */
//bool CLI::breakBuffer(char *buffer, string* brokeBuffer) {
//    string input;
//    int t = 0;
//    while(buffer[t] != '\0'){
//        input += buffer[t];
//        t++;
//    }
//    input += '\0';
//
//    // create first string - vector
//    string vectorString;
//    int i = 0;
//    while ((buffer[i] >= '0' && buffer[i] <= '9') || buffer[i] == ' ' || buffer[i] == '-'
//           || buffer[i] == '.' || buffer[i] == 'E') {
//        vectorString += buffer[i];
//        i++;
//    }
//    //check the validation of the vector
//    if(!checkStr(vectorString)){
//        return false;
//    }
//    brokeBuffer[0] = vectorString;
//
//    //check the validation of the rest of the client data
//    if(input.length() - brokeBuffer[0].length() < 5){
//        return false;
//    }
//
//    // create second string - distance (a 3 letters word)
//    string distanceString;
//    for (int j = 0; j < 3; j++) {
//        distanceString += buffer[i];
//        i++;
//    }
//    brokeBuffer[1] = distanceString;
//    i++;
//
//    // create third string - k (a number)
//    string kString;
//    while (buffer[i] != '\0') {
//        kString += buffer[i];
//        i++;
//    }
//    //check the validation of the k
//    if(!isPositiveInteger(kString)){
//        return false;
//    }
//    brokeBuffer[2] = kString;
//    return true;
//}

/**
 * This function sends the menu to the client.
 */
void CLI::printMenu(){
    this->dio->write("Welcome to the KNN Classifier Server. Please choose an option:\n");
    int size = this->commands.size();

    for (int i=0; i< size; i++) {
        this->dio->write(commands.at(i)->getDescription());
    }
    this->dio->write("$$$");
}

/**
 * This function sends the menu to the client using an auxiliary function, receives an answer and execute the
 * proper command.
 */
void CLI::start() {
    string input;
    int userInput;

    do {
        input = "";
        //sends the menu to the client
        printMenu();

        //get user's choice
        input = this->dio->read();
        //check validation of input
        if(isPositiveInteger(input)){
           userInput = stoi(input);
        }else{
            //go to next iteration and print the menu again
            continue;
        }
        //execute
        if (userInput >= 1 && userInput <= 5) {
            this->commands.at(userInput - 1)->execute(info);
        }

    } while (userInput != 8);
    ///////delete all test and train vectors!!!!
    delete info->database;
    delete info;
}


