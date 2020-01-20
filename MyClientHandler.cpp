//
// Created by yael and linoy on 16/01/2020.
//


#include "MyClientHandler.h"
#include "Searchable.h"

MyClientHandler::MyClientHandler() {
    this->cacheManager = new FileCacheManager();
}

void MyClientHandler::handleClient(int socket_fd) {
    int index, startFlag = 0;
    //CacheManager<string,string>* fileCacheManager = this->cacheManager;
    vector<string> matrixVec;
    //reading from client as long as the parser function didn't end its' work
    while (!isEndOfRead) {
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
        for (int i = 0; i < 1024; i++) {
            if (totalBuffer[i] != '\000') {
                bufferAsString += totalBuffer[i];
            }
        }
        if (bufferAsString.find("end") != std::string::npos) {
            isEndOfRead = true;
            continue;
        } else {
            matrixVec.push_back(bufferAsString);
        }
    }
    if (isEndOfRead) {
        //Solve!!!!!
        Searchable<string>* matrix = new Matrix(matrixVec);
        // convert the vector to a problem string to find in the CacheManager
        auto i = matrixVec.begin();
        string problem, solution;
        while(i != matrixVec.end()) {
            // CHECK IF NEED TO REMOVE THE START AND END INDEX FROM THIS STRING**********
            problem += *i;
            i++;
        }
        //CHECK WHERE WE NEED TO PUT MUTEX
        bool isExist = this->cacheManager->doesASolutionExist(problem);
        if(isExist) {
            solution = this->cacheManager->getSolution(problem);
        } else {
            solution = this->solver->solve(matrixVec);
            this->cacheManager->saveSolution(problem, solution);
        }
        //BEFORE SENDING THE SOLUTION TO THE CLIENT, DONT FORGET TO ADD \r\n
    }
    //**************************** check if needed with matrix*******************
    isEndOfRead = false;
}