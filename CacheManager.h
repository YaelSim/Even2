//
// Created by linoy on 12/01/2020.
//

#ifndef EVEN2_CACHEMANAGER_H
#define EVEN2_CACHEMANAGER_H

class CacheManager {
private:
    virtual bool doesASolutionExist() = 0; //parameter - Problem problem
    // virtual Solution getSolution() = 0;
    virtual void saveSolution() = 0;
};

#endif //EVEN2_CACHEMANAGER_H
