//
// Created by linoy on 12/01/2020.
//

#ifndef EVEN2_FILECACHEMANAGER_H
#define EVEN2_FILECACHEMANAGER_H

#include "CacheManager.h"


using namespace std;

class FileCacheManager: public CacheManager<string, string> {
private:
    unordered_map<string,string> cacheMap;
    void updateCacheMapFromFiles(string problem);
    string getCurrentFileName(const string& problem);
public:
    FileCacheManager() = default;
    bool doesASolutionExist(string problem) override ;
    string getSolution(string problem) override;
    void saveSolution(string problem, string solution) override ;
};

#endif //EVEN2_FILECACHEMANAGER_H
