//
// Created by linoy and yael on 23/01/2020.
//

#ifndef EVEN2_MYPARALLELSERVER_H
#define EVEN2_MYPARALLELSERVER_H

#include "MyClientHandler.h"
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
#include <ctime>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ioctl.h>

using namespace std;

//A struct that will order a client_socket and its proper clientHandler.
struct clHandlers {
    int socketfd;
    ClientHandler* ch;
};

extern bool doneAcceptingClient;

void callClientHandler(void* argument);
bool isClosed(int sock);

class MyParallelServer: public server_side::Server {
public:
    MyParallelServer() = default;
    void open(int port, ClientHandler* clientHandler) override;
    void stop() override;
};

#endif //EVEN2_MYPARALLELSERVER_H
