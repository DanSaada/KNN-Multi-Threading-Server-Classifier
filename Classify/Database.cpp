//
// Created by Dansa on 06/12/2022
//
#include "Database.h"
#include "../Distances/Euclidean.h"
#include "../Distances/Manhattan.h"
#include "../Distances/Chebyshev.h"
#include "../Distances/Canberra.h"

/**
 * constructor of dataBase
 * @param k for select
 * @param dis distance
 */
Database::Database(int k, const string& dis) {
    setK(k);
    setMDistance(dis);
    setMDistanceString(dis);
}

/**
 * getter for the size of k
 * @return k
 * */
int Database::getK() const {
    return m_k;
}

/**
 * setter for k
 * @param k - value for size of the neighbors group
 * */
void Database::setK(int k) {
    if(k == 0){
        m_k = 1;
    }else{
        m_k = k;
    }
}

/**
 * getter for the data.
 * @return A pointer to the data member.
 */
vector<TrainCatalog> *Database::getMTrain() {
    return &m_Train;
}

vector<TestCatalog> *Database::getMTest() {
    return &m_Test;
}

/**
 * This function checks if the string is a valid number.
 *
 * @param substring the string that we want to check if it's a number.
 *
 * @return a boolean value.
 */
bool Database::checkIfNum(string substring) {
    //flag for decimal point.
    bool flag = false;
    //flag for e number.
    bool eFlag = false;
    //flag for plus or minus after e.
    bool plusMinusFlag = false;
    //checking all the edge cases of valid numbers.
    for (size_t i = 0; i < substring.length(); i++) {
        if (substring.at(i) == 'E') {
            if (eFlag) {
                return false;
            }
            eFlag = true;
            continue;
        }
        //check the character after the e number.
        if (eFlag && !plusMinusFlag) {
            //if the characters after the e number are not plus or minus this is not a number!
            if (substring.at(i) != '+' && substring.at(i) != '-') {
                return false;
            }
            plusMinusFlag = true;
            continue;
        }
        //checks if the first letter is a number or minus or point.
        if (i == 0 && isdigit(substring.at(0)) == 0 && substring.at(0) != '-' && substring.at(i) != '.') {
            return false;
        }
        //checks if there are more than 1 decimal points.
        if (substring.at(i) == '.') {
            if (flag) {
                return false;
            }
            flag = true;
            continue;
        }
        //verifying there isn't a none valid character from the 2nd character and on.
        if (i > 0 && isdigit(substring.at(i)) == 0 && substring.at(i) != '.') {
            return false;
        }
    }
    return true;
}

/**
 * It takes a string, checks if it's a number using an auxiliary function, and if it
 * is, it adds it to a new created vector.
 * @param str the string that we get from the user.
 * @return A pointer to a new catalog.
 */
TrainCatalog *Database::setTrainCatalog(string str) {
    vector<double> newVector;
    //making a flag to the end of the string.
    str += '\0';
    string substring;
    string name;
    //iterating over the string.
    for (char x: str) {
        if (x == ',') {
            if (!checkIfNum(substring)) {
                substring = "";
                continue;
            }
            newVector.push_back(stod(substring));
            //nullifies the substring and the flag.
            substring = "";
        } else if (x == '\0') {
            name = substring;
        } else {
            substring += x;
        }
    }
    if (!m_Train.empty()) {
        if (m_Train.at(0).getVector().size() != newVector.size()) {
            return nullptr;
        }
    }
    auto *newCatalog = new TrainCatalog(name, newVector);
    return newCatalog;
}

/**
 * It takes a string, checks if it's a number using an auxiliary function, and if it
 * is, it adds it to a new created vector.
 * @param str the string that we get from the user.
 * @return A pointer to a new catalog.
 */
TestCatalog *Database::setTestCatalog(string str) {
    vector<double> newVector;
    //making a flag to the end of the string.
    str += '\0';
    string substring;
    //iterating over the string.
    for (char x: str) {
        if (x == ',') {
            if (!checkIfNum(substring)) {
                substring = "";
                continue;
            }
            newVector.push_back(stod(substring));
            //nullifies the substring and the flag.
            substring = "";
        } else {
            substring += x;
        }
    }
    if (m_Train.at(0).getVector().size() != newVector.size()) {
        return nullptr;
    }
    auto *newCatalog = new TestCatalog("", newVector);
    return newCatalog;
}

/**
 * This function finds the k's nearest neighbors using the select algorithm.
 * @param d - the metric distance algorithm to use
 * @param unclassifiedVector - the new inserted vector to be classified
 * @return the classification of the new vector
 * */
