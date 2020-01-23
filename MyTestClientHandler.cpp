//
// Created by linoy on 12/01/2020.
//

#include "MyTestClientHandler.h"

bool isEndOfRead = false;
std::mutex progMutex;

MyTestClientHandler::MyTestClientHandler() {
    this->cacheManager = new FileCacheManager();
    this->solver = new StringReverser();
}

void MyTestClientHandler::handleClient(int socket_fd) {
    int index;
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
        string problem, solution;
        for (int i = 0; i < 1024; i++) {
            if (totalBuffer[i] != '\000') {
                problem += totalBuffer[i];
            }
        }
        if (problem.find("end") != std::string::npos) {
            isEndOfRead = true;
            continue;
        } else {
            //CHECK WHERE WE NEED TO PUT MUTEX
            this->cacheManager->setAlg(this->solver->getNameOfCurrAlg());
            bool isExist = this->cacheManager->doesASolutionExist(problem);
            if(isExist) {
                solution = this->cacheManager->getSolution(problem);
            } else {
                solution = this->solver->solve(problem);
                this->cacheManager->saveSolution(problem, solution);
            }
            solution += "\r\n";
            const char* solutionToClient = solution.c_str();
            int is_sent = send(socket_fd, solutionToClient, strlen(solutionToClient), 0);
            if (is_sent < 0) {
                cout<<"Failed Sending Solution To Client!"<<endl;
            }
            //Check what is the issue with the broken pipe.*******************************
        }
    }
    isEndOfRead = false;
}
