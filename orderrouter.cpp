#include <iostream>
#include <cstdio>
#include "orderrouter.h"
using namespace std;
bool OrderRouter::OnTraderEnter(const OrderIdentifier& aInternal,
                                uint32_t aPrice,uint32_t aQuantity){
    return _orderManager->OnTraderEnter(aInternal, aPrice, aQuantity);
}

bool OrderRouter::OnExchangeNew(const OrderIdentifier& aInternal,
                                 const std::string &aExternal){

    return _orderManager->OnExchangeNew(aInternal, aExternal);
}

std::string OrderRouter::HandleMessage(char* msg){
    cout<<"HandleMessage:"<<msg<<endl;
    int action=0;
    auto it = find(msg, msg+strlen(msg), ',');
    if(it != msg+strlen(msg))
    {
        *it = '\0';
        ++it;
    }
    else{
        cout<<"data error!"<<msg<<endl;
        return "data error";
    }

    sscanf(msg,"%d",&action);
    switch(action){
    case 1:
    {
        uint32_t market, desk, trader, sequence, price, quantity;
        sscanf(it,"%d,%d,%d,%d,%d,%d",&market,&desk,&trader,&sequence,&price,&quantity);
        OrderIdentifier oi{(uint16_t)market,(uint16_t)desk,(uint16_t)trader,sequence};
        auto ret = _orderManager->OnTraderEnter(oi, price, quantity);
        if(ret){
            return "successful";
        }
        else{
            return "failed";
        }
    }
    break;
    }
    return "";
}
