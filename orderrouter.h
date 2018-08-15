#ifndef ORDER_ROUTER_H
#define ORDER_ROUTER_H

struct Order;
class OrderManager;

class OrderRouter{
public:
    OrderRouter();
    bool EnterOrder(const Order& order);
private:
    OrderManager* _orderManager;
};

#endif
