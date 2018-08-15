#include <iostream>
#include <thread>
#include <vector>
#include "trader.h"
#include "ordermanager.h"

using namespace std;
void StartOrderMgr(){

}

int main(){
    // start trader thread
    // start exchange thread
    // start order manager
    Trader trader;
    int action{0};
    uint32_t price{0};
    uint32_t quanlity{0};
    uint16_t market{0};
    uint16_t desk{0};
    while(true)
    {
        cout<<"Action: 1:EnterOrder,2:CancleOrder"<<endl;
        cin>>action;
        switch(action){
        case 1:
        {
            cout<<"Please type the market, desk, price & quanlity"<<endl;
            cin>>market>>desk>>price>>quanlity;
            cout<<" market:"<<market<<" desk:"<<desk<<"Price:"<<price<<",Quanlity:"<<quanlity<<endl;

            if (trader.EnterOrder(market, desk, price, quanlity))
            {
                cout<<"Successfully."<<endl;
            }
            else
            {
                cout<<"Failed."<<endl;
            }
        };
        break;
        case 2:
        {
            
        };
        break;
        default:
            break;
        }
    }
    
}
