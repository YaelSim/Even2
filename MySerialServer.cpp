//
// Created by linoy on 12/01/2020.
//

#include <condition_variable>
#include "MySerialServer.h"
bool doneAcceptingClients = false;

void MySerialServer::open(int port, ClientHandler *clientHandler) {
    std::thread openServerThread(openServer, port, clientHandler);
    openServerThread.detach();
    while (!doneAcceptingClients) { // check when convert to true***************
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    if (doneAcceptingClients) {
        this->stop();
    }
}

void MySerialServer::stop() {
    doneAcceptingClients = true;
}

void openServer(int port, ClientHandler* clientHandler) {
    int timeout_in_seconds = 120, option = 1;
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
    bzero((char *) &sockAddress, sizeof(sockAddress)); //Initialize
    sockAddress.sin_family = AF_INET;
    sockAddress.sin_addr.s_addr = INADDR_ANY;
    sockAddress.sin_port = htons(port);
    if (bind(socketfd, (struct sockaddr *) &sockAddress, sizeof(sockAddress)) < 0) {
        exit(-2);
    }

    while(!doneAcceptingClients) {
        //Listening for clients!
        if (listen(socketfd, 3) < 0) {
            exit(-3);
        }
        //Defining a time out
        struct timeval tv;
        tv.tv_sec = timeout_in_seconds;
        setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

        //Accepting a client.
        int clientSocket = accept(socketfd, (struct sockaddr *) &sockAddress, (socklen_t*) &sockAddress);
        if (clientSocket < 0) {
            //Did a timeout happen?
            if (errno == EWOULDBLOCK) {
                cout<<"timeout"<<endl;
                doneAcceptingClients = true;
                continue;
            } else {
                exit(-4);
            }
        }
        clientHandler->handleClient(socketfd);

        close(clientSocket);
    }

    close(socketfd);
    //this.stop(); when???***************

}