string Database::findKNN(vector<double> unclassifiedVector) {
    for (auto &i: m_Train) {
        i.setDistance(this->m_distance->distance(i.getVector(), unclassifiedVector));
    }
    select(0, (int) m_Train.size() - 1);
    string classified = classifyVector();
    return classified;
}

/**
 * This function classified and return a new vector classification
 * @return the classification of a vector
 * */
string Database::classifyVector() {
    // Create an empty map
    map<string, int> count;
    if(this->m_k > (int) m_Train.size()){
        this->m_k = (int) this->m_Train.size();
    }
    //iterate over the k's nearest neighbors and update the frequency of each catalog
    for (int i = 0; i < this->m_k; i++) {
        //get the catalog name
        string group = this->m_Train.at(i).getName();
        //if name is already in map, increment its frequency by 1
        if (count.find(group) != count.end())
            count[group]++;
            //else insert this element with frequency 1
        else
            count[group] = 1;
    }

    //count the number of catalog in each group and return the biggest
    int max_count = 0;
    string mostFrequentName;
    for (auto &itr: count) {
        if (max_count < itr.second) {
            max_count = itr.second;
            mostFrequentName = itr.first;
        }
    }
    return mostFrequentName;
}

/**
 * This function returns true if the distance of the point at index i is less than the
 * distance of the point at index j.
 * @param i the index of the first element to compare
 * @param j the index of the first element to be compared
 * @return A boolean value.
 */
bool Database::compare(int i, int j) {
    return (m_Train[i].getDistance() < m_Train[j].getDistance());
}

/**
 * This function swaps the two TrainCatalog objects at the given indices
 * @param i the index of the first item to swap
 * @param j the index of the first item to be swapped
 */
void Database::swap(int i, int j) {
    TrainCatalog tempCatalog = m_Train[i];
    m_Train[i] = m_Train[j];
    m_Train[j] = tempCatalog;
}

/**
 * This function implements a classic partition for the select algorithm.
 * First it takes the pivot, swaps it with the rightmost element, then iterates through
 * the array, swapping elements that are less than the pivot with the leftmost element,
 * and then swaps the pivot with the leftmost element.
 * @param left the leftmost index of the array
 * @param right the rightmost index of the array
 * @param pivot the index of the pivot element
 * @return The index of the pivot.
 */
int Database::partition(int left, int right, int pivot) {
    swap(pivot, right);
    int tempIndex = left;
    for (int i = left; i < right; i++) {
        if (compare(i, right)) {
            swap(tempIndex, i);
            tempIndex++;
        }
    }
    swap(right, tempIndex);
    return tempIndex;
}


/**
 * This function implements the select recursive algorithm.
 * It basically finds the kth smallest element in the array.
 * @param left the left index of the array
 * @param right the rightmost index of the array
 * @return The kth smallest element in the array.
 */
void Database::select(int left, int right) {
    if (left == right) {
        return;
    }
    int pivot = left + (right - left) / 2;
    pivot = partition(left, right, pivot);
    if (m_k == pivot + 1) {
        return;
    } else if (m_k < pivot + 1) {
        return select(left, pivot - 1);
    } else {
        return select(pivot + 1, right);
    }
}

/**
 * getter of Distance string
 * @return string
 */
const string &Database::getMDistanceString() const {
    return m_distanceString;
}

/**
 * setter of Distance string
 * @param mDistanceString string
 */
void Database::setMDistanceString(const string &mDistanceString) {
    m_distanceString = mDistanceString;
}

/**
 * getter of Distance
 * @return &Distance
 */
Distance *Database::getMDistance() const {
    return m_distance;
}

/**
 * This function sets the distance metric to be used by the database
 *
 * @param distance The distance metric to use.
 *
 * @return The distance between two points.
 */
void Database::setMDistance(const string& distance) {
    //if the metric hasn't been changed
    if (getMDistanceString() == distance){
        return;
    }
     if (distance == "MAN") {
        this->m_distance  =  new Manhattan();
         setMDistanceString("MAN");
    } else if (distance == "CHB") {
        this->m_distance  =  new Chebyshev();
         setMDistanceString("CHB");
    } else if (distance == "CAN") {
        this->m_distance  =  new Canberra();
         setMDistanceString("CAN");
    } else if (distance == "MIN") {
        this->m_distance  =  new Minkowski();
         setMDistanceString("MIN");
    } else {
        this->m_distance  =  new Euclidean();
         setMDistanceString("AUC");
    }
}



