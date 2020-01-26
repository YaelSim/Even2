//
// Created by yael and linoy on 14/01/2020.
//

#ifndef EVEN2_MATRIX_H
#define EVEN2_MATRIX_H

#include "Searchable.h"
#include "State.h"
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

class Matrix: public Searchable<string> {
private:
    unordered_map<string, State<string>*> matrixMap;
    State<string>* startOfSearchState;
    State<string>* endOfSearchState;
    int numOfRows;
    int numOfCols;
    bool isItSearchCoordinate(string buffer);
    void setStartOfSearchState(State<string>* state);
    void setEndOfSearchState(State<string>* state);
public:
    Matrix(vector<string> matrixVec);
    State<string>* getInitialState() override ;
    bool isGoalState(State<string>* state) override;
    State<string>* getGoalState() override;
    std::vector<State<string>*> getAllPossibleStates(State<string>* state) override;
    unordered_map<string, State<string>*> buildMatrix(vector<string> matrixVec);

};

#endif //EVEN2_MATRIX_H
