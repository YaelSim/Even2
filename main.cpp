#include "StringReverser.h"
#include "Main.h"
#include "Matrix.h"
#include <vector>
#include "BFS.h"
#include "DFS.h"
#include "BestFirstSearch.h"
#include "AStar.h"

int main(int argc, char** argv) {
    vector<string> vec;
    vec.push_back("1,2,3,4,5");
    vec.push_back("6,7,-1,9,10");
    vec.push_back("9,10,13,-1,15");
    vec.push_back("2,12,4,14,7");
    vec.push_back("0,0");
    vec.push_back("2,2");
    Matrix* mat = new Matrix(vec);
    Searcher<string>* s = new BFS<string>();
    s = new BestFirstSearch<string>();
    //s = new AStar<string>();
    s->search(mat);
    int portAsInt = stoi(argv[1]);
    boot::Main().main(portAsInt);
    return 0;
}