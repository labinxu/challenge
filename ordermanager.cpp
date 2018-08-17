#include <tuple>
#include <string>
#include <mutex>
#include <algorithm>
#include "ordermanager.h"
using namespace std;

typedef tuple<OrderIdentifier, uint32_t, uint32_t, string, int> Order_t;
OrderManager::GetOrderByInternal(const vector<Order> &orders, const OrderIdentifier & aInternal){
   std::lock_guard<std::mutex> guard(_orderMutex);
   auto it = find_if(begin(_activeOrders), end(_activeOrders),[&](auto v){
        return (aInternal._market==v._market && aInternal._desk == v._desk)
        && (aInternal._trader ==  v._trader) && (aInternal._sequence == v._sequence);
        });
    return it;
        
};
OrderManager::GetOrderByExternal(const vector<Order> &orders, const std::string & aExternal){
   std::lock_guard<std::mutex> guard(_orderMutex);
   auto it = find_if(begin(_activeOrders), end(_activeOrders),[&](auto v){
            return v->get<3>() == aExternal;
        });
    return it;
        
};

bool OrderManager::OnTraderEnter(const OrderIdentifier& aInternal, uint32_t
aPrice, uint32_t aQuantity){
    Order_t order = make_tuple(aInternal, aPrice, aQuantity, "");
    std::lock_guard<std::mutex> guard(_orderMutex);
    auto it = GetOrderByInternal(_activeOrders, aInternal);
    if(it == end(_activeOrders)){
        _activeOrders.push_back(order);
        return true;
    }
    return false;
}

bool OrderManager::OnTraderCancel(const OrderIdentifier& aInternal)
{
    std::lock_guard<std::mutex> guard(_orderMutex);
    auto it = GetOrder(_orders, aInternal);
    
    // the order not found in orders
    if(it == end(_orders)){
        return false;
    }
   
    auto ait = GetOrder(_traderCancelled, aInternal);
    if (ait != end(_traderCancelled){
     // the order already  cancelled
        return false;
    }
    
    _traderCancels.push_back(*it);
    return true;
}

bool OrderManager::OnExchangeNew(const OrderIdentifier& aInternal,
                               const std::string& aExternal)
{
    auto it = GetOrder(_orders, aInternal);
    
    // the order not found in orders
    if(it == end(_orders)){
        return false;
    }
    
    it->get<3>() = aExternal;
    _activeOrders.push_back(*it);
}

bool OrderManager::OnExchangeTrade(const std::string& aExternal,
                                 uint32_t aQuantity){
     auto it =  GetOrdreByExternal(_activeOrders, aExternal);
        
    if(it != end(_activeOrders))
    {
        if(aQuantity > it->get<2>()){return false;}
        it->get<2>() -= aQuantity;
        if(it->get<2>() == 0)
        {
            // used up.
            
        }
        return ture;
    }
    return false;
}
bool OrderManager::OnExchangeCancel(const std::string& aExternal){
    auto it =  GetOrdreByExternal(_traderCancelled, aExternal);
        
    if(it != end(_traderCancelled))
    {
         it->get<4>() = true;
         return true;
    }
    return false;
}
 virtual bool OrderManager::IsOrderActive(const OrderIdentifier& aInternal) const{
     auto it = GetOrderByInternal(_activeOrders, aInternal);
     return it != end(_activeOrders);

 }
 virtual bool OrderManager::IsOrderActive(const std::string& aExternal) const{
     auto it = GetOrderByExternal(_activeOrders, aExternal);
     return it != end(_activeOrders);
 }
 
virtual uint32_t OrderManager::GetActiveOrderQuantity(const OrderIdentifier&
aInternal) const
{
     auto it = GetOrderByInternal(_activeOrders, aInternal);
     if(it != end(_activeOrders))
     {
        return it->get<3>();
     }
     return 0;
}
