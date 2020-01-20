//
// Created by linoy on 12/01/2020.
//

#ifndef EVEN2_CLIENTHANDLER_H
#define EVEN2_CLIENTHANDLER_H

#include <regex>
#include <mutex>

extern std::mutex progMutex;

class ClientHandler {
public:
    virtual void handleClient(int sock_fd) = 0;
};

#endif //EVEN2_CLIENTHANDLER_H
