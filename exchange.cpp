#include <iostream>
#include <sstream>
#include "exchange.h"
using namespace std;

std::string Exchange::NewOrderConfirmed(const Order_t &order,)
{
  // generate the exchange identify
  static uint32_t ident = 0;
  ident++;
  std::stringstream strm;
  strm<<"exch_"<<ident;
  _confirmedOrders.insert(std::make_pair(strm.str(), order));
  return strm.str();
}

bool Exchange::OrderCancelled(const std::string &exIdentity)
{
  auto it = _confirmedOrders.find(exIdentity);
  if (it != _confirmedOrders.end())
  {
       _cancelledOrders.insert(*it);
       _confirmedOrders.erase(it);
       return true;
  }
  else
  {
       cout<<"The order not found"<<endl;
  }
  return false;

}

bool Exchange::OrderTrade(const std::string &exIdentity, uint32_t quantity)
{
     auto it = _confirmedOrders.find(exIdentity);
     if(it != _confirmedOrders.end())
     {
	  if ((*it).second._quantity >= quantity)
	  {
	       (*it).second._quantity -= quantity;
	       // if the quantity is zero ,remove it
	       if ((*it).second._quantity ==  0)
	       {
		    _confirmedOrders.erase(it);
	       }

	       auto tit= _tradedOrders.find(exIdentity);
	       if (tit != _tradedOrders.end())
	       {
		    tit.second += quanlity;
	       }
	       else
	       {
		    _tradedOrders[exIdentity] = quanlity;
	       }
	       return true
	  }
	  else
	  {
	       return false;
	  }
     }
     else
     {
	  cout<<"No order has been found "<<exIdentity<<endl;
	  return false;
     }
}
