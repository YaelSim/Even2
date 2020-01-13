//
// Created by linoy on 12/01/2020.
//

#include "MyTestClientHandler.h"

bool isEndOfRead = false;

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
        vector<string> splitBufferVec = splitBuffer(totalBuffer, ',');
        // send to solver
    }
}

//This static method receives an array and divides its content into a new Vector<string> (and returns it accordingly).
vector<string> splitBuffer(char buffer[1024], char comma) {
    vector<string> vec;
    size_t start;
    string word;
    //Convert char[] buffer to string bufferAsString
    string bufferAsString;
    stringstream stringstream;
    stringstream << buffer;
    stringstream >> bufferAsString;
    size_t end = 0;
    //push the value that was found to the vector
    while ((start = bufferAsString.find_first_not_of(comma, end)) != std::string::npos) {
        end = bufferAsString.find(comma, start);
        word = bufferAsString.substr(start, end - start);
        if(word == "end") {
            isEndOfRead = true;
            continue;
        }
        vec.push_back(word);
    }
    return vec;
}