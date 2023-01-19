//
// Created by tomer on 1/16/23.
//

#ifndef KNN_SERVER_TESTCATALOG_H
#define KNN_SERVER_TESTCATALOG_H

#include <string>
#include <vector>
#include "Catalog.h"

using namespace std;

class TestCatalog : public Catalog{
private:
    string m_name;
    vector<double> m_vector;
public:
    TestCatalog(string name, vector<double> vector);

    void setName(string name);

    void setVector(vector<double> vector);

    string getName();

    vector<double> getVector();

};


#endif //KNN_SERVER_TESTCATALOG_H
