#pragma once

#include <optional>
#include <iostream>

template <typename T>
class Stack
{
public:
    bool push(const T &value)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        m_data = value;
        return true;
    }

    std::optional<T> pop()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return m_data;
    }

private:
    std::optional<T> m_data{std::nullopt}; //keep last value
};

template <typename T>
class Queue
{
public:
    bool push(const T &value)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        m_data = value;
        return true;
    }

    std::optional<T> pop()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return m_data;
    }

private:
    std::optional<T> m_data{std::nullopt}; //keep last value
};

template <typename T>
struct PushOnly
{
public:
    bool push(const T &value)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return false;
    }
};

template <typename T>
struct WrongPopSignature
{
public:
    bool push(const T &value)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return true;
    }

    T *pop()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return nullptr;
    }
};
