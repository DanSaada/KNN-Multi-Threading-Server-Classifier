//
// Created by Dansa on 31/12/2022.
//

#include "ClassificationLogic.h"

/**
 * This function checks if a string is a positive number
 *
 * @param str the string to check.
 *
 * @return true if the string is a positive number, and false if it is not.
 */
bool isPositiveInteger(const string &s) {
    if (s.empty() || ((!isdigit(s[0])))) {
        return false;
    }

    char *p;
    strtol(s.c_str(), &p, 10);
    return (*p == 0);
}
