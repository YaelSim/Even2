//
// Created by linoy on 23/01/2020.
//

#ifndef EVEN2_MYPARALLELSERVER_H
#define EVEN2_MYPARALLELSERVER_H

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
#include "Server.h"
#include <iostream>

extern bool isThreadDone;
extern bool doneAcceptingClients;
using namespace std;

void openParallelServer(int portToListen, ClientHandler* clientHandler);

class MyParallelServer: public server_side::Server {
    public:
        MyParallelServer() = default;
        void open(int port, ClientHandler* clientHandler) override;
        void stop() override;
};

#endif //EVEN2_MYPARALLELSERVER_H
