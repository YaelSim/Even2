//
// Created by linoy on 12/01/2020.
//

#ifndef EVEN2_STRINGREVERSER_H
#define EVEN2_STRINGREVERSER_H

#include "Solver.h"

class StringReverser: public Solver <string, string> {
public:
    StringReverser() = default;
    string solve(string problem) override;
};

#endif //EVEN2_STRINGREVERSER_H
