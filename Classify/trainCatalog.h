//
// Created by Tomer on 06/12/2022.
//

#ifndef WORKS_IN_C___CATALOG_H
#define WORKS_IN_C___CATALOG_H

#include "../Distances/Distance.h"
#include "Catalog.h"

namespace classifiedCatalog {
    class trainCatalog : Catalog{
    private:
        string m_name;
        vector<double> m_vector;
        double m_distance;
    public:
        trainCatalog(string name, vector<double> vector);

        void setName(string name);

        void setVector(vector<double> vector);

        void setDistance(double distance);

        string getName();

        vector<double> getVector();

        double getDistance();
    };
}


#endif //WORKS_IN_C___CATALOG_H
