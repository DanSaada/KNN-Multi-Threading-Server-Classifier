//
// Created by Tomer on 06/12/2022.
//

#ifndef WORKS_IN_C___CATALOG_H
#define WORKS_IN_C___CATALOG_H

#include "Catalog.h"

namespace classifiedCatalog {
    class TrainCatalog : public Catalog{
    private:
        double m_distance;
    public:
        TrainCatalog(string name, vector<double> vector);

        void setDistance(double distance);

        double getDistance();
    };
}


#endif //WORKS_IN_C___CATALOG_H
