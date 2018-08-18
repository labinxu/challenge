#include <thread>
#include <mutex>

#include "test_orderidentifier.h"
#include "../types.h"
#include "../trader.h"
#include "../orderrouter.h"
#include "../exchange.h"
using namespace std;

int main()
{
    auto router = new OrderRouter();
    auto trader = new Trader(router, 1);
    mutex mut;
    auto exchange = new Exchange(router);
    thread tdrthread(&Trader::start, trader);
    thread exthread(&Exchange::start, exchange);


    tdrthread.join();
    exthread.join();

    return 0;
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
