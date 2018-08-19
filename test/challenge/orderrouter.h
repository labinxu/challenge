#ifndef ORDER_ROUTER_H
#define ORDER_ROUTER_H
#include <unistd.h>
#include <mutex>
#include "types.h"
#include "ordermanager.h"
#include "types.h"
#include "server.h"

class OrderRouter: public Server{
public:
    OrderRouter():_orderManager(new OrderManager()){}
    std::string HandleMessage(char *msg);
private:
    OrderManager *_orderManager;
};

#endif
