//
// Created by Tomer on 06/12/2022.
//

#include "trainCatalog.h"

namespace classifiedCatalog {
    /**
     * constructor of trainCatalog. sets a default distance to 0 because we didn't check
     * distances from any vector yet.
     * @param name name of one of the kinds of the catalog.
     * @param vector a vector.
     */
    trainCatalog::trainCatalog(string name, vector<double> vector) {
        setName(name);
        setVector(vector);
        setDistance(0);
    }

    /**
     * setter of name.
     * @param name name of the kinds of the catalog.
     */
    void trainCatalog::setName(string name) {
        this->m_name = name;
    }

    /**
     * setter of vector
     * @param vector a vector.
     */
    void trainCatalog::setVector(vector<double> vector) {
        this->m_vector = vector;
    }

    /**
     * setter of distance.
     * @param distance distance between this vector and the new coming vector
     */
    void trainCatalog::setDistance(double distance) {
        this->m_distance = distance;
    }

    /**
     * getter of name.
     * @return string.
     */
    string trainCatalog::getName() {
        return this->m_name;
    }

    /**
     * getter of vector.
     * @return vector<double>
     */
    vector<double> trainCatalog::getVector() {
        return this->m_vector;
    }

    /**
     * getter of distance.
     * @return int.
     */
    double trainCatalog::getDistance() {
        return this->m_distance;
    }
}