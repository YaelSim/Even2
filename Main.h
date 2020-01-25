//
// Created by linoy on 12/01/2020.
//

#ifndef EVEN2_MAIN_H
#define EVEN2_MAIN_H

#include "MyParallelServer.h"
#include "MyClientHandler.h"
#include "MySerialServer.h"

namespace boot {
    class Main {
    public:
        int main(int port) {
            ClientHandler* clientHandler = new MyClientHandler;
            server_side::Server* server = new MyParallelServer;
            //server_side::Server* server = new MySerialServer;
            server->open(port, clientHandler);
            return 0;
        }
    };
}

#endif //EVEN2_MAIN_H
