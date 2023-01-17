//
// Created by dansa97 on 1/12/23.
//

#include "SocketIO.h"


/**
* This function read a string from the client using socket.
* @return a string from the user
*/
string SocketIO:: read() {
    char temp = 0;
    string data;

    //read data from the client char by char and create a string from it
    while (temp != '\n') {
        recv(this->clientID, &temp, sizeof(char), 0);

        //end of data
        if(temp == '\n'){
            break;
        }
        data += temp;
    }
    return data;
};

/**
* This function write a string to the client using socket.
* @param text
*/
void SocketIO:: write(string text) {
    send(this->clientID, text.c_str(), text.length(), 0);
};