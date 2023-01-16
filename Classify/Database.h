//
// Created by Dansa on 06/12/2022.
//

#ifndef K_NEAREST_NEIGHBORS_DATABASE_H
#define K_NEAREST_NEIGHBORS_DATABASE_H


#include "../Distances/Distance.h"
#include "trainCatalog.h"
#include "fstream"


using namespace classifiedCatalog;

class Database {
private:
    Distance* m_distance;
    string m_file;
    string m_distanceString;
    int m_k;
public:
    vector<trainCatalog> m_data;

    Database(string fileName, int k);

    int getK() const;

    void setK(int k);

    vector<trainCatalog> *getMData();

    trainCatalog *setCatalog(string str);

    static bool checkIfNum(string substring);

    void setData();

    void add(string newName, vector<double> unclassifiedVector);

    string findKNN(Distance &d, vector<double> unclassifiedVector);

    string classifyVector();

    bool compare(int i, int j);

    void swap(int i, int j);

    int partition(int left, int right, int pivot);

    const string &getMDistanceString() const;

    void setMDistanceString(const string &mDistanceString);

    Distance *getMDistance() const;

    void setMDistance(const string& distance);

    void select(int left, int right);
};


struct Info{
    Database *database;
    bool isUploaded = false;
    bool isClassified = false;
    bool isDisplaying = false;
    bool isDownloading = false;
};

#endif //K_NEAREST_NEIGHBORS_DATABASE_H
