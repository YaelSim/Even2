//
// Created by linoy on 12/01/2020.
//

#ifndef EVEN2_MAIN_H
#define EVEN2_MAIN_H

#include "FileCacheManager.h"
#include "MySerialServer.h"

namespace boot {
    class Main {
    public:
        int main(int port) {
            Solver* solver = new StringReverser();
            CacheManager* cacheManager = new FileCacheManager();
            server_side::Server* server = new MySerialServer;
        }
    };
}

#endif //EVEN2_MAIN_H
