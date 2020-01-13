//
// Created by linoy on 12/01/2020.
//

#ifndef EVEN2_MYTESTCLIENTHANDLER_H
#define EVEN2_MYTESTCLIENTHANDLER_H

#include <thread>
#include <cstdio>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <mutex>
#include <unistd.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include <sys/socket.h>
#include <sstream>
#include <vector>
#include <iostream>
#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"

extern bool isEndOfRead;
vector<string> splitBuffer(char* buffer, char comma);

class MyTestClientHandler: public ClientHandler {
private:
    Solver* solver;
    CacheManager* cacheManager;
public:
    void handleClient(int socket_fd) override ;
};

#endif //EVEN2_MYTESTCLIENTHANDLER_H
