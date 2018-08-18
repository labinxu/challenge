#include <algorithm>
#include <tuple>
#include <iterator>
#include "ordermanager.h"
using namespace std;

Orders_i::value_type OrderManager::GetOrderByInternal(const Orders_i& orders,
                                                      const OrderIdentifier& aInternal) const{
    auto itc = std::find_if(begin(orders),
                            end(orders), [&](const Orders_i::value_type& v){
                                return v->_internal ==  aInternal;
                            });
    if (itc != end(orders)){
        return *itc;
    }
    return nullptr;
}

Orders_i::value_type OrderManager::GetOrderByExternal(const Orders_i& orders,
                                                      const std::string& aExternal) const{ 
    auto itc = std::find_if(begin(orders),
                            end(orders), [&](const Orders_i::value_type& v){
                                return v->_external == aExternal;
                            });
    if (itc != end(orders)){
        return *itc;
    }
    return nullptr;

}
bool OrderManager::OnTraderEnter(const OrderIdentifier& aInternal, uint32_t aPrice,
                                 uint32_t aQuantity)
{
    std::lock_guard<std::mutex> guard(_ordersMutex);
    auto it = _orders.find(aInternal);
    if(it != _orders.end()){
        return false;
    }
    // insert order into orders
    _orders.insert(make_pair(aInternal,
                             Order{aInternal,aPrice, aQuantity,
                                     OdrStatus::OrderEntered,""}));
    return true;
}

bool OrderManager::OnTraderCancel(const OrderIdentifier& aInternal)
{
    {
        std::lock_guard<std::mutex> cguard(_cancelsMutex);
        auto itc = GetOrderByInternal(_cancelledOrders, aInternal);
        // it's already in cancelled list
        if(itc != nullptr){
            return false;
        }
    }

    // The Trader made a mark for cancel an order,
    // and put the order into cancels ,
    // after the exchange canlled received the set status to Order cancelled
    std::lock_guard<std::mutex> guard(_ordersMutex);
    auto it = _orders.find(aInternal);
    if (it != _orders.end()){
        auto ost = it->second._status;
        if (ost != OdrStatus::OrderConfirmed || ost != OdrStatus::OrderTraded){
            return false;
        }
        it->second._status = OdrStatus::TraderCancelled;
    }
    std::lock_guard<std::mutex> cguard(_cancelsMutex);
    _cancelledOrders.push_back(&(it->second));
    return true;
}

bool OrderManager::OnExchangeCancel(const std::string& aExternal)
{
    auto it =  GetOrderByExternal(_cancelledOrders, aExternal);
    if(it != nullptr){
        if (it->_status != OdrStatus::TraderCancelled){
            return false;
        }
        it->_status = OdrStatus::OrderCancelled;
        return true;
    }
    return false;
}

bool OrderManager::OnExchangeNew(const OrderIdentifier& aInternal,
                               const std::string& aExternal)
{
    auto it = _orders.find(aInternal);
    // trader not enter the order
    if (it == _orders.end()){
         return false;
     }
    if (it->second._status != OdrStatus::OrderEntered){
        return false;
    }

    it->second._status = OdrStatus::OrderConfirmed;
    it->second._external = aExternal;
    std::lock_guard<std::mutex> guard(_activesMutex);
    _activeOrders.push_back(&(it->second));
    return true;
}

bool OrderManager::OnExchangeTrade(const std::string& aExternal,
                                   uint32_t aQuantity)
{
    auto od = GetOrderByExternal(_activeOrders, aExternal);
    if (od == nullptr){
        return false;
    }

    if(aQuantity > od->_quantity){
        // quantity error
        return false;
    }

    od->_quantity -= aQuantity;
    if (od->_quantity == 0){
        // used up
    }

    return true;
}
//
// Assume the order status is not OrderCancelled or OrderEntered
//
bool OrderManager::IsOrderActive(const OrderIdentifier& aInternal) const
{
    auto it = _orders.find(aInternal);
    if(it != end(_orders)){
        return (it->second._status != OdrStatus::OrderEntered||
                it->second._status != OdrStatus::OrderCancelled);
    }

    // not found the order
    return false;
}

bool OrderManager::IsOrderActive(const std::string& aExternal) const
{
     // Assume the order status is not OrderCancelled or OrderEntered
     auto it = GetOrderByExternal(_activeOrders, aExternal);
     if (it != nullptr){
         return true;
     }
     return false;
}

uint32_t OrderManager::GetActiveOrderQuantity(const OrderIdentifier&
aInternal) const
{
    auto it = _orders.find(aInternal);
    if(it != end(_orders)){
        return it->second._quantity;
    }
    return 0;
}
