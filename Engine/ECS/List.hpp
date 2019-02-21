/*
LeoTamminen
Created 18/02/2019
*/

#pragma once

#include <type_traits>

// Metaprogramming Template Library, that is cool
namespace mtl
{
    template<typename ... Types>
    struct List {};

    using emptyList = List<>;

    namespace detail
    {
        template<typename T>
        struct listSize;

        template<typename ... Types>
        struct listSize<List<Types ...>>
        {
            using value = std::integral_constant<int, sizeof ... (Types)>;
        };
    }

    template<typename List>
    using listSize = typename detail::listSize<List>::value;
}