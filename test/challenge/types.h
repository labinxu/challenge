#ifndef TYPES_H
#define TYPES_H
#include <stdint.h>
#include <string>

// company's order identifier
struct OrderIdentifier {
     OrderIdentifier()
          :_market(0),
           _desk(0),
           _trader(0),
           _sequence(0){}

    OrderIdentifier(uint16_t m, uint16_t d, uint16_t t, uint32_t s)
        : _market(m)
        , _desk(d)
        ,_trader(t)
        ,_sequence(s){}

    uint16_t _market;
    uint16_t _desk;
    uint16_t _trader;
    uint32_t _sequence;
};
inline bool operator == (const OrderIdentifier &lhs,
                         const OrderIdentifier &rhs){
     return lhs._market == rhs._market &&
          lhs._desk == rhs._desk &&
          lhs._trader==rhs._trader &&
          lhs._sequence == rhs._sequence;
}

enum class OdrStatus:char {
    OrderDefault,
    OrderEntered=1 ,OrderConfirmed=2,
    OrderTraded=3, TraderCancelled=4,
    OrderCancelled=5
};

struct Order{
     OrderIdentifier _internal;
     uint32_t _price;
     uint32_t _quantity;
     OdrStatus _status;
     std::string _external;
};

#endif
