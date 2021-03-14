#include <vector>
#include <iostream>
#include <optional>

// Problem: Create a container capable of holding different objects
//          that adhere to the PushPop interface with the following
//          additional requirements
//          1) The objects are be usable in a polymorphic way (i.e. behave
//             as the actual type).
//          2) The objects are be owned by the container.
//          3) The object classes do not need to inherit from the interface.

// Regular polymorphism only achieves 1) but fails at 2) and 3).

template <typename ValueType>
class PushPopInterface
{
public:
    virtual ~PushPopInterface() {}

    virtual bool push(const ValueType &value) = 0;
    virtual std::optional<ValueType> pop() = 0;
};

template <typename T>
class Stack : public PushPopInterface<T> // violates 3)
{
public:
    bool push(const T &value)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return false;
    }

    std::optional<T> pop()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return std::nullopt;
    }
};

template <typename T>
class Queue : public PushPopInterface<T> // violates 3)
{
public:
    bool push(const T &value)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return false;
    }

    std::optional<T> pop()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return std::nullopt;
    }
};

using PushPop = PushPopInterface<int>;

int main(int argc, char **argv)
{
    std::vector<PushPop *> v;
    v.push_back(new Queue<int>);
    v.push_back(new Stack<int>);

    for (auto p : v)
    {
        //behaves polymorphically 1)
        p->push(37);
        p->pop();
        std::cout << "********" << std::endl;
    }

    // v does not own the actual objects, we need to delete them once done - violates 2)
    for (auto p : v)
    {
        delete p;
    }

    return 0;
}

// To achieve 1), 2) and 3) we will use a specific form of type erasure.
// We only require the user types to be copyable (fairly weak restriction).
