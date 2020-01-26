//
// Created by yael and linoy on 17/01/2020.
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
        int numOfVertex = 0;
        vector<State<T>*> stateVec, adjVec;
        stack<State<T>*> dfsStack;
        State<T>* currState = searchable->getInitialState();
        dfsStack.push(currState);

        while(!dfsStack.empty()) {
            //get the first node in the stack
            State<T>* node = dfsStack.top();
            numOfVertex++;
            //pop the top in the stack
            dfsStack.pop();
            // mark the node as visited
            if(!(node->getIsVisited())) {
                node->setIsVisited(true);
            }

            //if the node is the goal
            if(node->isEqual(searchable->getGoalState())) {
                while (!(node->getFatherVertex())->isEqual(searchable->getInitialState())) {
                    stateVec.push_back(node);
                    node = node->getFatherVertex();
                }
                stateVec.push_back(node);
                this->totalCost = stateVec.size();
                //reverse the vertices
                vector<State<T>*> traceBack;
                auto i = stateVec.rbegin();
                for (; i != stateVec.rend(); i++) {
                    State<T>*& curr = *i;
                    traceBack.push_back((*i));
                }
                //count the amount of vertices we visited to the goal
                this->countVisitedVertexes = numOfVertex;
                return traceBack;
            }
            //get adj
            adjVec = searchable->getAllPossibleStates(node);
            for (State<T>* currAdj : adjVec) {
                //set and push to stack if not visited
                if (!(currAdj->getIsVisited())) {
                    currAdj->setIsVisited(true);
                    currAdj->setFatherVertex(node);;
                    dfsStack.push(currAdj);
                }
            }
        }
    }
};

#endif //EVEN2_DFS_H