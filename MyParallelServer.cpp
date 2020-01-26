//
// Created by linoy and yael on 23/01/2020.
//

#include "MyParallelServer.h"

bool doneAcceptingClient = false;

//This static method receives a struct and handles the client (in a different thread).
//This method is called when a different thread is created.
void callClientHandler(void* argument) {
    auto *handler = (clHandlers*) argument;
    handler->ch->handleClient(handler->socketfd);
    close(handler->socketfd);
    delete handler;
}

//this static method receives a socketfd and returns true if the socket is closed.
bool isClosed(int sock) {
    fd_set rfd;
    FD_ZERO(&rfd);
    FD_SET(sock, &rfd);
    timeval tv = { 0 };
    select(sock + 1, &rfd, 0, 0, &tv);
    if (!FD_ISSET(sock, &rfd)) {
        return false;
    }
    int n = 0;
    ioctl(sock, FIONREAD, &n);
    return n == 0;
}

//This is the main method of MyParallelServer. we're given a port and a clientHandler and we create a socket (using the
//given port) listen to possible clients. Each client accepted is handled (using clientHandler) in a different thread.
void MyParallelServer::open(int port, ClientHandler *clientHandler) {
    int option = 1, clientSocket, addrlen, timeout_in_seconds = 120;
    struct sockaddr_in sockAddress;
    //Creation of socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        exit(-1);
    }
    //Attaching socket
    if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option))) {
        exit(-8);
    }

    sockAddress.sin_family = AF_INET;
    sockAddress.sin_addr.s_addr = INADDR_ANY;
    sockAddress.sin_port = htons(port);
    if (bind(socketfd, (struct sockaddr *) &sockAddress, sizeof(sockAddress)) < 0) {
        exit(-2);
    }

    /* Important: when a new client is received, we will add a new thread for it and will add the thread
     * to our _threadsQueue. We will handle those clients one by one, but we can accept more clients while
     * we are still handling the previous client.
     */
    if (listen(socketfd, 10) < 0) {
        exit(-3);
    }
    addrlen = sizeof(sockAddress);

    while (!doneAcceptingClient) {
        //Defining a time out
        struct timeval tv;
        tv.tv_sec = timeout_in_seconds;
        tv.tv_usec = 0;
        setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof(tv));

        //Accepting a client.
        clientSocket = accept(socketfd, (struct sockaddr *) &sockAddress, (socklen_t *) &addrlen);
        if (clientSocket < 0) {
            //Did a timeout happen?
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                cout << "timeout!" << endl;
                doneAcceptingClient = true;
                continue;
            } else {
                exit(-4);
            }
        }
        //initialize a new struct of handlers with the given arguments.
        auto *handler = new clHandlers();
        handler->socketfd = clientSocket;
        handler->ch = new MyClientHandler();

        std::thread chThread(callClientHandler, handler);
        chThread.detach();
    }
    if (doneAcceptingClient) {
        this->stop();
    }
    close(socketfd);
}

//This method prevents the MyParallelServer from running.
void MyParallelServer::stop() {
    doneAcceptingClient = true;
}