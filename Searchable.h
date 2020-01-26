//
// Created by yael and linoy on 14/01/2020.
//

#ifndef EVEN2_SEARCHABLE_H
#define EVEN2_SEARCHABLE_H

#include <regex>
#include "State.h"

template <class T>
class Searchable {
public:
    virtual State<T>* getInitialState() = 0;
    virtual State<T>* getGoalState() = 0;
    virtual bool isGoalState(State<T>* state) = 0;
    virtual std::vector<State<T>*> getAllPossibleStates(State<T>* state) = 0;
private:

};

#endif //EVEN2_SEARCHABLE_H
