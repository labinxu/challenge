#ifndef ORDER_ROUTER_H
#define ORDER_ROUTER_H
#include <list>
#include <tuple>
#include <string>
#include <unistd.h>
#include <mutex>
#include "types.h"
#include "ordermanager.h"
#include "types.h"
#include "server.h"

typedef std::tuple<OrderIdentifier, uint32_t, uint32_t> TraderMsg;

class OrderRouter: public Server{
public:
    OrderRouter():_orderManager(new OrderManager()){}
    bool OnTraderEnter(const OrderIdentifier& aInternal,
                       uint32_t aPrice, uint32_t aQuantity);

    bool OnExchangeNew(const OrderIdentifier& aInternal,
                                     const std::string& aExternal);

    std::string HandleMessage(char *msg);
private:
    OrderManager *_orderManager;
};

#endif
