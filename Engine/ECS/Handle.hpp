/*
Shophorn
Leo Tamminen
Created 17/02/2019
*/

#pragma once

#include <functional> // hash

// Index to entity, counter to tell generation, ie. this handle has expired if it has wrong counter
// Counter is advanced when handle is reused
struct Handle
{
    constexpr Handle () : index(0), counter (0) {}
    constexpr Handle (unsigned _index, unsigned _counter) : index(_index), counter (_counter) {}

    constexpr bool operator == (const Handle& rhs)
    {
        return index == rhs.index && counter == rhs.counter;
    }

    constexpr  bool operator != (const Handle & rhs)
    {
        return !(*this == rhs);
    }

    constexpr bool operator == (const Handle& rhs) const
    {
        return index == rhs.index && counter == rhs.counter;
    }

    constexpr  bool operator != (const Handle & rhs) const

    {
        return !(*this == rhs);
    }

    constexpr unsigned hash() const { return counter << 16 | index; }

    // TODO
    // bool isValid
    // operator bool
    // hash

    // this is called bit field, 'unsigned' is just alias to 'unsigned int', and 16 masks only 16 bits of it.
    // This uses explicit number of bytes, unlike 'short' or 'int'
    unsigned index : 16;
    unsigned counter : 16;
};

namespace std
{
    template <> struct hash<Handle>
    {
        size_t operator() (const Handle & h) const noexcept
        {
            return h.hash();
        }
    };
}