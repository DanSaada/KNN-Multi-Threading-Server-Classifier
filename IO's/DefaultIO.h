//
// Created by dansa97 on 1/11/23.
//

#ifndef KNN_SERVER_DEFAULTIO_H
#define KNN_SERVER_DEFAULTIO_H

using namespace std;
#include "string"
#include "iostream"

//DefaultIO - an abstract class that is used to define ways to interact with the user.
class DefaultIO {
public:
    //constructor
    DefaultIO()= default;

    //read a string from the user
    virtual string  read()=0;

    //write a string to the user
    virtual void write(string output)=0;

    //destructor
    virtual ~DefaultIO() = default;
};


#endif //KNN_SERVER_DEFAULTIO_H
