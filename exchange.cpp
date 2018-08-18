#include <iostream>
#include <string>
#include <cstdio>
#include <unistd.h>
#include "exchange.h"
#include "types.h"

using namespace std;

void Exchange::start(){
    while(true){
        cout<<"Input action 1:confirm order, 2:order cancel, 3: order trade"<<endl;
        int action = 0;
        cin>>action;
        switch(action){
        case 1:
        {
            cout<<"input order identifier\n market,desk,trader,sequence"<<endl;
            std::string oi;
            std::string external;
            cin>>oi;
            uint32_t market, desk, trader, sequence;
            sscanf(oi.c_str(),"%d,%d,%d,%d",&market,&desk,&trader,&sequence);
            cout<<market<<desk<<trader<<sequence<<endl;
            cout<<"Input external"<<endl;
            cin>>external;
            OrderIdentifier oif{(uint16_t)market, (uint16_t)desk, (uint16_t)trader, sequence};
            _router->OnExchangeNew(oif, external);
        }
        break;
        }
    }
}
