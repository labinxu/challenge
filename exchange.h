#ifndef EXCHANGE_H
#define EXCHANGE_H
#ifndef EXCHANGE_H
#define EXCHANGE_H
#include <string>
#include <map>
#include <unistd.h>
#include "order.h"

class Exchange
{
 public:
  std::string NewOrderConfirmed(const Order &order);
  bool OrderCancelled(const std::string &exIdentify);
  bool OrderTrade(const std::string &exIdentify);
 private:
  std::map<std::string, Order_t> _confirmedOrders;
  std::map<std::string, Order_t> _cancelledOrders;
  std::map<std::string, uint32_t> _tradedOrders;
};
#endif


#endif
