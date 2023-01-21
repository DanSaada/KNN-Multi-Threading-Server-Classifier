//
// Created by dansa97 on 1/12/23.
//

#include "StandardIO.h"

/**
* This function read a string from the user.
* @return a string from the user
*/
string  StandardIO:: read() {
    string input;
    getline(cin, input);
    return input;
};

/**
* This function write a string to the user.
* @param text to be printed in the console
*/
void StandardIO:: write(string text) {
    cout << text;
};
