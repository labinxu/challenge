#include <sstream>
#include "types.h"

// company's order identifier
std::string OrderIdentifier::Serialize() const{
    std::stringstream strm;
    strm<<_market<<_desk<<_trader<<_sequence;
    return strm.str();
}
OrderIdentifier& OrderIdentifier::Deserialize(const char *data, uint32_t len){
    std::stringstream strm;
    strm<<data;
    strm>>_market>>_desk>>_trader>>_sequence;
    return *this;
}


