//
// Created by yael and linoy on 16/01/2020.
//


#include "MyClientHandler.h"

MyClientHandler::MyClientHandler() {
    this->cacheManager = new FileCacheManager();
    this->solver = new ObjectAdapter<string, string>();
    //Searcher<string>* s = new AStar<string>();
    Searcher<string>* s = new BestFirstSearch<string>();
    //Searcher<string>* s = new BFS<string>();
    this->solver->setSearcher(s);
}

void MyClientHandler::handleClient(int socket_fd) {
    int index;
    vector<string> matrixVec;
    //reading from client as long as the parser function didn't end its' work
    while (true) {
        index = 0;
        char buffer[1] = {0};
        char totalBuffer[1024] = {0};
        int val_read = read(socket_fd, buffer, 1);
        while (buffer[0] != '\n') {
            totalBuffer[index] = buffer[0];
            index++;
            val_read = read(socket_fd, buffer, 1);
        }
        //check if the total line (receieved from totalBuffer) contains "end"
        string bufferAsString;
        for(int i = 0; i < 1024; i++) {
            if (totalBuffer[i] != '\000') {
                bufferAsString += totalBuffer[i];
            }
        }
        if (bufferAsString != "end") {
            matrixVec.push_back(bufferAsString);
        } else {
            // convert the vector to a problem string to find in the CacheManager
            auto i = matrixVec.begin();
            string problem, solution;
            while(i != matrixVec.end()) {
                problem += *i;
                i++;
            }
            //Update the name of this current search algorithm
            this->cacheManager->setAlg(this->solver->getNameOfCurrAlg());
            bool isExist = this->cacheManager->doesASolutionExist(problem);
            if(isExist) {
                solution = this->cacheManager->getSolution(problem);
            } else {
                i = matrixVec.begin();
                string dilimProblem;
                while(i != matrixVec.end()) {
                    dilimProblem += *i;
                    dilimProblem += ";";
                    i++;
                }
                solution = this->solver->solve(dilimProblem);
                this->cacheManager->saveSolution(problem, solution);
            }
            solution += "\r\n";
            const char* solutionToClient = solution.c_str();
            int is_sent = send(socket_fd, solutionToClient, strlen(solutionToClient), 0);
            if (is_sent < 0) {
                cout<<"Failed Sending Solution To Client!"<<endl;
            }
            break;
        }
    }

}