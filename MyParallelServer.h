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
#include <queue>
#include <mutex>
#include <ctime>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ioctl.h>

using namespace std;
extern queue<thread> threadsQueue;
extern bool doneAcceptingClient;
extern mutex fileMutex;
extern mutex mapMutex; //we need 2 mutexes- one for file handling, one for updating our map.

struct clHandlers {
    bool isThreadDone;
    int socketfd;
    ClientHandler* ch;
};

void openParallelServer(int port, ClientHandler* clientHandler);
void callClientHandler(clHandlers* handlers);
bool isClosed(int sock);

class MyParallelServer: public server_side::Server {
public:
    MyParallelServer() = default;
    void open(int port, ClientHandler* clientHandler) override;
    void stop() override;
};

#endif //EVEN2_MYPARALLELSERVER_H
