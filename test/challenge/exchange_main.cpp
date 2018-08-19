#include <unistd.h>
#include <cstdlib>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include "types.h"

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
        // order confirmed
        cout<<"Input action: [2:Order confirmed], [3: Order traded] ,[5:Order cancelled], [7:Order status]"<<endl;
        cin>>action;
        switch (action){
        case 2:
        {
            cout<<"input [internal,external]: market, desk, trader, sequence,eg: 1,2,3,4,external"<<endl;
            cin>>data;
            data = "2," + data;
        }
        break;
        case 3:
        {// Order Traded
            cout<<"input [external]:external,quantity eg: abc,12"<<endl;
            cin>>data;
            data = "3," + data;
        }
        break;
        case 5:
        {
            // order cancelled
            cout<<"input [external]:external eg: abc"<<endl;
            cin>>data;
            data = "5," + data;
        }
        break;
        case 7:
        {
            cout<<"input [external]:external eg: abc"<<endl;
            cin>>data;
            data = "7," + data;
        }
        break;
        default:
            cout<<"Please input correct action"<<endl;
            data.clear();
            break;
        }// end switch

        if (!data.empty()){
            write(sockfd, data.c_str(), data.size());
            cout<<"send:"<<data<<endl;
            data.clear();
            auto len = read(sockfd, recvbuf, 128);
            recvbuf[len]='\0';
            cout<<"result:"<< recvbuf<<endl;
            memset(recvbuf, 0, sizeof(recvbuf));
        }
        /// reset
        action = 0;
        cin.clear();
        cin.ignore();
    }
    close(sockfd);
    return 0;
}
