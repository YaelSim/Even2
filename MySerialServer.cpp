//
// Created by linoy and yael on 12/01/2020.
//

#include "MySerialServer.h"

bool doneAcceptingClients = false;

//This is the main method of MySerialServer. It receives a port to listen to and clientHandler that will manage
//the communication (sending the solution / getting another problem) with the client.
void MySerialServer::open(int port, ClientHandler *clientHandler) {
    std::thread openServerThread(openServer, port, clientHandler);
    openServerThread.detach();
    while (!doneAcceptingClients) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    if (doneAcceptingClients) {
        this->stop();
    }
}

//This method prevents MySerialServer from running.
void MySerialServer::stop() {
    doneAcceptingClients = true;
}

//This static method is called every time a new thread is created
void openServer(int port, ClientHandler* clientHandler) {
    int timeout_in_seconds = 120, option = 1, clientSocket, addrlen;
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

    //Listening for clients!
    if (listen(socketfd, 1) < 0) {
        exit(-3);
    }
    addrlen = sizeof(sockAddress);

    while(!doneAcceptingClients) {
        //Defining a time out
        struct timeval tv;
        tv.tv_sec = timeout_in_seconds;
        tv.tv_usec = 0;
        setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char*) &tv, sizeof(tv));

        //Accepting a client.
        clientSocket = accept(socketfd, (struct sockaddr *) &sockAddress, (socklen_t*) &addrlen);
        if (clientSocket < 0) {
            //Did a timeout happen? If so, stop the server from running.
            if (errno == EWOULDBLOCK) {
                cout << "timeout" << endl;
                doneAcceptingClients = true;
                continue;
            } else {
                exit(-4);
            }
        }
        clientHandler->handleClient(clientSocket);
        close(clientSocket);
    }
    close(socketfd);
}