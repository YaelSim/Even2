//
// Created by linoy and yael on 12/01/2020.
//

#include <iostream>
#include <utility>
#include "FileCacheManager.h"

//this method inserts the problem and the solution into the cacheMap and writes it also to the matching file.
void FileCacheManager::saveSolution(string problem, string solution) {
    //insert to cache map
    this->cacheMap[problem] = solution;
    // write to file the new solution
    fstream file;
    file.open(getCurrentFileName(problem), std::ios::app);
    if (!file) {
        cout<<"error in opening file!"<<endl;
    }
    problem += "\n";
    solution += "\n";
    file << problem << solution << "\n";
    file.close();
}

//this method returns true if a file of the exact given problem already exists.
bool FileCacheManager::doesASolutionExist(string problem) {
    //search for it in the cache map
    if (this->cacheMap.find(problem) == this->cacheMap.end()) {
        if (this->cacheMap.empty()) {
            //cacheMap is empty while first running the program. We shall initialize it.
            updateCacheMapFromFiles(problem);
            //Check again!
            return !(this->cacheMap.find(problem) == this->cacheMap.end());
        }
    } else {
        return true;
    }
    return false;
}

string FileCacheManager::getSolution(string problem) {
    string solution = "notExist";
    // search it in map - if exist get the solution
    if(doesASolutionExist(problem)) {
        solution = this->cacheMap[problem];
    }
    return solution;
}

//If the cacheMap is empty, this method is called in order to update its values.
void FileCacheManager::updateCacheMapFromFiles(string problem) {
    ifstream file;
    int flag = 0, gotPair = 0;
    string line, currProblem, currSolution;
    file.open(getCurrentFileName(problem));
    if(file) {
        //Read its content and look
        while (getline(file, line)) {
            if(line == "\n") {
                continue;
            }
            if(flag == 0) {
                //if token are needed remove them from here
                currProblem = line;
                flag = 1;
                gotPair++;
            } else {
                //if token are needed remove them from here
                currSolution = line;
                flag = 0;
                gotPair++;
            }
            if(gotPair == 2) {
                this->cacheMap[currProblem] = currSolution;
                gotPair = 0;
            }
        }
        file.close();
    }
}

//This is a hash method - it creates a unique file name according to the current problem + and the current algorithm.
string FileCacheManager::getCurrentFileName(const string& problem) {
    string finalFileName;
    std::size_t name = std::hash<string>{}(problem);
    finalFileName = to_string(name);

    //append to fileName the name of the current algorithm.
    finalFileName.append(this->nameOfSearchAlg);
    finalFileName.append(".txt");
    return finalFileName;
}

