#include "StringReverser.h"
#include "Main.h"
#include "Matrix.h"
#include <vector>
#include "BFS.h"
#include "DFS.h"
#include "BestFirstSearch.h"
#include "AStar.h"
#include "ObjectAdapter.h"

int main(int argc, char** argv) {
    /*vector<string> vec;
    vec.push_back("1,2,3,4,5");
    vec.push_back("6,7,-1,9,10");
    vec.push_back("9,10,13,-1,15");
    vec.push_back("2,12,4,14,7");
    vec.push_back("0,0");
    vec.push_back("2,2");
    //Searchable<string>* mat = new Matrix(vec);
    //s = new BestFirstSearch<string>();
    //s = new AStar<string>();
    //s->search(mat);

    auto i = vec.begin();
    string dilimProblem;
    while(i != vec.end()) {
        dilimProblem += *i;
        dilimProblem += ";";
        i++;
    }

    Searcher<string>* s = new AStar<string>();
    ObjectAdapter<string, string>* oa = new ObjectAdapter<string, string>();
    oa->setSearcher(s);
    string solution = oa->solve(dilimProblem);*/


    int portAsInt = stoi(argv[1]);
    boot::Main().main(portAsInt);
    return 0;
}