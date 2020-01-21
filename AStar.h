//
// Created by yael on 17/01/2020.
//

#ifndef EVEN2_ASTAR_H
#define EVEN2_ASTAR_H

#include <vector>
#include "Searcher.h"
#include <list>
#include <algorithm>

using namespace std;

template <class T>
class AStar: public Searcher<T> {

public:
    AStar() = default;

    struct StateBehavior {
        State<T>* state;
        double f = 0;
        double g = 0;
        double h = 0;
    };

    vector<State<T> *> search(Searchable<T> *searchable) override {
        int foundInOpen = 0;
        //Initialize the open and closed list
        list<StateBehavior*> openList;
        list<StateBehavior*> closedList;
        State<T>* currState = searchable->getInitialState();
        StateBehavior initialVertex = {};
        initialVertex.state = currState;

        //put the starting node on the open list
        openList.push_back(&initialVertex);

        //3. while the open list is not empty
        while (!openList.empty()) {
            // a) find the node with the least f on the open list, call it "q"
            StateBehavior* q = theLeastFNode(openList);

            //b) pop q off the open list
            StateBehavior* checkIfQInFront = openList.front();
            while (!(checkIfQInFront->state->isEqual(q->state))) {
                openList.push_back(checkIfQInFront);
                openList.pop_front();
                checkIfQInFront = openList.front();
            }
            //pop q
            openList.pop_front();

            //check if we need to push it to the closedList

            // c) generate q's adj
            vector<State<T>*> adjVec = searchable->getAllPossibleStates(q->state);
            //set their parents to q
            for (State<T>* currAdj : adjVec) {
                currAdj->setFatherVertex(q->state);
            }

            for (State<T>* currAdj : adjVec) {
                StateBehavior currBehavior = {};
                // initialize the struct of currBehavior
                currBehavior.state = currAdj;
                //g = q.g + successor.g
                //g = the sum of the weights up till now
                currBehavior.g = ((q->state->getVertexValue()) + (currAdj->getVertexValue()));
                //h = distance from goal to successor
                currBehavior.h = getDistanceBetweenStates(searchable->getGoalState(), currAdj);
                // successor.f = successor.g + successor.h
                currBehavior.f = currBehavior.g + currBehavior.h;

                // i) if successor is the goal, stop search
                if (searchable->isGoalState(currAdj)) {
                    //successor.g = q.g + distance between successor and q
                    currBehavior.g = (q->g) + getDistanceBetweenStates(currAdj, q->state);

                    // successor.h = distance from goal to successor
                    currBehavior.h = getDistanceBetweenStates(searchable->getGoalState(), currAdj);

                    // successor.f = successor.g + successor.h
                    currBehavior.f = currBehavior.g + currBehavior.h;

                    //stop search - return the pathTrace
                }

                //ii) if a node with the same position as successor is in the OPEN list
                // which has a lower f than successor, skip this successor
                auto i = openList.begin();
                for (; i != openList.end(); i++) {
                    StateBehavior*& checked = *i;
                    if (checked->state->isEqual(currAdj)) {
                        if (checked->f < currBehavior.f) {
                            //skip this successor
                            continue;
                        }
                    }
                }

                // iii) if a node with the same position as successor is in the CLOSED list which has
                // a lower f than successor, skip this successor.
                auto j = closedList.begin();
                for (; j != closedList.end(); j++) {
                    StateBehavior*& now = *j;
                    if (now->state->isEqual(currAdj)) {
                        if (now->f < currBehavior.f) {
                            //skip this successor
                            continue;
                        } else {
                            // otherwise, add the node to the open list.
                            openList.push_back(now);
                        }
                    }
                }
            } //end of for loop

            //e) push q on the closed list
            closedList.push_back(q);
        } //end of while loop
    }

    StateBehavior* theLeastFNode(list<StateBehavior*> openList) {
        StateBehavior* curr = openList.front();
        StateBehavior* minState = openList.front();
        double min = curr->f;
        auto i = openList.begin();
        for (; i != openList.end(); i++) {
            StateBehavior*& checked = *i;
            if(checked->f < min) {
                min = checked->f;
                minState = checked;
            }
        }
        return minState;
    }

    /*Manhattan Distance – It is nothing but the sum of absolute values of differences
     * in the goal’s x and y coordinates and the current cell’s x and y coordinates
     * Manhattan Distance is used because  we're allowed to move (right, left, top, bottom).
     */
    double getDistanceBetweenStates(State<T>* curr, State<T>* goal) {
        return (abs(curr->getX() - goal->getX()) + abs(curr->getY() - goal->getY()));
    }

};

#endif //EVEN2_ASTAR_H
