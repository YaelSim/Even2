//
// Created by yael on 17/01/2020.
//

#ifndef EVEN2_DFS_H
#define EVEN2_DFS_H

#include "Searcher.h"
#include <stack>

template <class T>
class DFS: public Searcher<T> {
public:
    DFS() = default;
    vector<State<T>*> search(Searchable<T>* searchable) override {
        vector<State<T>*> stateVec, adjVec;
        stack<State<T>*> dfsStack;
        State<T>* currState = searchable->getInitialState();
        // marked as visited
        currState->setIsVisited(true);
        //insert the first vertex     check if lines 22,23 are actually needed!!!!!!!!!!!!!!*****************
        stateVec.push_back(currState);
        //while we didn't find the goal index
        while(!searchable->isGoalState(currState)) {
            //get adj
            adjVec = searchable->getAllPossibleStates(currState);
            auto i = adjVec.rbegin();
            for (; i != adjVec.rend(); i++) {
                State<T>*& curr = *i;
                if (!curr->getIsVisited()) {
                    curr->setIsVisited(true);
                    dfsStack.push(curr);
                }
            }
            //pop the top in the stack
            if(!dfsStack.empty()) {
                currState = dfsStack.top();
                dfsStack.pop();
                stateVec.push_back(currState);
            }
        }
        this->countVisitedVertexes = stateVec.size();
        for(int i = 0; i < stateVec.size(); i++) {
            State<T>* current = stateVec.at(i);
            this->totalCost += (current->getVertexValue());
        }
        return stateVec;
    }
};

#endif //EVEN2_DFS_H
