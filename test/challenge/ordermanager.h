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

/*
  Modules : router, trader, exchange,

  router: responsible for message router between trader and exchange,
  it's an interface for ordermanager.

  trader: enter and cancel orders
  exchange: confirm , trade and cancel orders;

  design:
  the orders can queried by internal and external with different query key,
  In order to ensure the data consistency,similar index view structure is needed.
  there I select vector,(unordered_map or map should better when the data is bigger) to store the orders pointer,
  due to simplify the code ,I using thread instead process.

  ambiguities:
  1.
  I assumed the exchange cancel must after cancelled by trader,becuase it's hardly to loop through
  a unordered_map without the key,vector is also , but bit better after the trader put the cancelled orders put into it.

  2.
  2.1
  I'm not sure when the exchange send the message ExchangeNew, So I made the exchange send it motivately.
  the step for a new order,should be 1. trader enter order get the order identifier
     2). exchange get the identifier and generate a external identifier then send all of them to router.
  2.2
    Not deal with the used up orders specially.

  test:
  1.Actually a test framework I would like to use in my work. google test or cppunit
  2.function test.
  3.module test.

  Additionally,I think it's very good idea to using system emulators in testing.

  run:
  using make tool to build the code.

  make -j4
  there should generate four files:trader, router, exchange, test.

  manually run:
  start trader,router,exchange in different terminal.
  in trader terminal:
  according to the hint
  below example: -> means input
  ./trader
  Input action:[1: enter order], [4:cancel order] ,[6, order status], [8, quantity]
-> 1
  input[internal] market, desk, trader, sequence,price,quantity, like 1,2,3,4,5,6
->  1,2,3,4,5,6
  send:1,1,2,3,4,5,6
  result: successful
  Input action:[1: enter order], [4:cancel order] ,[6, order status], [8, quantity]

  on exchange terminal:
  $ ./exchange
  Input action: [2:Order confirmed], [3: Order traded] ,[5:Order cancelled], [7:Order status]
->  2
  input [internal,external]: market, desk, trader, sequence,eg: 1,2,3,4,external
-> 1,2,3,4,external
  send:2,1,2,3,4,external
  result:successful
  Input action: [2:Order confirmed], [3: Order traded] ,[5:Order cancelled], [7:Order status]


  A totally test run is in test file (but it's just simple)
 */

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
#endif
