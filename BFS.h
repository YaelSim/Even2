//
// Created by yael and linoy on 17/01/2020.
//

#ifndef EVEN2_BFS_H
#define EVEN2_BFS_H
#include "Searcher.h"
#include <queue>
#include <list>

template <class T>
class BFS: public Searcher<T> {
public:
    BFS() = default;

    string getNameOfSearcher() override {
        return "BFS";
    }

    vector<State<T>*> search(Searchable<T>* searchable) override {
        int numOfVertex = 0;
        vector<State<T>*> stateVec;
        list<State<T>*> openList;
        State<T>* currState = searchable->getInitialState();
        // marked as visited
        currState->setIsVisited(true);
        //insert the first vertex
        openList.push_back(currState);
        numOfVertex++;

        while(!openList.empty()) {
            //get the front from the list and pop him
            State<T>* frontNode = openList.front();
            openList.pop_front();
            numOfVertex++;
            if(frontNode->isEqual(searchable->getGoalState())) {
                //get all the vertices we visited
                while (frontNode->getFatherVertex() != nullptr) {
                    stateVec.push_back(frontNode);
                    this->totalCost += frontNode->getVertexValue();
                    frontNode = frontNode->getFatherVertex();
                }
                stateVec.push_back(frontNode);
                this->totalCost += frontNode->getVertexValue();
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
            //get the adj of frontNode
            vector<State<T>*> adjVec = searchable->getAllPossibleStates(frontNode);
            for (State<T>* currAdj : adjVec) {
                //set and push to openList if not visited
                if(!currAdj->getIsVisited()) {
                    currAdj->setIsVisited(true);
                    //set frontNode as parent
                    currAdj->setFatherVertex(frontNode);
                    openList.push_back(currAdj);
                }
            }
        }
    }
};

#endif //EVEN2_BFS_H