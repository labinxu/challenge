#include "test_orderidentifier.h"
#include <iostream>
using namespace std;

int main()
{
    int action = 0;
    while (true)
    {
        cout<<"Input action:[1: Enter Order] ,[2:Cancell Order]"<<endl;
        cin>>action;
        cout<<action<<endl;
        switch (action){
        case 1:
            break;
        default:
            cout<<"Please input correct action"<<endl;
            break;
        }
        action = 0;
        cin.clear();
        cin.ignore();
    }
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
