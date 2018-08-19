#include <iostream>
#include <unistd.h>
#include <thread>
#include <cstdlib>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <sstream>
#include <list>
//#include "../ordermanager.h"
#include "../orderrouter.h"

using namespace std;
void test_trade_order(int trader_id){
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

    char recvbuf[128];
    std::string data;
    uint16_t desk = trader_id+1;
    uint16_t market = trader_id+2;
    stringstream strm;
    // trade Order
    strm<<"3,"<<market<<"_"<<desk<<"_"<<trader_id<<"_";
    string tradeorer = strm.str();
    strm.str("");
    // TODO:
    // check the status and quantity about the traded orders
    auto counter = 10;
    for(auto i=0; i<counter; i++){
        //sequence
        strm<<i;
        // 100 is quantity
        auto data = tradeorer+strm.str()+",100";
        write(sockfd, data.c_str(), data.size());
        cout<<"send:"<<data<<endl;
        auto len = read(sockfd, recvbuf, 128);
        recvbuf[len]='\0';
        // TODO:
        // check the result
        // ASSERT_EQUAL
        cout<<"result: "<< recvbuf<<endl;
        strm.str("");
        memset(recvbuf, 0, sizeof(recvbuf));
    }
    close(sockfd);
}

void test_enter_order(int trader_id){
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

    char recvbuf[128];
    std::string data;
    uint16_t desk = trader_id+1;
    uint16_t market = trader_id+2;
    stringstream strm;
    // Enter Order
    strm<<"1,"<<market<<","<<desk<<","<<trader_id<<",";
    string enterorder = strm.str();
    strm.str("");
    // strm<<"4,"<<market<<","<<desk<<","<<trader_id<<",";
    cout<<"trade thread..."<<trader_id<< endl;
    // query status
    uint32_t price = 100;
    uint32_t quantity = 100;
    strm<<"2,"<<market<<","<<desk<<","<<trader_id<<",";
    std::string orderconfirm=strm.str();
    strm.str("");
    strm<<market<<"_"<<desk<<"_"<<trader_id<<"_";
    std::string external = strm.str();
    strm.str("");
    int number = 10;
    while(true){
        // generator create order; 10
        // action enter order
        for (auto i=0; i<number; i++){
            strm<<i<<","<<price<<","<<quantity;
            std::string data = enterorder+strm.str(); 
            write(sockfd, data.c_str(), data.size());
            cout<<"send:"<<data<<endl;
            auto len = read(sockfd, recvbuf, 128);
            recvbuf[len]='\0';

            // TODO:
            // check the result
            // ASSERT_EQUAL
            cout<<"result: "<< recvbuf<<endl;
            strm.str("");
            memset(recvbuf, 0, sizeof(recvbuf));
            sleep(1);
        }
        // order confirm
        for (auto i=0; i<number; i++){
            strm<<i;
            auto tmpexternal = external+strm.str();
            auto data = orderconfirm + strm.str()+","+tmpexternal;
            write(sockfd, data.c_str(), data.size());
            cout<<"send:"<<data<<endl;
            auto len = read(sockfd, recvbuf, 128);
            recvbuf[len]='\0';

            // TODO:
            // check the result
            // ASSERT_EQUAL
            cout<<"result: "<< recvbuf<<endl;
            strm.str("");
            memset(recvbuf, 0, sizeof(recvbuf));
            sleep(1);
        }
        break;
    }
    close(sockfd);
}

// tets the function one by one
void test_functional(){
    auto odrmgr = new OrderManager();
    // TODO:
    // check result
    OrderIdentifier oi{1,2,3,4};
    odrmgr->OnTraderEnter(oi, 100, 100);
    std::string aExternal ="external1";
    odrmgr->OnExchangeNew(oi, aExternal);
    odrmgr->IsOrderActive(aExternal);
    // TODO:
    // ... all of the function
    delete odrmgr;
}

int main(){

    // start the router server
    auto routerid = fork();
    if (routerid == 0){
        auto router = new OrderRouter();
        router->run();
    }
    cout<<"router pID"<<routerid<<endl;
    // test enter order
    //if (fork()==0){
    // init the orders data;
    //wait the router process start
    sleep(1);
    std::list<std::thread*> threads;
    for(auto i = 0 ; i< 4; i++){
        auto t= new std::thread(test_enter_order, i);
        threads.push_back(t);
    }
    for (auto t: threads){
        t->join();
    }
    //
    test_functional();
    //}
    // test trade orer
    if (fork()==0){
        std::list<std::thread*> threads;
        for(auto i = 0 ; i< 1; i++){
            auto t= new std::thread(test_trade_order, i);
            threads.push_back(t);
        }

        for (auto t: threads){
            t->join();
        }
    }
    int rnt=0;
    wait(&rnt);
    cout<<"terminal:"<<rnt<<endl;
    // while(true){
    //     sleep(1);
    // }
}
