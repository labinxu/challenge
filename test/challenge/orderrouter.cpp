#include <iostream>
#include <cstdio>
#include <algorithm>
#include <sstream>
#include "orderrouter.h"

using namespace std;

std::string OrderRouter::HandleMessage(char* msg){
    cout<<"HandleMessage:"<<msg<<endl;
    int action=0;
    auto it = std::find(msg, msg+strlen(msg), ',');
    if(it != msg+strlen(msg))
    {
        *it = '\0';
        ++it;
    }
    else{
        cout<<"data error!-"<<msg<<endl;
        return "data error!";
    }
    if(sscanf(msg,"%d",&action)==0)
    {
        return "data error";
    }
    msg = it;
    switch(action){
    case 1:
    {
        uint32_t market, desk, trader, sequence, price, quantity;
        auto ret = sscanf(msg,"%d,%d,%d,%d,%d,%d",&market,&desk,&trader,&sequence,&price,&quantity);
        if(ret == 0)
        {
            return "data error";
        }
        OrderIdentifier oi{(uint16_t)market,(uint16_t)desk,(uint16_t)trader,sequence};
        auto r = _orderManager->OnTraderEnter(oi, price, quantity);
        if(r)
        {
            return "successful";
        }
        else
        {
            return "failed";
        }
    }
    break;
    case 2:
    {
        uint32_t market, desk, trader, sequence, price, quantity;
        auto external = msg+strlen(msg);
        while(*external-- != ',');
        *(++external) = '\0';
        external++;
        auto ret = sscanf(msg,"%d,%d,%d,%d,%d,%d",&market,&desk,&trader,&sequence,&price,&quantity);
        if (ret == 0)
        {
            return "data error";
        }

        OrderIdentifier oi{(uint16_t)market,(uint16_t)desk,(uint16_t)trader,sequence};
        auto r = _orderManager->OnExchangeNew(oi, external);
        if(r)
        {
            return "successful";
        }
        else
        {
            return "failed";
        }
    }
    break;
    case 3:
    {// Order traded
        auto external = msg;
        msg = find(external, external+strlen(external), ',');
        *msg++ = '\0';
        uint32_t quantity;
        auto ret = sscanf(msg,"%d",&quantity);
        if (ret == 0)
        {
            return "data error";
        }
        cout<<"external:"<<external<<";quantity:"<<quantity<<endl;
        auto r = _orderManager->OnExchangeTrade(external, quantity);
        if(r)
        {
            return "successful";
        }
        else
        {
            return "failed";
        }
    }
    break;
    case 4:
    {
        uint32_t market, desk, trader, sequence;
        auto ret = sscanf(msg,"%d,%d,%d,%d",&market,&desk,&trader,&sequence);
        if (ret == 0)
        {
            return "data error";
        }
        OrderIdentifier oi{(uint16_t)market,(uint16_t)desk,(uint16_t)trader,sequence};
        if (_orderManager->OnTraderCancel(oi))
        {
            return "successful";
        }
        return "failed";
    }
    break;
    case 5:
    {
        // exchange order cancel
        cout<<"exchange cancel:"<<msg<<endl;
        auto external = msg;
        if(_orderManager->OnExchangeCancel(external))
        {
            return "successful";
        }
        return "failed";
    }
    break;
    case 6:
    {
        // trader query order active
        uint32_t market, desk, trader, sequence;
        auto ret = sscanf(msg,"%d,%d,%d,%d", &market,&desk,&trader,&sequence);
        if (ret == 0)
        {
            return "data error";
        }
        OrderIdentifier oi{(uint16_t)market,(uint16_t)desk,(uint16_t)trader,sequence};
        if (_orderManager->IsOrderActive(oi))
        {
            return "Active";
        }
        return "Disactive";
    }
    break;
    case 7:
    {
        // exchange query order active
        auto external = msg;
        if (_orderManager->IsOrderActive(external))
        {
            return "Active";
        }
        return "Disactive";

    }
    break;
    case 8:
    {
        // trader query order quantity
        uint32_t market, desk, trader, sequence;
        auto ret = sscanf(msg, "%d,%d,%d,%d",&market,&desk,&trader,&sequence);
        if (ret == 0)
        {
            return "data error";
        }
        OrderIdentifier oi{(uint16_t)market,(uint16_t)desk,(uint16_t)trader,sequence};
        auto quantity = _orderManager->GetActiveOrderQuantity(oi);
        std::stringstream strm;
        strm<<quantity;
        return strm.str();
    }
    break;
    default:
        break;
    }//end switch

    return "failed";
}
