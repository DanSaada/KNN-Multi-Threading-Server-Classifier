//
// Created by tomer on 1/16/23.
//

#ifndef KNN_SERVER_TESTCATALOG_H
#define KNN_SERVER_TESTCATALOG_H

#include "Catalog.h"

using namespace std;

class TestCatalog : public Catalog{
public:
    TestCatalog(string name, vector<double> vector);
};


#endif //KNN_SERVER_TESTCATALOG_H
