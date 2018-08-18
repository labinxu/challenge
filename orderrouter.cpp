#include "orderrouter.h"
#include "challenge.h"
#include "ordermanager.h"

bool OrderRouter::OnTraderEnter(const OrderIdentifier& aInternal,
                                uint32_t aPrice,uint32_t aQuantity){
    _orderManager->OnTraderEnter(aInternal, aPrice, aQuantity);
}
