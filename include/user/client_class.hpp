#pragma once

#include <optional>

#include "concepts/pushpop_concept.hpp"

// the client uses concept PushPop but also has additional functionality

template <typename T, typename PushPop>
class Client
{
    //PushPop implements the concept interface
    REQUIRE_FUNCTION(PushPop, push, bool(const T &));
    REQUIRE_FUNCTION(PushPop, pop, std::optional<T>());

public:
    bool push(const T &value)
    {
        ++pushCalls;
        return q.push(value);
    }

    std::optional<T> pop()
    {
        ++popCalls;
        return q.pop();
    }

    int numPushCalls()
    {
        return pushCalls;
    }

    int numPopCalls()
    {
        return popCalls;
    }

private:
    PushPop q;

    int pushCalls{0};
    int popCalls{0};
};