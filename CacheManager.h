//
// Created by linoy on 12/01/2020.
//

#ifndef EVEN2_CACHEMANAGER_H
#define EVEN2_CACHEMANAGER_H

#include <string>
#include <unordered_map>
#include <fstream>
#include <functional>

template <class Problem, class Solution>
class CacheManager {
public:
    CacheManager() = default;
    virtual bool doesASolutionExist(Problem problem) = 0;
    virtual Solution getSolution(Problem problem) = 0;
    virtual void saveSolution(Problem problem, Solution solution) = 0; //According to the type of our cache.
};

#endif //EVEN2_CACHEMANAGER_H
