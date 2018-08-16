#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <thread>
#include "message.hpp"
#include "server.h"


const int MAX_LINE = 200;
const int PORT = 6060;
const int LISTENQ = 6666;
const int MAX_CONNECT = 20;

void Server::run()
{
    struct sockaddr_in serAddr, cliAddr;
    int listenFd, connFd;
    pid_t childPid;
    socklen_t client;

    listenFd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenFd < 0){
        perror("socket error");
        exit(1);

    }
    bzero(&serAddr, sizeof(serAddr));
    serAddr.sin_family = AF_INET;
    serAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serAddr.sin_port = htons(PORT);
    if(bind(listenFd, (struct sockaddr*)&serAddr, sizeof(serAddr)) < 0) {
        perror("bind error");
        exit(1);
    };
    if(listen(listenFd, LISTENQ) < 0) {
        perror("listen error");
        exit(1);
    };

    while(true) {
        client = sizeof(cliAddr);
        connFd = accept(listenFd, (struct sockaddr*)&cliAddr, &client);
        if(connFd < 0) {
            perror("accept error");
            exit(1);
        }

        std::thread msghandler([&](){
                char buf[MAX_LINE+1];
                memset(buf, 0 ,sizeof(buf)+1);
                while(read(connFd, buf, MAX_LINE) > 0) {
                    printf("data is %s", buf);
                    this->HandleMessage(buf);
                    memset(buf, 0 ,sizeof(buf)+1);
                }
            });
    }
    close(listenFd);
}
