#include "test_orderidentifier.h"
#include "../types.h"
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <iterator>
#include "../ordermanager.h"
using namespace std;
int main()
{
    Orders orders;
    Order order;
    OrderIdentifier oi{1,2,3,4};
    order._internal = oi;
    order._price = 1;
    order._quantity = 2;
    order._external = "";
    orders.insert(make_pair(oi, order));
}

// #include <iostream>


// #include "../message.h"


// #include "../types.h"


// using namespace std;


// int main()


// {


//   //OrderIdentifier oi{1,2,3,4};


//   auto msg=new message<OrderIdentifier>(OrderIdentifier{1,2,3,4},message_type::CANCEL_ORDER);


  


//   std::cout<<int(msg->msg_type())<<std::endl;


// 　


//   auto msg1 = make_message<OrderIdentifier>(msg->data());


//   auto oi = msg1->get_value();


//   std::cout<<oi->_market<<oi->_desk<<oi->_trader<<oi->_sequence<<endl;


// 　


// }
