#ifndef TRADER_H
#define TRADER_H

#include <mutex>
#include <vector>
#include <memory>
#include "orderrouter.h"
#include "types.h"

class Trader{

public:
    Trader() = default;
    Trader(OrderRouter *router, uint16_t t)
        :_trader(t),_orderRouter(router){}

    void start();

private:
    uint16_t _trader;
    OrderRouter *_orderRouter;
};

#endif
