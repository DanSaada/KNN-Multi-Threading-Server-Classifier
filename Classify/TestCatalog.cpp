//
// Created by tomer on 1/16/23.
//

#include "TestCatalog.h"

TestCatalog::testCatalog(string name, vector<double> vector, int id) {
    setName(name);
    setVector(vector);
    setDistance(0);
    setId(id);
}

void TestCatalog::setName(string name) {
    this->m_name = name;
}

void TestCatalog::setVector(vector<double> vector) {
    this->m_vector = vector;
}

void TestCatalog::setDistance(double distance) {
    this->m_distance = distance;
}

string TestCatalog::getName() {
    return this->m_name;
}

vector<double> TestCatalog::getVector() {
    return this->m_vector;
}

double TestCatalog::getDistance() {
    return this->m_distance;
}

int TestCatalog::getId() const {
    return m_id;
}

void TestCatalog::setId(int id) {
    this->m_id = id;
}
