#pragma once

#include <optional>

template <typename ValueType>
class PushPopInterface
{
public:
    virtual ~PushPopInterface() {}

    virtual bool push(const ValueType &value) = 0;
    virtual std::optional<ValueType> pop() = 0;
};