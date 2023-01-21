//
// Created by Dansa on 06/12/2022.
//

#ifndef K_NEAREST_NEIGHBORS_DATABASE_H
#define K_NEAREST_NEIGHBORS_DATABASE_H


#include "../Distances/Distance.h"
#include "TrainCatalog.h"
#include "TestCatalog.h"
#include "fstream"


using namespace classifiedCatalog;

class Database {
private:
    Distance* m_distance;
    string m_distanceString;
    int m_k;
    vector<TrainCatalog> m_Train;
    vector<TestCatalog> m_Test;
public:

    Database(int k, const string& dis);

    int getK() const;

    void setK(int k);

    vector<TestCatalog> *getMTest();

    TestCatalog *setTestCatalog(string str);

    vector<TrainCatalog> *getMTrain();

    TrainCatalog *setTrainCatalog(string str);

    static bool checkIfNum(string substring);

    string findKNN(vector<double> unclassifiedVector);

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
    Database* database = new Database(5, "AUC");
    bool isUploaded = false;
    bool isClassified = false;
    bool isDisplaying = false;
    bool isDownloading = false;
};

#endif //K_NEAREST_NEIGHBORS_DATABASE_H
