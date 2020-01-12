//
// Created by linoy on 12/01/2020.
//

#ifndef EVEN2_MYTESTCLIENTHANDLER_H
#define EVEN2_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"

class MyTestClientHandler: public ClientHandler {
private:
    Solver* solver;
    CacheManager* cacheManager;
public:
    void handleClient(int socket_fd) override ;
};

#endif //EVEN2_MYTESTCLIENTHANDLER_H
