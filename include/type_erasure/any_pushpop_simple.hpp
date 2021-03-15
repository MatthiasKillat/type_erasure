#pragma once

#include "concepts/pushpop_concept.hpp"

#include <memory>
#include <optional>

//The file could be generated automatically from the concept interface.

//class capable of holding any object implementing PushPopInterface
//does not implement copy behavior of the actual type
template <typename ValueType>
class AnyPushPop
{
private:
    template <typename PushPopType>
    class PushPopDelegate : public PushPopInterface<ValueType>
    {
    public:
        PushPopDelegate(const PushPopType &obj) : m_native(obj)
        {
        }

        bool push(const ValueType &value)
        {
            return m_native.push(value);
        }

        std::optional<ValueType> pop()
        {
            return m_native.pop();
        }

    private:
        PushPopType m_native; //the underlying object (copy)
    };

public:
    //PushPopType has to implement the PushPop concept
    template <typename PushPopType>
    AnyPushPop(const PushPopType &obj) : m_delegate(std::make_shared<PushPopDelegate<PushPopType>>(obj))
    {
    }

    AnyPushPop(const AnyPushPop &other) = delete; //we cannot copy it with this implementation
    AnyPushPop(AnyPushPop &&other) = default;

    bool push(const ValueType &value)
    {
        return m_delegate->push(value); //note that shared_pointer behaves polymorphically
    }

    std::optional<ValueType> pop()
    {
        return m_delegate->pop();
    }

private:
    //the dtor will delete the copy of the underlying object
    //since we do not allow copies for now, it could be a unique pointer
    std::shared_ptr<PushPopInterface<ValueType>> m_delegate;
};