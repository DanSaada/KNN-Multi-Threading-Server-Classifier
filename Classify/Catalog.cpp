//
// Created by tomer on 1/16/23.
//

#include "Catalog.h"

/**
 * setter of name.
 * @param name name of the kinds of the catalog.
 */
void Catalog::setName(string name) {
    this->m_name = name;
}

/**
 * setter of vector
 * @param vector a vector.
 */
void Catalog::setVector(vector<double> vector) {
    this->m_vector = vector;
}


/**
  * getter of name.
  * @return string.
  */
string Catalog::getName() {
    return this->m_name;
}

/**
 * getter of vector.
 * @return vector<double>
 */
vector<double> Catalog::getVector() {
    return this->m_vector;
}
