//
// Created by linoy on 12/01/2020.
//

#ifndef EVEN2_MAIN_H
#define EVEN2_MAIN_H

#include "FileCacheManager.h"
#include "MySerialServer.h"
#include "MyTestClientHandler.h"

namespace boot {
    class Main {
    public:
        int main(int port) {
            ClientHandler* clientHandler = new MyTestClientHandler;
            server_side::Server* server = new MySerialServer;
            server->open(port, clientHandler);
            return 0;
        }
    };
}

#endif //EVEN2_MAIN_H
