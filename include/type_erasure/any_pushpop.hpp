#pragma once

#include "concepts/pushpop_concept.hpp"

#include <memory>
#include <optional>
#include <iostream>

//The file could be generated automatically from the concept interface.

//class capable of holding any object implementing PushPopInterface
//implements copy and move behavior of the actual type
template <typename ValueType>
class AnyPushPop
{
private:
    //we need polymorphic copy behavior
    class CloneablePushPopInterface : public PushPopInterface<ValueType>
    {
    public:
        virtual CloneablePushPopInterface *clone() = 0;
    };

    template <typename PushPopType>
    class PushPopDelegate : public CloneablePushPopInterface
    {
    public:
        //PushPopType must be copyable
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

        //we retain the information how to copy the native type in this way
        CloneablePushPopInterface *clone()
        {
            return new PushPopDelegate(m_native);
        }

    private:
        PushPopType m_native; //the underlying object (copy)
    };

public:
    //PushPopType has to implement the PushPop concept
    template <typename PushPopType>
    AnyPushPop(const PushPopType &obj) : m_delegate(new PushPopDelegate(obj))
    {
        //state type requirements
        //generate better (?) compiler errors
        REQUIRE_FUNCTION(PushPopType, push, bool(const ValueType &));
        REQUIRE_FUNCTION(PushPopType, pop, std::optional<ValueType>());
    }

    ~AnyPushPop()
    {
        cleanup();
    }

    AnyPushPop(const AnyPushPop &other) : m_delegate(other.m_delegate->clone())
    {
    }

    AnyPushPop(AnyPushPop &&other) : m_delegate(other.m_delegate)
    {
    }

    AnyPushPop &operator=(const AnyPushPop &other)
    {
        if (&other != this)
        {
            cleanup();
            m_delegate = other.m_delegate->clone();
        }
        return *this;
    }

    AnyPushPop &operator=(AnyPushPop &&other)
    {
        if (&other != this)
        {
            cleanup();
            m_delegate = other.m_delegate;
            other.m_delegate = nullptr;
        }
        return *this;
    }

    bool push(const ValueType &value)
    {
        return m_delegate->push(value);
    }

    std::optional<ValueType> pop()
    {
        return m_delegate->pop();
    }

private:
    CloneablePushPopInterface *m_delegate{nullptr};

    void cleanup()
    {
        if (m_delegate)
        {
            delete m_delegate;
        }
    }
};

// note: we can do this without dynamic memory and without internal virtual interfaces
// by using
// i) a storage policy
// ii) creating a "vtable" via function pointers

// virtual or ii) precludes using this in Shared Memory where function pointers may become invalid
