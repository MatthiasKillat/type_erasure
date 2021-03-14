#include <iostream>

#include "type_erasure/any_pushpop_simple.hpp"
#include "user/user_types.hpp"

#include <vector>

using Any = AnyPushPop<int>;
using namespace std;

int main(int argc, char **argv)
{
    Stack<int> stack;
    Queue<int> queue;
    PushOnly<int> pushOnly;

    Any any(stack);

    std::vector<Any> v;
    v.emplace_back(stack);
    v.emplace_back(queue);
    v.emplace_back(any); // AnyPushPop also implements the concept itself

    //v.emplace_back(pushOnly); //error, does not implement PushPop concept

    for (auto &any : v)
    {
        any.push(73);
        any.pop();
        cout << "*********" << endl;
    }

    return 0;
}

// Goal achieved: AnyPushPop satisfies
//                1) polymorphic behavior
//                2) owns the objects
//                3) user types do not need to inherit from the interface
//
// Drawbacks:
//                A) AnyPushPop is not copyable (yet)
//                B) client type requirements not clearly stated (improve template errors)
//                C) we use dynamic memory (shared_ptr)
//                D) delegation call overhead (virtual)
//                E) native type cannot be retrieved from AnyPushPop

// A) will be solved in advanced variant
// B) use pseudo concepts
// C) can be solved with some effort and limitations - shared pointer is only for convenience
//    we can define our own storage type and simulate a vtable
// D) is somewhat unavoidable (price of generality) but potentially improvable
// E) can only be achievd in a limited way using RTTI, we need to "guess" the native type similar
//    to dynamic_cast or any_cast<T> of std::any