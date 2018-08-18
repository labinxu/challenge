#include <iostream>
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

void OrderRouter::HandleMessage(const char* msg){
    cout<<"HandleMessage:"<<msg<<endl;
}
