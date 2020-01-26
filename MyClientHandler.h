//
// Created by yael and linoy on 16/01/2020.
//

#ifndef EVEN2_MYCLIENTHANDLER_H
#define EVEN2_MYCLIENTHANDLER_H

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
#include "Matrix.h"
#include "Solver.h"
#include "FileCacheManager.h"
#include "ObjectAdapter.h"
#include "AStar.h"

class MyClientHandler: public ClientHandler {
private:
    Solver<string, string>* solver;
    CacheManager<string, string>* cacheManager;
public:
    void handleClient(int socket_fd) override ;
    MyClientHandler();
};


#endif //EVEN2_MYCLIENTHANDLER_H
