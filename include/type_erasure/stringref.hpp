#pragma once
#include "concepts/member_func_check.hpp"

GENERATE_HAS_FUNC(c_str);

//simplified interface
class StringInterface
{
public:
    virtual ~StringInterface() {}

    virtual const char *c_str() = 0;
};

#include <memory>
#include <iostream>

class StringRef
{
private:
    template <typename StringType>
    class StringDelegate : public StringInterface
    {
    public:
        StringDelegate(StringType &string) : m_string(&string)
        {
        }

        const char *c_str()
        {
            return m_string->c_str();
        }

    private:
        StringType *m_string; //we only hold a pointer (!)
    };

public:
    //StringType has to implement StringInterface
    template <typename StringType>
    StringRef(StringType &string)
    {
        REQUIRE_FUNCTION(StringType, c_str, const char *());
        m_delegate = std::make_shared<StringDelegate<StringType>>(string);
    }

    StringRef(const StringRef &other) = default;
    StringRef(StringRef &&other) = default;

    const char *c_str()
    {
        return m_delegate->c_str();
    }

private:
    //since it is a shared pointer we get shallow copy and move
    //we do not own the native string, all copies point to the original(!)
    //hence StringRef
    std::shared_ptr<StringInterface> m_delegate;
};