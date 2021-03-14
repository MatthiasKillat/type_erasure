#pragma once

#include <type_traits>

//TODO: could be improved regarding error output
//      will also detect static functions
//      namespace needed and avoid multiple definitions via macro

#define GENERATE_HAS_FUNC(funcname)                                            \
    template <typename, typename T>                                            \
    struct has_func_##funcname                                                 \
    {                                                                          \
        static_assert(                                                         \
            std::integral_constant<T, false>::value,                           \
            "second parameter needs to be a function signature type");         \
        operator bool() { return false; }                                      \
    };                                                                         \
    template <typename C, typename Ret, typename... Args>                      \
    struct has_func_##funcname<C, Ret(Args...)>                                \
    {                                                                          \
    private:                                                                   \
        template <typename T>                                                  \
        static constexpr auto check(T *)                                       \
            -> typename std::is_same<                                          \
                decltype(std::declval<T>().funcname(std::declval<Args>()...)), \
                Ret>::type;                                                    \
        template <typename>                                                    \
        static constexpr std::false_type check(...);                           \
        typedef decltype(check<C>(0)) type;                                    \
                                                                               \
    public:                                                                    \
        static constexpr bool value = type::value;                             \
        operator bool() { return value; }                                      \
    };

#define REQUIRE_FUNCTION(type, funcname, signature)            \
    static_assert(has_func_##funcname<type, signature>::value, \
                  "no function " #type "::" #funcname " with signature " #signature);
