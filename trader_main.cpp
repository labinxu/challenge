#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <string>
#include <iostream>
#include "types.h"
#include "trader.h"
using namespace std;
const int MYPORT = 7000;
const int BUFFER_SIZE = 1024;

int main()
{
    int sock_cli = socket(AF_INET,SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect failed");
        exit(1);
    }

    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];
    //uint32_t market, desk, sequence, trader,quantity, price;
    int action = 0;
    std::string data;
    while (true)
    {
        cout<<"Input action 1: Enter Order,2:Cancell Order"<<endl;
        cin>>action;
        switch (action){
        case 1:
        {
            cout<<"input trader,market, desk, sequence,price,quantity, like 1,2,3,4"<<endl;
            cin>>data;
            //sscanf(data.c_str(),"%d,%d,%d,%d",&trader,&market,&desk,&sequence, &price, &quantity);
            //OrderIdentifier oi{market, desk, trader, sequence};
            // encode action
            //memcpy(sendbuf, (char*)&action, sizeof(int));
            // encode oi
            //memcpy(sendbuf+sizeof(int),(char*)&oi, sizeof(OrderIdentifier));
            send(sock_cli, data.c_str(), data.size(), 0);
            cout<<"send:"<<data<<endl;
            data="";
        }
        break;
        case 2:
            break;
        default:
            break;
        }

        if(strcmp(sendbuf,"exit\n")==0)
            break;
        recv(sock_cli, recvbuf, sizeof(recvbuf),0);
        cout<<recvbuf<<endl;
        memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));

    }

    close(sock_cli);
    return 0;
}
