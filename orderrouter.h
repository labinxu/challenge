#ifndef ORDER_ROUTER_H
#define ORDER_ROUTER_H

#include <string>
#include <unistd.h>
#include "server.h"
#include "types.h"
#include "ordermanager.h"

class OrderRouter: public Server{
protected:
    OrderRouter();
    bool EnterOrder(const OrderIdentifier& orderIdentifier,
                    uint32_t price, uint32_t quantity);

    bool CancelOrder(const std::string &exchangeIdentifier);

    void HandleMessage(const char* msg);

private:
    OrderManager* _orderManager;
};

#endif
