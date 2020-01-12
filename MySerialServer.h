//
// Created by linoy on 12/01/2020.
//

#ifndef EVEN2_MYSERIALSERVER_H
#define EVEN2_MYSERIALSERVER_H

#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <mutex>
#include <unistd.h>
#include "Server.h"

extern bool isThreadDone;

void openServer(int portToListen);

class MySerialServer: public server_side::Server {

    //Think if more methods/functions are needed. *************
public:
    MySerialServer() = default;
    void open(int port, ClientHandler* clientHandler) override;
    void stop() override;
};

#endif //EVEN2_MYSERIALSERVER_H
