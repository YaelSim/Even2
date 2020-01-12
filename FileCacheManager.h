//
// Created by linoy on 12/01/2020.
//

#ifndef EVEN2_FILECACHEMANAGER_H
#define EVEN2_FILECACHEMANAGER_H

#include "CacheManager.h"

class FileCacheManager: public CacheManager {
public:
    FileCacheManager() = default;
    bool doesASolutionExist() override ; //parameter - Problem problem
    // Solution getSolution() override;
    void saveSolution() override ;
};

#endif //EVEN2_FILECACHEMANAGER_H
