#include <unistd.h>
#include <cstdlib>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include "types.h"

using namespace std;

int main(){
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(9736);
    int len = sizeof(address);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int result = connect(sockfd, (struct sockaddr *)&address, (socklen_t)len);
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
        cout<<"Input action:[1: enter order], [4:cancel order] ,[6, order status], [8, quantity]"<<endl;
        cin>>action;
        switch (action){
        case 1:
        {
            cout<<"input[internal] market, desk, trader, sequence,price,quantity, like 1,2,3,4,5,6"<<endl;
            cin>>data;
            data = "1," + data;
        }
        break;
        case 4:
        {
            // cancel
            cout<<"input[internal] market, desk, trader, sequence like 1,2,3,4"<<endl;
            cin>>data;
            data = "4,"+data;

        }
        break;
        case 6:
        {
            // check order active
            cout<<"input[internal] market, desk, trader, sequence like 1,2,3,4"<<endl;
            cin>>data;
            data = "6,"+data;
        }
        break;
        case 8:
        {
            cout<<"input[internal] market, desk, trader, sequence like 1,2,3,4"<<endl;
            cin>>data;
            data = "8,"+data;
        }
        break;
        default:
            data.clear();
            break;
        }
        //TODO:
        // verify the data

        if (!data.empty()){
            write(sockfd, data.c_str(), data.size());
            cout<<"send:"<<data<<endl;
            data="";
            auto len = read(sockfd, recvbuf, 128);
            recvbuf[len]='\0';
            cout<<"result: "<< recvbuf<<endl;
            memset(recvbuf, 0, sizeof(recvbuf));
        }
        action = 0;
        cin.clear();
        cin.ignore();
    }
    close(sockfd);
    return 0;
}
