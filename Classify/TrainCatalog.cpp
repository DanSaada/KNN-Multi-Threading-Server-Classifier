//
// Created by Tomer on 06/12/2022.
//

#include "TrainCatalog.h"

namespace classifiedCatalog {
    /**
     * constructor of TrainCatalog. sets a default distance to 0 because we didn't check
     * distances from any vector yet.
     * @param name name of one of the kinds of the catalog.
     * @param vector a vector.
     */
    TrainCatalog::TrainCatalog(string name, vector<double> vector) {
        setName(name);
        setVector(vector);
        setDistance(0);
    }

    /**
     * setter of distance.
     * @param distance distance between this vector and the new coming vector
     */
    void TrainCatalog::setDistance(double distance) {
        this->m_distance = distance;
    }

    /**
     * getter of distance.
     * @return int.
     */
    double TrainCatalog::getDistance() {
        return this->m_distance;
    }
}