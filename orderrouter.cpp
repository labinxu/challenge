#include "orderrouter.h"
#include "challenge.h"
#include "ordermanager.h"

OrderRouter::OrderRouter(){
    //get the ordermanager
}

bool OrderRouter::EnterOrder(uint16_t m, uint16_t d, uint32_t price, uint32_t quanlity){
    auto sq = _orderIdentifier.size()+1;
    _orderIdentifier.push_back(OrderIdentifier(m, d, _identify, sq));
    _orderManager->OnTraderEnter(_order, price, quanlity);

}

// handle the message from the trader
void OrderRouter::HandleMessage(const char *msg)
{
    
}
