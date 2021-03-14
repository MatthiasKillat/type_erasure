#pragma once

#include <iostream>
#include <string>

//simplified
template <uint64_t Capacity>
class String
{
    //would not be used in actual implementation
    std::string m_data;

public:
    String()
    {
        //actually known at compile time but needs sophisticated init tricks
        //due to Capacity
        m_data = "String<" + std::to_string(Capacity) + ">";
    }

    const char *c_str()
    {
        return m_data.c_str();
    }
};
