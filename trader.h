#ifndef TRADER_H
#define TRADER_H

#include <vector>
#include <memory>
#include "orderrouter.h"
#include "types.h"

class Trader{

public:
    Trader(OrderRouter *router, uint16_t t)
        :_orderRouter(router),_trader(t){}
    void start();

private:
    uint16_t _trader;
    OrderRouter *_orderRouter;
};

#endif
