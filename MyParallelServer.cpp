//
// Created by linoy on 23/01/2020.
//

#include "MyParallelServer.h"

bool doneAcceptingClients = false;

void openParallelServer(int portToListen, ClientHandler* clientHandler) {

}

void MyParallelServer::open(int port, ClientHandler *clientHandler) {
    std::thread openServerThread(openParallelServer, port, clientHandler);
    openServerThread.detach();
    while (!doneAcceptingClients) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    if (doneAcceptingClients) {
        this->stop();
    }
}

void MyParallelServer::stop() {

}

