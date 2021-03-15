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

    stack.push(42);

    // checks that we actually work on a copy
    auto result = any.pop();
    if (result)
    {
        cout << "any pop " << *result << endl;
    }
    else
    {
        cout << "any is empty" << endl;
    }

    any.push(37);
    result = stack.pop();
    if (result)
    {
        cout << "stack pop " << *result << endl;
    }
    else
    {
        cout << "stack is empty" << endl;
    }

    cout << "******vector test*********" << endl;

    std::vector<Any> v;
    v.emplace_back(stack);
    v.emplace_back(queue);

    //v.emplace_back(pushOnly); //error, does not implement PushPop concept

    for (auto &obj : v)
    {
        obj.push(73);
        auto result = obj.pop();
        if (result)
        {
            cout << "pop " << *result << endl;
        }
        else
        {
            cout << "empty" << endl;
        }
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