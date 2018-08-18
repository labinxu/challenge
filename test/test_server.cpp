#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <thread>

int main(int argc, char **argv)
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
        char ch = '\0';
        client_len = sizeof(client_addr);
        printf("Server waiting\n");
        client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &client_len);
        auto threadfn=[&](int client_sockfd){
            char buf[1024];
            while(true){
                read(client_sockfd, buf, 1024);

                write(client_sockfd, buf, 1024);
            }
        };
        std::thread t(threadfn, client_sockfd);
        t.detach();
        // if (fork() == 0)
        // {
        //     char buf[1024];
        //     while(true){
        //         read(client_sockfd, buf, 1024);
        //         write(client_sockfd, buf, 1024);
        //     }
        // }
        // else
        // {
        //     close(client_sockfd);
        // }
    }
}
