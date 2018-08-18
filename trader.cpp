#include <iostream>
#include "trader.h"
#include "orderrouter.h"
using namespace std;
void Trader::start()
{
    uint16_t market, desk, sequence;
    uint32_t quantity, price;
    cout<<"input market, desk, sequence"<<endl;
    cin>>market>>desk>>sequence;
    cout<<"input quantity, price"<<endl;
    cin>>quantity>>price;
    OrderIdentifier io{market, desk, _trader, sequence};
    if (_orderRouter->OnTraderEnter(io, quantity, price)){
        cout<<"successful"<<endl;
    }
    else
    {
        cout<<"failed"<<endl;
    }
}
