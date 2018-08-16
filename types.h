#ifndef TYPES_H
#define TYPES_H
// test web edittest web edit
#include <stdint.h>
#include <string>
#include <sstream>

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
    std::string Serialize() const;
    OrderIdentifier& Deserialize(const char *data, uint32_t len);
};

struct Order{
    OrderIdentifier _orderIdentifier;
    uint32_t _price;
    uint32_t _quantity;
    std::string _changeIdentifier;
};

enum class TradeAction {ENT_ORDER, CANCEL_ORDER, ORDER_TRADE};
#endif