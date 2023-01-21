//
// Created by tomer on 1/16/23.
//

#ifndef KNN_SERVER_CATALOG_H
#define KNN_SERVER_CATALOG_H

#include <string>
#include <vector>
#include "../Distances/Distance.h"

using namespace std;
class Catalog {
protected:
    string m_name;
    vector<double> m_vector;
public:
    void setName(string name);

    void setVector(vector<double> vector);

    string getName();

    vector<double> getVector();
};


#endif //KNN_SERVER_CATALOG_H
