//
// Created by linoy on 12/01/2020.
//

#include "MySerialServer.h"
bool isThreadDone = false;

void MySerialServer::open(int port, ClientHandler *clientHandler) {
    std::thread openServerThread(openServer, port);
    openServerThread.detach();
    while (!isThreadDone) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void MySerialServer::stop() {

}

void openServer(int port) {
    int timeout_in_seconds = 120, option = 1;
    //Creation of socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        exit(-1);
    }
    //Attaching socket
    if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option))) {
        exit(-8);
    }
    struct sockaddr_in sockAddress;
    sockAddress.sin_family = AF_INET;
    sockAddress.sin_addr.s_addr = INADDR_ANY;
    sockAddress.sin_port = htons(port);
    if (bind(socketfd, (struct sockaddr *) &sockAddress, sizeof(sockAddress)) < 0) {
        exit(-2);
    }
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
        exit(-4);
    }
    close(socketfd);

    /*
     * PROCCESS......
     IF MET "END" --> CALL STOP();
     *
     * isThreadDone = true;
    while (!isProgFinished) {
        index = 0;
        char buffer[1] = {0};
        char totalBuffer[1024] = {0};
        int val_read = read(clientSocket, buffer, 1);
        while (buffer[0] != '\n') {
            totalBuffer[index] = buffer[0];
            index++;
            val_read = read(clientSocket, buffer, 1);
        }
        vector<string> splitBufferVec = splitBuffer(totalBuffer, ',');
        updateValsOfBufferXmlMap(splitBufferVec);
    }*/
}

