#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <thread>
#include <iostream>
#include <string>
#include "server.h"


void Server::HandleConnection(int client_sockfd){
    std::cout<<"HandleConnection"<<std::endl;
    char buf[1024];
    while(true){
        auto len = read(client_sockfd, buf, 1024);
        buf[len+1] = '\0';
        std::string ret = this->HandleMessage(buf);
        //std::cout<<"response:"<<ret<<std::endl;
        write(client_sockfd, ret.c_str(), ret.size());
    }
}

void Server::run()
{
    int server_sockfd = -1;
    int client_sockfd = -1;
    socklen_t client_len = 0;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(9736);
    bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_sockfd, 5);
    signal(SIGCHLD, SIG_IGN);
    while (1)
    {
        client_len = sizeof(client_addr);
        printf("Server waiting\n");
        client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &client_len);
        std::thread t(&Server::HandleConnection,this, client_sockfd);
        t.detach();
    }
}
