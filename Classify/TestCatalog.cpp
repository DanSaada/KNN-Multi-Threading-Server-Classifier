//
// Created by tomer on 1/16/23.
//

#include "TestCatalog.h"

TestCatalog::TestCatalog(string name, vector<double> vector) {
    setName(name);
    setVector(vector);
}

void TestCatalog::setName(string name) {
    this->m_name = name;
}

void TestCatalog::setVector(vector<double> vector) {
    this->m_vector = vector;
}

string TestCatalog::getName() {
    return this->m_name;
}

vector<double> TestCatalog::getVector() {
    return this->m_vector;
}
