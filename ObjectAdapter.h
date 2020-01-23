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
    Searcher<Problem>* searcher; //algorithm
public:
    ObjectAdapter() = default;

    void setSearcher(Searcher<Problem>* alg) {
        this->searcher = alg;

    }

    string getNameOfCurrAlg() override {
        return this->searcher->getNameOfSearcher();
    }

    Solution solve(Problem problem) override {
        //Convert the dilimProblem (string with ';') to a vector
        vector<string> matrixVec;
        stringstream ss(problem);
        string token;
        //Tokenize the problem according to ';'
        //Inspiration - https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
        while (getline(ss, token, ';')) {
            matrixVec.push_back(token);
        }

        //Convert the matrixVec to a new Searchable type (matrix).
        Searchable<string>* matrix = new Matrix(matrixVec);
        vector<State<Problem>*> solutionVec = this->searcher->search(matrix);

        //Convert the solution to an output that will be sent to the client.
        string output = this->getSolutionString(solutionVec);
        return output;
    }

    /*
     * This method gets the solution vector from the search algorithm, and converts its' states accordingly
     * to strings - UP,DOWN,LEFT,RIGHT. This solution string will be later on sent to the client.
     */
    string getSolutionString(vector<State<Problem>*> solutionVec) {
        string output;
        int currCost = 0;
        for(int i = 0; (i < (solutionVec.size() - 1)); i++) {
            State<Problem>* currState = solutionVec.at(i);
            currCost += currState->getVertexValue();
            State<Problem>* nextState = solutionVec.at(i + 1);
            currCost += nextState->getVertexValue();
            //Add '{' first
            if (i == 0) {
                output += "{";
            }
            //Is curr.x - next.x == 0? If so, we took the current step on the Y coordinate (RIGHT/LEFT).
            if (currState->getX() - nextState->getX() == 0) {
                //If so, we took a step LEFT
                if (currState->getY() - nextState->getY() == 1) {
                    output += "Left";
                } //If so, we took a step RIGHT
                else if (currState->getY() - nextState->getY() == (-1)) {
                    output += "Right";
                }
            } //Is curr.y - next.y == 0? If so, we took the current step on the X coordinate (UP/DOWN).
            else if (currState->getY() - nextState->getY() == 0) {
                //If so, we took a step UP
                if (currState->getX() - nextState->getX() == 1) {
                    output += "Up";
                } //If so, we took a step DOWN
                else if (currState->getX() - nextState->getX() == (-1)) {
                    output += "Down";
                }
            }
            if (i != (solutionVec.size() - 2)) {
                output += "(";
                output += to_string(currCost);
                output += "), ";
            } else {
                output += "(";
                output += to_string(currCost);
                output += "}\r\n";
            }
        }
        return output;
    }
};

#endif //EVEN2_OBJECTADAPTER_H
