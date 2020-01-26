//
// Created by linoy and yael on 12/01/2020.
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
#include "StringReverser.h"
#include "FileCacheManager.h"

extern bool isEndOfRead;

class MyTestClientHandler: public ClientHandler {
private:
    Solver<string, string>* solver;
    CacheManager<string, string>* cacheManager;
    bool isItSearchCoordinate(char* buffer);
public:
    void handleClient(int socket_fd) override ;
    MyTestClientHandler();
};

#endif //EVEN2_MYTESTCLIENTHANDLER_H
