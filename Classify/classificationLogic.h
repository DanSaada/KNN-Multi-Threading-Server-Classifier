//
// Created by Dansa on 31/12/2022.
//

#ifndef PROJECT_CLASSIFICATIONLOGIC_H
#define PROJECT_CLASSIFICATIONLOGIC_H

#include "Database.h"
#include "../Distances/Distance.h"
#include "../Distances/Euclidean.h"
#include "../Distances/Manhattan.h"
#include "../Distances/Chebyshev.h"
#include "../Distances/Canberra.h"
#include "../Distances/Minkowski.h"
#include "cstring"

bool checkStr(string str);
vector<double> createVec();
Database *initializeDatabase(string file, int k);
Distance *chooseDis(const char *disAlg);
string newVectorClassification(Database *dataBase, Distance *dis, string vec);
bool isPositiveInteger(const string &s);

#endif //PROJECT_CLASSIFICATIONLOGIC_H
