#include "type_erasure/any_pushpop.hpp"

#include "user/client_class.hpp"
#include "user/user_types.hpp"

#include <vector>
#include <iostream>

using Client1 = Client<int, Stack<int>>;
using Client2 = Client<int, Queue<int>>;

//note Client1 and Client2 not only use the concept but they also satsify it themselves
//(this must not be the case in general)

//can be defined but when creating it we fail at compile time since the pop method is missing
//in Pusher (the type is only instantiated and fully compiled when used)
using Client3 = Client<int, PushOnly<int>>;

using Any = AnyPushPop<int>;
using namespace std;

int main(int argc, char **argv)
{
    Client1 client1;
    Client2 client2;
    //Client3 client3; //does not compile, concept not implemented

    client1.push(73);
    client1.push(42);
    auto result1 = client1.pop();
    if (result1)
        cout << "result1 " << *result1 << endl;

    client2.push(37);
    auto result2 = client2.pop();
    if (result2)
        cout << "result2 " << *result2 << endl;

    cout << "**************" << endl;
    cout << "client1 push calls " << client1.numPushCalls() << endl;
    cout << "client1 pop calls " << client1.numPopCalls() << endl;
    cout << "client2 push calls " << client2.numPushCalls() << endl;
    cout << "client2 pop calls " << client2.numPopCalls() << endl;

    return 0;
}