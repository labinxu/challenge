#ifndef CHALLENGE_H
#define CHALLENGE_H

#include <stdint.h>
#include <string>
// company's order identifier
struct OrderIdentifier {
    OrderIdentifier() = default;
    OrderIdentifier(uint16_t m, uint16_t d, uint16_t t, uint32_t s)
        : _market(m)
        , _desk(d)
        ,_trader(t)
        ,_sequence(s){}

    uint16_t _market{0};
    uint16_t _desk{0};
    uint16_t _trader{0};
    uint32_t _sequence{0};
};


struct Order{
    OrderIdentifier _orderIdentifier;
    uint32_t _price;
    uint32_t _quantity;
    std::string _changeIdentifier;
};

#endif
