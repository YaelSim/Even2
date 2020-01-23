//
// Created by yael on 14/01/2020.
//

#ifndef EVEN2_SEARCHER_H
#define EVEN2_SEARCHER_H

#include <string>
#include <vector>
#include "Searchable.h"
#include "State.h"

using namespace std;

template <class T>
class Searcher {
protected:
    int countVisitedVertexes = 0;
    double totalCost = 0;
public:
    virtual vector<State<T>*> search(Searchable<T>* searchable) = 0;
    virtual string getNameOfSearcher() = 0;
};

#endif //EVEN2_SEARCHER_H
