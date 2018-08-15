#ifndef TRADER_H
#define TRADER_H

#include <vector>
#include <memory>
#include "challenge.h"

class Trader{

public:
    Trader() = delete;
    Trader(uint32_t identify)
        :_identify(identify){}

    bool EnterOrder(uint32_t price, uint32_t quantity);
    bool CancleOrder(const OrderIdentifier& orderIdentifier);

private:
    uint32_t _identify{0};
    std::vector<std::shared_ptr<OrderIdentifier> > _orderIdentifies;
};
#endif
