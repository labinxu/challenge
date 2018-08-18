#include <iostream>
#include "trader.h"
#include "orderrouter.h"
using namespace std;
void Trader::start()
{
    uint16_t market, desk, sequence;
    uint32_t quantity, price;
    int action = 0;
    while(true){
        cout<<"Input action 1: Enter Order,2:Cancell Order"<<endl;
        cin>>action;
        switch (action){
        case 1:
        {
            cout<<"input market, desk, sequence"<<endl;
            cin>>market>>desk>>sequence;
            cout<<"input quantity, price"<<endl;
            cin>>quantity>>price;
            OrderIdentifier oi{market, desk, _trader, sequence};
            if (_orderRouter->OnTraderEnter(oi, quantity, price)){
                cout<<"successful"<<endl;
            }
            else
            {
                cout<<"failed"<<endl;
            }
        }
        break;
        case 2:
            break;
        default:
            break;
        }
    }
}
