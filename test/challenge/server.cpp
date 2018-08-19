#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <thread>
#include <iostream>
#include <string>
#include "server.h"

void Server::HandleConnection(int client_sockfd){
    char buf[128];
    while(true){
        auto len = read(client_sockfd, buf, 128);
        if (len <=0 ){
            continue;
        }
        buf[len+1] = '\0';
        std::string ret = this->HandleMessage(buf);
        write(client_sockfd, ret.c_str(), ret.size());
        memset(buf,0,sizeof(buf));
    }
    close(client_sockfd);
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
    int opt = 1;
    setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt, sizeof(opt));
    bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_sockfd, 5);
    std::cout<<"router running..."<<std::endl;
    while (true)
    {
        client_len = sizeof(client_addr);
        client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &client_len);
        char IPdotdec[20];
        bzero(IPdotdec,sizeof(IPdotdec));
        inet_pton(AF_INET, IPdotdec, (void *)&(client_addr.sin_addr));
        std::cout<<"New connection from:"<<inet_ntoa(client_addr.sin_addr)<<std::endl;
        // client handler thread
        std::thread t(&Server::HandleConnection,this, client_sockfd);
        t.detach();
    }
    close(server_sockfd);
    std::cout<<"exit!"<<std::endl;
}
