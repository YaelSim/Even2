//
// Created by linoy on 12/01/2020.
//

#ifndef EVEN2_CACHEMANAGER_H
#define EVEN2_CACHEMANAGER_H

#include <string>
#include <unordered_map>
#include <fstream>
#include <functional>

using namespace std;

template <class Problem, class Solution>
class CacheManager {
protected:
    string nameOfSearchAlg;
public:
    CacheManager() = default;
    virtual bool doesASolutionExist(Problem problem) = 0;
    virtual Solution getSolution(Problem problem) = 0;
    void setAlg(string name) {
        this->nameOfSearchAlg = name;
    }
    virtual void saveSolution(Problem problem, Solution solution) = 0; //According to the type of our cache.
};

#endif //EVEN2_CACHEMANAGER_H
