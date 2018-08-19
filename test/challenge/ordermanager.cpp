#include <iostream>
#include <algorithm>
#include <tuple>
#include <iterator>
#include "ordermanager.h"
using namespace std;
void DisplayOrder(const Order &od){
    cout<<"market:"<<od._internal._market<<" ;desk:"<<od._internal._desk<<" ;trader:"<<od._internal._trader<<" ;sequence:"<<od._internal._sequence<<" ;price:"<<od._price<<" ;quantity:"<<od._quantity<<endl;
}
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
    //auto ait =
    _orders.insert(make_pair(aInternal,
                             Order{aInternal, aPrice, aQuantity,
                                     OdrStatus::OrderEntered,""}));
    //DisplayOrder(ait.first->second);
    return true;
}

bool OrderManager::OnTraderCancel(const OrderIdentifier& aInternal)
{
    {
        std::lock_guard<std::mutex> cguard(_cancelsMutex);
        auto itc = GetOrderByInternal(_cancelledOrders, aInternal);
        // it's already in cancelled list
        if(itc != nullptr){
            cout<<"already in the cancel list"<<endl;
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
        if (ost == OdrStatus::OrderConfirmed || ost == OdrStatus::OrderTraded){
            it->second._status = OdrStatus::TraderCancelled;
            std::lock_guard<std::mutex> cguard(_cancelsMutex);
            _cancelledOrders.push_back(&(it->second));
            return true;
        }
        else
        {
            cout<<"status is wrong "<<int(ost)<<endl;
        }
    }
    else
    {
        cout<<"not found order"<<endl;
    }

    return false;
}

bool OrderManager::OnExchangeCancel(const std::string& aExternal)
{
    std::lock_guard<std::mutex> cguard(_cancelsMutex);
    for (auto it:_cancelledOrders){
        cout<<"it->_external:"<<it->_external<<"aExternal:"<<aExternal<<endl;
        if (it->_external == aExternal){
            it->_status = OdrStatus::OrderCancelled;
            return true;
        }
    }
    return false;
}

bool OrderManager::OnExchangeNew(const OrderIdentifier& aInternal,
                               const std::string& aExternal)
{

    std::lock_guard<std::mutex> cguard(_ordersMutex);
    auto it = _orders.find(aInternal);
    // trader not enter the order
    if (it == _orders.end()){
        cout<<"Order not found!"<<endl;
        return false;
     }
    if (it->second._status != OdrStatus::OrderEntered){
        cout<<"Status of order is wrong!"<<endl;
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
