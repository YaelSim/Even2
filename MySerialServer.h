//
// Created by linoy and yael on 12/01/2020.
//

#ifndef EVEN2_MYSERIALSERVER_H
#define EVEN2_MYSERIALSERVER_H

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

extern bool doneAcceptingClients;
using namespace std;

void openServer(int portToListen, ClientHandler* clientHandler);

class MySerialServer: public server_side::Server {
public:
    MySerialServer() = default;
    void open(int port, ClientHandler* clientHandler) override;
    void stop() override;
};

#endif //EVEN2_MYSERIALSERVER_H
