#include "trader.h"
#include "orderrouter.h"

bool Trader::EnterOrder(uint16_t m, uint16_t d, uint32_t price, uint32_t quantity)
{
    auto sq = _orderIdentifies.size()+1;
    auto odi = (std::make_shared<OrderIdentifier>(m, d, _identify, sq));
    _orderIdentifies.push_back(odi);
    _orderManager->OnTraderEnter(*odi, price, quantity);
}
