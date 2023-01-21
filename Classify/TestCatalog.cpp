//
// Created by tomer on 1/16/23.
//

#include "TestCatalog.h"

/**
 * constructor of TestCatalog
 * @param name of the catalog
 * @param vector vector of numbers
 */
TestCatalog::TestCatalog(string name, vector<double> vector) {
    setName(name);
    setVector(vector);
}
