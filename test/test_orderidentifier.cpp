#include "../types.h"
#include <string>
#include <iostream>

using namespace std;

void test_OrderIdentifier_Serialize()
{
    OrderIdentifier oi{1,2,3,4};
    std::string serialized = oi.Serialize();
    cout<<serialized<<endl;
}



