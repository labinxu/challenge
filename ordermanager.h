#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <vector>
#include "iordermanager.h"
#include "types.h"

class OrderManager: public IOrderManager
{
public:
    OrderManager() = default;
     // trader operations - these return false if there is a problem
    virtual bool OnTraderEnter(const OrderIdentifier& aInternal, uint32_t
aPrice, uint32_t aQuantity);
    virtual bool OnTraderCancel(const OrderIdentifier& aInternal);
    // exchange operations - these return false if there is a problem
    virtual bool OnExchangeNew(const OrderIdentifier& aInternal,
                               const std::string& aExternal);
    virtual bool OnExchangeTrade(const std::string& aExternal,
                                 uint32_t aQuantity);
    virtual bool OnExchangeCancel(const std::string& aExternal);
    virtual bool IsOrderActive(const OrderIdentifier& aInternal) const;
    virtual bool IsOrderActive(const std::string& aExternal);
    // returns the quantity of the order that is active in the market, or
//zero if the order isn't
    // recognised or is not active
 
virtual uint32_t GetActiveOrderQuantity(const OrderIdentifier&
aInternal) const;

private:
    std::vector<Order> _activeOrders;
    
};
#endif
