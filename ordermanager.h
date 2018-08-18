#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H
#include <mutex>
#include <sstream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <functional>
#include "types.h"
#include "iordermanager.h"

namespace std
{
    template<>
    struct hash<OrderIdentifier>
    {
        std::size_t operator()(const OrderIdentifier &key) const{
            using std::size_t;
            using std::hash;
            std::stringstream strm;
            strm<<key._market<<key._desk<<key._trader<<key._sequence;
            //return std::_Hash_seq((const unsigned char *)&key, sizeof(OrderIdentifier));
            return hash<std::string>()(strm.str());
        }
    };
};

typedef std::unordered_map<OrderIdentifier, Order> Orders;
typedef std::vector<Order*> Orders_i;

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
    virtual bool IsOrderActive(const std::string& aExternal) const;
    // returns the quantity of the order that is active in the market, or
//zero if the order isn't
    // recognised or is not active
    virtual uint32_t GetActiveOrderQuantity(const OrderIdentifier& aInternal) const;

    Orders_i::value_type GetOrderByInternal(const Orders_i &orders,
                                            const OrderIdentifier &aInternal) const;

    Orders_i::value_type GetOrderByExternal(const Orders_i &orders,
                                            const std::string &aExternal) const;

private:
    std::mutex _ordersMutex;
    std::mutex _cancelsMutex;
    std::mutex _activesMutex;
    std::mutex _tradedMutex;

    Orders _orders;
    Orders_i _activeOrders;
    Orders_i _cancelledOrders;
    Orders_i _tradedOrders;
};

template <class T>
class Singleton{
public:
    static T& GetInstance(){
        static T instance;
        return instance;
    }

private:
    Singleton();
    ~Singleton();
    Singleton(const Singleton&);
    Singleton& operator =(const Singleton&);
};
#endif
