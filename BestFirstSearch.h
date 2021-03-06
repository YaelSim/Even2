//
// Created by yael and linoy on 17/01/2020.
//

#ifndef EVEN2_BESTFIRSTSEARCH_H
#define EVEN2_BESTFIRSTSEARCH_H

#include <queue>
#include "Searcher.h"
#include <list>
#include <unordered_set>
#include <algorithm>

using namespace std;

template <class T>
class BestFirstSearch: public Searcher<T> {
public:
    BestFirstSearch() = default;

    string getNameOfSearcher() override {
        return "BestFirstSearch";
    }

    vector<State<T> *> search(Searchable<T> *searchable) override {
        int numOfVertex = 0;
        vector<State<T>*> stateVec; //traceBack will "remember" our way back with our father vertices.
        unordered_set<State<T>*> closed;
        int foundInOpen, foundInClose;
        list<State<T>*> openList;
        State<T>* currState = searchable->getInitialState();
        openList.push_back(currState);

        while (!openList.empty()) {
            State<T>* n = theSmallestInList(openList); //The best state!
            //mark as visited
            n->setIsVisited(true);

            State<T>* checkIfQInFront = openList.front();
            while (!(checkIfQInFront->isEqual(n))) {
                openList.push_back(checkIfQInFront);
                openList.pop_front();
                checkIfQInFront = openList.front();
            }
            openList.pop_front();
            numOfVertex++;
            //Add the popped n to the closed set
            closed.insert(n);

            if (n->isEqual(searchable->getGoalState())) {
                while (!n->isEqual(searchable->getInitialState())) {
                    stateVec.push_back(n);
                    this->totalCost += n->getVertexValue();
                    n = n->getFatherVertex();
                }
                stateVec.push_back(n);
                this->totalCost += n->getVertexValue();
                vector<State<T>*> traceBack;
                auto i = stateVec.rbegin();
                for (; i != stateVec.rend(); i++) {
                    State<T>*& curr = *i;
                    traceBack.push_back((*i));
                }
                this->countVisitedVertexes = numOfVertex;
                return traceBack;
            }

            vector<State<T>*> adjVec = searchable->getAllPossibleStates(n);
            for (State<T>* currAdj : adjVec) {
                foundInOpen = 0;
                foundInClose = 0;
                //check if exist in openList
                auto i = openList.begin();
                for (; i != openList.end(); i++) {
                    State<T>*& currInOpen = *i;
                    //not in open
                    if (currInOpen->isEqual(currAdj)) {
                        foundInOpen = 1;
                    }
                }
                //check if exist in closedList
                if (closed.find(currAdj) != closed.end()) {
                    foundInClose = 1;
                }
                //not in closed AND not in open
                if ((foundInOpen == 0) && (foundInClose == 0)) {
                    currAdj->setFatherVertex(n);
                    //add the cost to the subCost of currAdj, and push currAdj to the openList.
                    double cost = n->getSubCost() + currAdj->getVertexValue();
                    currAdj->setSubCost(cost);
                    openList.push_back(currAdj);
                } else if (currAdj->getSubCost() > (n->getSubCost() + currAdj->getVertexValue())) {
                    //if this new path is better than the previous path!

                    //if currAdj is not in openList, add it to openList
                    auto j = openList.begin();
                    foundInOpen = 0;
                    for (; j != openList.end(); j++) {
                        State<T>*& currInOpen = *j;
                        //If currAdj is in open, foundInOpen = 1.
                        if (currInOpen->isEqual(currAdj)) {
                            foundInOpen = 1;
                        }
                    }
                    if (foundInOpen == 0) {
                        openList.push_back(currAdj);
                    } else {
                        //else - adjust its priority in open.
                        while ((!openList.empty()) && (!(openList.front()->isEqual(currAdj)))) {
                            State<T>* topOfList = openList.front();
                            openList.push_back(topOfList);
                            openList.pop_front();
                        }
                    }
                }
            }
        }
    }

    State<T>* theSmallestInList(list<State<T>*> openList) {
        State<T>* curr = openList.front();
        State<T>* minState = openList.front();
        double min = curr->getSubCost();
        auto i = openList.begin();
        for (; i != openList.end(); i++) {
            State<T>*& checked = *i;
            if(checked->getSubCost() < min) {
                min = checked->getSubCost();
                minState = checked;
            }
        }
        return minState;
    }
};

#endif //EVEN2_BESTFIRSTSEARCH_H