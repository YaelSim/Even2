//
// Created by yael on 22/01/2020.
//

#ifndef EVEN2_OBJECTADAPTER_H
#define EVEN2_OBJECTADAPTER_H

#include "Searcher.h"
#include "Solver.h"
#include "Matrix.h"

template<class Problem, class Solution>
class ObjectAdapter: public Solver<Problem, Solution> {
private:
    Searcher<Problem>* searcher;
public:
    ObjectAdapter() = default;

    void setSearcher(Searcher<Problem>* alg) {
        this->searcher = alg;
    }

    Solution runSearcher(Searchable<Problem>* searchable) {
        //which algorithm we need to "search"***********************************
        // do we need to get it and send it as matrix?????**********************
        vector<State<Problem>> solutionVec = this->searcher->search(searchable);
    }
};

#endif //EVEN2_OBJECTADAPTER_H
