//
// Created by tomer on 1/18/23.
//

#include "Client.h"

/**
 * If the string is empty or the first character is not a digit, then it's not a positive integer. Otherwise, it's a
 * positive integer if the string is equal to the number converted to a string
 *
 * @param s The string to be checked
 *
 * @return A boolean value.
 */
bool isPositiveInteger(const string &s) {
    if (s.empty() || ((!isdigit(s[0])))) return false;

    char *p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);
}

/**
 * This function takes in a port number and an IP address and sets the serverPort and serverIpAddr variables to the values
 * passed in
 *
 * @param port The port number of the server.
 * @param ipAddr The IP address of the server.
 */
Client::Client(const string& port, const char* ipAddr) {
    this->standardIo = new StandardIO();
    if(!isPositiveInteger(port) || stoi(port) <= 0 || stoi(port) > 65535 ){
        exit(1);
    }
    this->serverPort = stoi(port);
    this->serverIpAddr = ipAddr;
    //default socket
    this->clientSocket = -1;
}

/**
 * It returns the socket of the client.
 *
 * @return The client socket.
 */
int Client::getSocket() const {
    return clientSocket;
}

/**
 * This function sets the clientSocket variable to the socket passed in as a parameter.
 *
 * @param socket The socket that the client is connected to.
 */
void Client::setSocket(int socket) {
    this->clientSocket = socket;
}

/**
 * This function creates a socket and connects it to the server
 */
void Client::initializeSocket() {
    setSocket((int)socket(AF_INET, SOCK_STREAM, 0));

    //checking creation succeed
    if (getSocket() < 0){
        this->standardIo->write("error creating sock\n");
        exit(1);
    }

    //for sending a group of parameters and get them back we create a struct
    struct sockaddr_in sin;
    //nullify the struct
    memset(&sin, 0, sizeof (sin));
    //initialize the struct fields
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(serverIpAddr);
    sin.sin_port = htons(serverPort);
    if(connect(getSocket(), (struct sockaddr *) &sin, sizeof(sin)) < 0){
        this->standardIo->write("error connecting to server\n");
        exit(1);
    }
    this->socketIo = new SocketIO(getSocket());

}

/**
 * This function handles with the client's side of the related UploadDataCommand.
 * basically monitor and sends the classified and the un classified vectors to the server
 */
void Client::uploadDataCommandClientSide(){
    string str;
    //print "please upload train massage"
    this->standardIo->write(this->socketIo->read());
    //get the path from the user
    getline(cin, str);
    //check that the train file open properly
    if(!uploadData(str)){
        this->socketIo->write("#$$$");
        return;
    }
    //print "upload complete + please upload test" massages
    string check = this->socketIo->read();
    this->standardIo->write(check);
    if(check == "invalid input\n"){
        return;
    }
    //get the path from the user
    getline(cin, str);
    //check that the test file open properly
    if(!uploadData(str)){
        this->socketIo->write("#$$$");
        return;
    }
    //upload complete
    this->standardIo->write(this->socketIo->read());
    this->socketIo->write("$$$");
}

/**
* This function handles with the client's side of the related SettingCommand.
* basically monitor and sends the classified and the un classified vectors to the server
*/
void Client::settingCommandClientSide() {
    string str, invalidOption;
    //current k and distance metric
    this->standardIo->write(this->socketIo->read());
    //press enter or enter new k and distance metric
    getline(cin, str);
    this->socketIo->write(str + "$$$");
    //checks that the data entered a proper way
    invalidOption = this->socketIo->read();
    this->socketIo->write("$$$");
    if(!invalidOption.empty()) {
        this->standardIo->write(invalidOption);
    }
}

/**
* This function handles with the client's side of the related ClassifyDataCommand and the DisplayResultsCommand.
* Because both has the same logic, if an error occurs in those commands the "read" will catch it, and otherwise if
 * they manage to finish successfully the task then the "read" will catch message saying they did so.
*/
void Client::classifyAndDisplayCommandsClientSide() {
    this->standardIo->write(this->socketIo->read());
    //creating an explicit delay
    this->socketIo->write("#####$$$");
}

/**
* This function handles with the client's side of the related DownloadResultsCommand.
 * The function first checks that all actions that needs to be done before were made, and then call an auxiliary
 * function called "downloadData" which is running on a different thread, what allows the user to continue with other
 * requests while the classified data is being downloaded into a local file to his choice on his computer.
*/
void Client::downloadResultsCommandClientSide() {
    string path;
    string data = this->socketIo->read();
    if(data == "please upload data\n" || data == "please classify the data\n") {
        this->standardIo->write(data);
        this->socketIo->write("#####$$$");
        return;
    }
    this->socketIo->write("#####$$$");
    getline(cin, path);
    thread t(&downloadData, path, data);
    t.detach();
}

/**
 * This function receives a choice from the user, sends it to the server, and then starts a "ping-pong"
 * communication between them based on the requested task.
 */
void Client::communicate() {

    while (true) {
        //print the menu
        this->standardIo->write(this->socketIo->read());

        //get the user's choice
        string str;
        getline(cin, str);

        //check that the user entered a number
        if(isPositiveInteger(str)){
            //send the server the user's choice, so it could invoke and execute the right command
            this->socketIo->write(str + "$$$");
            int userChoice = stoi(str);

            //handle the client side of the communication based on the user's task choice
            switch (userChoice) {
                case 1:
                    uploadDataCommandClientSide();
                    break;

                case 2:
                    settingCommandClientSide();
                    break;

                case 3:
                    classifyAndDisplayCommandsClientSide();
                    break;

                case 4:
                    classifyAndDisplayCommandsClientSide();
                    break;

                case 5:
                    downloadResultsCommandClientSide();
                    break;

                case 8:
                    close(getSocket());
                    return;

                default:
                    //in case the user choose a number that doesn't appear in the menu
                    this->standardIo->write("invalid input\n");
                    this->socketIo->write("#$$$");
            }
        }else{
            //in case the user choose a character that isn't a number end the current loop and reprint the menu
            this->standardIo->write("invalid input\n");
            this->socketIo->write("#$$$");
        }
    }
}

/**
 * This function opens a local file in the users computer, and write to the file line by line the result
 * classification vectors.
 * @param route
 */
void Client::downloadData(string route, string data) {
    ofstream outFile;
    outFile.open(route);
    if (!outFile) {
        cout << "invalid input\n";
        return;
    }
    outFile << data;
    outFile.close();
}

/**
 * This function opens the file, reads the file line by line, and then calls the
 * setTrainCatalog function to create a new TrainCatalog object.
 */
bool Client::uploadData(string route) {
    ifstream file;
    file.open(route, ios::in);
    if (!file) {
        this->standardIo->write("invalid input\n");
        return false;
    }
    string line;
    while (getline(file, line)) {
        if(line.at(line.size() - 1) != '\r'){
            line+='\r';
        }
        this->socketIo->write(line);
    }
    file.close();
    //end current massages
    this->socketIo->write("$$$");
    return true;
}

/**
 * It creates a new client object, initializes the socket, and then communicates with the server
 *
 * @param argc the number of arguments passed to the program
 * @param argv
 *
 * @return The return value of the function.
 */
int main(int argc, char const *argv[]) {
    //checks if there are 2 argument put.
    if (argc != 3) {
        cout << "Invalid input!" << endl;
        exit(1);
    }
    auto* client = new Client(argv[2], argv[1]);
    //initialize connection to server
    client->initializeSocket();
    client->communicate();
    return 0;
}
