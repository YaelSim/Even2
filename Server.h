//
// Created by linoy on 12/01/2020.
//

#ifndef EVEN2_SERVER_H
#define EVEN2_SERVER_H

#include <pthread.h>
#include "ClientHandler.h"

namespace server_side {

    class Server {
    public:
        virtual void open(int port, ClientHandler* client_handler) = 0;
        virtual void stop() = 0;
    };
}

#endif //EVEN2_SERVER_H
