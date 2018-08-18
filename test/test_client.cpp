#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
using namespace std;
int main(int argc, char **argv)
{
    int sockfd = -1;
    int len = 0;
    struct sockaddr_in address;
    int result;
    char ch = 'A';
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(9736);
    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr *)&address, (socklen_t)len);
    if (result == -1)
    {
        perror("ops: client\n");
        exit(1);
    }
    while(1){
        std::string data;
        std::cin>>data;
        write(sockfd, data.c_str(), data.size());
        char buf[1024];
        auto len = read(sockfd, buf, 1024);
        buf[len+1]='\0';
        cout<<"char from server = "<< buf<<endl;
    }
    close(sockfd);
    exit(0);
}
