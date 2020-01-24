//
// Created by linoy on 23/01/2020.
//

#include "MyParallelServer.h"
#include "MyClientHandler.h"

bool doneAcceptingClient = false;
queue<thread> threadsQueue;

void openParallelServer(int port, ClientHandler* clientHandler) {
    bool isItFirstClient = true;
    int option = 1, clientSocket, addrlen, timeout_in_seconds = 120;
    struct sockaddr_in sockAddress;
    //Creation of socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        exit(-1);
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
    if (listen(socketfd, 1) < 0) {
        exit(-3);
    }
    addrlen = sizeof(sockAddress);

    while (!doneAcceptingClient) {
        if (isItFirstClient) {
            //Accepting a client.
            clientSocket = accept(socketfd, (struct sockaddr *) &sockAddress, (socklen_t*) &addrlen);
            if (clientSocket < 0) {
                doneAcceptingClient = false;
                continue;
            } else {
                cout << "accepted1!" << endl;
            }
            isItFirstClient = false;
        } else {
            //Defining a time out
            struct timeval tv;
            tv.tv_sec = timeout_in_seconds;
            setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char*) &tv, sizeof(tv));
            //Accepting a client.
            clientSocket = accept(socketfd, (struct sockaddr *) &sockAddress, (socklen_t*) &addrlen);
            if (clientSocket < 0) {
                //Did a timeout happen?
                if (errno == EWOULDBLOCK) {
                    cout << "timeout" << endl;
                    doneAcceptingClient = true;
                    continue;
                } else {
                    exit(-4);
                }
            } else {
                cout << "accepted2!" << endl;
            }
        }
        //initialize a new struct of handlers with the given arguments.
        clHandlers* handler = new clHandlers();
        handler->socketfd = clientSocket;
        //handler->ch = clientHandler;
        handler->ch = new MyClientHandler();
        handler->isThreadDone = false;


        std::thread chThread(callClientHandler, handler);

        //clientHandler->handleClient(clientSocket);
        close(clientSocket);
    }
    close(socketfd);
}

void callClientHandler(clHandlers* handler) {
    if (!isClosed(handler->socketfd)) {
        handler->ch->handleClient(handler->socketfd);
        close(handler->socketfd);
    }
}

//this static method receives a socketfd and returns true if the socket is closed.
bool isClosed(int sock) {
    fd_set rfd;
    FD_ZERO(&rfd);
    FD_SET(sock, &rfd);
    timeval tv = { 0 };
    select(sock + 1, &rfd, 0, 0, &tv);
    if (!FD_ISSET(sock, &rfd))
        return false;
    int n = 0;
    ioctl(sock, FIONREAD, &n);
    return n == 0;
}

void MyParallelServer::open(int port, ClientHandler *clientHandler) {
     /*//threadsQueue.push(std::thread(openParallelServer, port, clientHandler));
    std::thread psThread(openParallelServer, port, clientHandler);

    while (!threadsQueue.empty()) {
        threadsQueue.front().join();
        threadsQueue.pop();
    }

    while (!doneAcceptingClient) {
            //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    if (doneAcceptingClient) {
        this->stop();
    }*/


    bool isItFirstClient = true;
    int option = 1, clientSocket, addrlen, timeout_in_seconds = 120;
    struct sockaddr_in sockAddress;
    //Creation of socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        exit(-1);
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
    if (listen(socketfd, 1) < 0) {
        exit(-3);
    }
    addrlen = sizeof(sockAddress);

    while (!doneAcceptingClient) {
        if (isItFirstClient) {
            //Accepting a client.
            clientSocket = accept(socketfd, (struct sockaddr *) &sockAddress, (socklen_t*) &addrlen);
            if (clientSocket < 0) {
                doneAcceptingClient = false;
                continue;
            } else {
                cout << "accepted1!" << endl;
            }
            isItFirstClient = false;
        } else {
            //Defining a time out
            struct timeval tv;
            tv.tv_sec = timeout_in_seconds;
            setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char*) &tv, sizeof(tv));
            //Accepting a client.
            clientSocket = accept(socketfd, (struct sockaddr *) &sockAddress, (socklen_t*) &addrlen);
            if (clientSocket < 0) {
                //Did a timeout happen?
                if (errno == EWOULDBLOCK) {
                    cout << "timeout" << endl;
                    doneAcceptingClient = true;
                    continue;
                } else {
                    exit(-4);
                }
            } else {
                cout << "accepted2!" << endl;
            }
        }
        //initialize a new struct of handlers with the given arguments.
        clHandlers* handler = new clHandlers();
        handler->socketfd = clientSocket;
        //handler->ch = clientHandler;
        handler->ch = new MyClientHandler();
        handler->isThreadDone = false;

        std::thread chThread(callClientHandler, handler);
        chThread.detach();

        //clientHandler->handleClient(clientSocket);
        close(clientSocket);
    }
    close(socketfd);
}

void MyParallelServer::stop() {
    doneAcceptingClient = true;
}


