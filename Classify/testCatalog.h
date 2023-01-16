//
// Created by tomer on 1/16/23.
//

#ifndef KNN_SERVER_TESTCATALOG_H
#define KNN_SERVER_TESTCATALOG_H

#include <string>
#include <vector>
#include "Catalog.h"

using namespace std;

class testCatalog : Catalog{
private:
    string m_name;
    vector<double> m_vector;
    double m_distance;
    int m_id;
public:
    testCatalog(string name, vector<double> vector, int id);

    void setName(string name);

    void setVector(vector<double> vector);

    void setDistance(double distance);

    string getName();

    vector<double> getVector();

    int getId() const;

    void setId(int id);

    double getDistance();


};


#endif //KNN_SERVER_TESTCATALOG_H
