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

    string getNameOfSearcher() override {
        return "DFS";
    }

    vector<State<T>*> search(Searchable<T>* searchable) override {
        vector<State<T>*> stateVec, adjVec;
        stack<State<T>*> dfsStack;
        State<T>* currState = searchable->getInitialState();
        // marked as visited
        currState->setIsVisited(true);

        //while we didn't find the goal index
        while(!searchable->isGoalState(currState)) {
            //get adj
            adjVec = searchable->getAllPossibleStates(currState);
            auto i = adjVec.rbegin();
            for (; i != adjVec.rend(); i++) {
                State<T>*& curr = *i;
                if (!curr->getIsVisited()) {
                    curr->setIsVisited(true);
                    if(curr->getFatherVertex() == nullptr) {
                        curr->setFatherVertex(currState);
                    }
                    dfsStack.push(curr);
                }
            }
            //pop the top in the stack
            if(!dfsStack.empty()) {
                currState = dfsStack.top();
                dfsStack.pop();
            }
        }
        //get all the vertices we visited
        while (currState->getFatherVertex() != nullptr) {
            stateVec.push_back(currState);
            this->totalCost += currState->getVertexValue();
            currState = currState->getFatherVertex();
        }
        stateVec.push_back(currState);
        this->totalCost += currState->getVertexValue();
        //reverse the vertices
        vector<State<T>*> traceBack;
        auto i = stateVec.rbegin();
        for (; i != stateVec.rend(); i++) {
            State<T>*& curr = *i;
            traceBack.push_back((*i));
        }
        //count the amount of vertices we visited to the goal
        this->countVisitedVertexes = traceBack.size();
        return traceBack;
    }
};

#endif //EVEN2_DFS_H