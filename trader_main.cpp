#include <unistd.h>
#include <cstdlib>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include "types.h"
#include "trader.h"

using namespace std;

int main(){
    int sockfd = -1;
    int len = 0;
    struct sockaddr_in address;
    int result;
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

    int action = 0;
    char recvbuf[128];
    std::string data;
    while (true)
    {
        cout<<"Input action 1: Enter Order,2:Cancell Order"<<endl;
        cin>>action;
        switch (action){
        case 1:
        {
            cout<<"input market, desk, trader, sequence,price,quantity, like 1,2,3,4,5,6"<<endl;
            cin>>data;
            data = "1," + data;
            write(sockfd, data.c_str(), data.size());
            cout<<"send:"<<data<<endl;
            data="";
            char buf[128];
            auto len = read(sockfd, buf, 128);
            buf[len]='\0';
            cout<<"status:"<< buf<<endl;
        }
        break;
        case 2:
            break;
        default:
            break;
        }
    }
    close(sockfd);
    return 0;
}
