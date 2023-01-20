//
// Created by dansa97 on 1/12/23.
//

#include "SocketIO.h"


/**
* This function read a string from the client using socket.
* @return a string from the user
*/
///////check that works!!!!!!!!!!
string SocketIO:: read() {
    string toRead;
    while(true) {
        char buffer[4096] = {0};
        int expected_data_len = sizeof(buffer);
        long read_bytes = recv(this->clientId, buffer, expected_data_len, 0);
        if (read_bytes == 0) {
            continue;
        } else if (read_bytes < 0) {
            cout << "ERROR" << endl;
            exit(1);
        }else{
            int i = 0;
            while (buffer[i] != '\0') {
                if(read_bytes >= 3 && buffer[i - 2] == '$' && buffer[i - 1] == '$' && buffer[i] == '$'){
                    buffer[i - 2] = '\0';
                    buffer[i - 1] = '\0';
                    buffer[i] = '\0';
                    return toRead;
                }
                if(buffer[i] != '$'){
                    toRead += buffer[i];
                }
                i++;
            }
        }

    }




//    char temp[4096] = {0};
//    string data;
//
//    //read data from the client char by char and create a string from it
//    while (temp != '\n') {
//        ///////////add validation check and size of massage!!!!
//        recv(this->clientId, &temp, sizeof(char), 0);
//
//        //end of data
//        if(temp == '\n'){
//            break;
//        }
//        data += temp;
//    }
//    return data;
};

/**
* This function write a string to the client using socket.
* @param toSend
*/
void SocketIO:: write(string toSend) {
    char data_addr[4096] = {0};
    toSend.copy(data_addr, toSend.length(), 0);
    int data_len = (int) strlen(data_addr);
    long sent_bytes = send(this->clientId, data_addr, data_len, 0);
    if(sent_bytes < 0){
        cout << "ERROR" << endl;
        exit(1);
    }

   // send(this->clientId, toSend.c_str(), toSend.length(), 0);
}

SocketIO::SocketIO(int id) {
    setId(id);
};