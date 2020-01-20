//
// Created by yael on 17/01/2020.
//

#ifndef EVEN2_BFS_H
#define EVEN2_BFS_H
#include "Searcher.h"
#include <queue>

template <class T>
class BFS: public Searcher<T> {
public:
    BFS() = default;

    vector<State<T>*> search(Searchable<T>* searchable) override {
        vector<State<T>*> stateVec, adjVec;
        queue<State<T>*> bfsQueue;
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
                    bfsQueue.push(curr);
                }
            }
            //pop the top in the stack
            if(!bfsQueue.empty()) {
                currState = bfsQueue.front();
                bfsQueue.pop();
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

#endif //EVEN2_BFS_H
