#include "type_erasure/any_pushpop.hpp"
#include "user/user_types.hpp"

#include <vector>
#include <iostream>

using Any = AnyPushPop<int>;
using namespace std;

int main(int argc, char **argv)
{
    Stack<int> stack;
    Queue<int> queue;
    PushOnly<int> pushOnly;
    WrongPopSignature<int> wrongPopSignature;

    Any any(stack);

    //accessing the underlying type requires guessing it ...
    //there is no other way within the C++ language (to my knowledge)
    if (any.cast<Stack<int>>())
    {
        cout << "any is a Stack" << endl;
    }

    if (any.cast<Queue<int>>())
    {
        cout << "any is a Queue" << endl;
    }

    cout << "*********" << endl;

    std::vector<Any> v;
    v.emplace_back(stack);
    v.emplace_back(queue);
    v.emplace_back(any); // AnyPushPop also implements the concept itself

    //v.emplace_back(pushOnly); //error, does not implement PushPop concept
    //v.emplace_back(wrongPopSignature); //error, has the methods but pop has the wrong signature

    int value = 73;
    for (auto &obj : v)
    {
        if (obj.push(value))
            cout << "push: " << value++ << endl;

        auto result = obj.pop();
        if (result)
            cout << "pop: " << *result << endl;
        cout << "*********" << endl;
    }
    cout << "copy vector" << endl;
    std::vector<Any> v_copy(v);

    cout << "*********" << endl;
    cout << "change original vector" << endl;

    value = 37;
    for (auto &obj : v)
    {
        obj.push(value++);
    }
    cout << "*********" << endl;
    for (auto &obj : v)
    {
        auto result = obj.pop();
        if (result)
            cout << "pop: " << *result << endl;
        cout << "*********" << endl;
    }

    cout << "copied vector is unchanged" << endl;
    for (auto &obj : v_copy)
    {
        auto result = obj.pop();
        if (result)
            cout << "pop: " << *result << endl;
        cout << "*********" << endl;
    }

    return 0;
}
