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
#include "message.hpp"

const int MAX_LINE = 200;
const int PORT = 6060;
const int LISTENQ = 6666;
const int MAX_CONNECT = 20;

int main() {
    struct sockaddr_in serAddr, cliAddr;
    int listenFd, connFd;
    pid_t childPid;
    char buf[MAX_LINE];
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
        printf("data");
    while(true) {
        client = sizeof(cliAddr);
        connFd = accept(listenFd, (struct sockaddr*)&cliAddr, &client);
        if(connFd < 0) {
            perror("accept error");
            exit(1);
        }
        childPid =fork();
        if(childPid == 0) {
            close(listenFd);
            char buf[message::header_length];
            while(read(connFd, buf, message::header_length) > 0) {
                int len = 
                char data[];
                read(connFd, data, )
                printf("data is %s", buf);
                memset(buf, 0 ,sizeof(buf));

            };
        }
    }
    close(listenFd);
    return 0;
}
