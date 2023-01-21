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
    if(!isPositiveInteger(port) || stoi(port) <= 0 || stoi(port) > 65535 ){
        exit(1);
    }
    this->serverPort = stoi(port);
    this->serverIpAddr = ipAddr;
    //default socket
    this->clientSocket = -1;
    this->printer = new StandardIO();
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
        cout << "error creating sock" << endl;
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
        cout << "error connecting to server" << endl;
        exit(1);
    }
    this->dio = new SocketIO(getSocket());

}

/**
 * It takes in a string from the user, sends it to the server, and then prints out the response from the server
 */
void Client::communicate() {
    string invalidOption;
    while (true) {
        //print the menu
        cout << this->dio->read();
        string str;
        getline(cin, str);
        if(isPositiveInteger(str)){
            this->dio->write(str + "$$$");
            if(stoi(str) == 1){
                //print "please upload train massage"
                cout << this->dio->read();
                //get the path from the user
                getline(cin, str);
                //check that the train file open properly
                if(!uploadData(str)){
                    this->dio->write("#$$$");
                    continue;
                }
                //print "upload complete + please upload test" massages
                string check = this->dio->read();
                cout << check;
                if(check == "invalid input\n"){
                    continue;
                }
                //get the path from the user
                getline(cin, str);
                //check that the test file open properly
                if(!uploadData(str)){
                    this->dio->write("#$$$");
                    continue;
                }
                //upload complete
                cout << this->dio->read();
                this->dio->write("$$$");
            }
            else if(stoi(str) == 2){
                //current k and distance metric
                cout << this->dio->read();
                //press enter or new k and distance metric
                getline(cin, str);
                this->dio->write(str + "$$$");
                invalidOption = this->dio->read();
                this->dio->write("$$$");
                if(!invalidOption.empty()) {
                    cout << invalidOption;
                }
            }
            else if(stoi(str) == 3){
                cout << this->dio->read();
                //creating an explicit delay
                this->dio->write("#####$$$");
            }
            else if(stoi(str) == 4){
                cout << this->dio->read();
                this->dio->write("#####$$$");
            }
            else if(stoi(str) == 5) {
                string path;
                string data = this->dio->read();
                if(data == "please upload data\n" || data == "please classify the data\n") {
                    cout << data;
                    this->dio->write("#####$$$");
                    continue;
                }
                this->dio->write("#####$$$");
                getline(cin, path);
                thread t(&downloadData, path, data);
                t.detach();
            }else if(stoi(str) == 8){
               close(getSocket());
               break;
            }else{
                cout << "invalid input\n";
                //in case the user choose a number that doesn't appear in the menu
                this->dio->write("#$$$");
            }
        }else{
            cout << "invalid input\n";
            //in case the user choose a character that isn't a number
            this->dio->write("#$$$");
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
        cout << "invalid input\n";
        return false;
    }
    string line;
    while (getline(file, line)) {
        if(line.at(line.size() - 1) != '\r'){
            line+='\r';
        }
        this->dio->write(line);
    }
    file.close();
    //end current massages
    this->dio->write("$$$");
    return true;
}

void Client::Send(string toSend){
    char data_addr[4096] = {0};
    toSend.copy(data_addr, toSend.length(), 0);
    int data_len = (int) strlen(data_addr);
    long sent_bytes = send(getSocket(), data_addr, data_len, 0);
    if(sent_bytes < 0){
        cout << "ERROR" << endl;
        exit(1);
    }
}

///////////check the return value!!!
void Client::receive(){

    while(true){
        char buffer[4096] = {0};
        int expected_data_len = sizeof(buffer);
        long read_bytes = recv(getSocket(), buffer, expected_data_len, 0);
        if(read_bytes == 0){
            continue;
        }
        else if (read_bytes < 0){
            cout << "ERROR" << endl;
            exit(1);
        }
        else {
            if(buffer[read_bytes - 3] == '$' && buffer[read_bytes - 2] == '$'
            && buffer[read_bytes - 1] == '$' && read_bytes > 3){
                buffer[read_bytes - 3] = '\0';
                buffer[read_bytes - 2] = '\0';
                buffer[read_bytes - 1] = '\0';
                cout << buffer;
                break;
            }else if(buffer[read_bytes - 3] == '$' && buffer[read_bytes - 2] == '$'
                     && buffer[read_bytes - 1] == '$' && read_bytes == 3){
                break;
            }else{
                cout << buffer;
                continue;
            }
        }
    }
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
