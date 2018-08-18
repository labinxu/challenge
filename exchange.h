#ifndef EXCHANGE_H
#define EXCHANGE_H
#include <mutex>
#include "orderrouter.h"

class Exchange
{
 public:
    Exchange(OrderRouter *router):_router(router){}
    void start();

private:
    OrderRouter *_router;
};

#endif
