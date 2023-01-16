//
// Created by tomer on 1/16/23.
//

#include "testCatalog.h"

testCatalog::testCatalog(string name, vector<double> vector, int id) {
    setName(name);
    setVector(vector);
    setDistance(0);
    setId(id);
}

void testCatalog::setName(string name) {
    this->m_name = name;
}

void testCatalog::setVector(vector<double> vector) {
    this->m_vector = vector;
}

void testCatalog::setDistance(double distance) {
    this->m_distance = distance;
}

string testCatalog::getName() {
    return this->m_name;
}

vector<double> testCatalog::getVector() {
    return this->m_vector;
}

double testCatalog::getDistance() {
    return this->m_distance;
}

int testCatalog::getId() const {
    return m_id;
}

void testCatalog::setId(int id) {
    this->m_id = id;
}
