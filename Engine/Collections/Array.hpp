/*
Leo Tamminen
Created 26/12/2018
*/

#pragma once

#include <initializer_list>
#include <cstring>

namespace Engine::Collections
{
    template<typename T>
    class Array
    {
    private:
        size_t _count;
        T *_values;

    public:
        Array() : _count(0), _values(nullptr) {}
        explicit Array(size_t count) : _count(count), _values(new T[count]) {}

        Array(std::initializer_list<T> list)
        {
            _count = list.size();
            _values = new T[_count];
            std::memcpy(_values, list.begin(), _count * sizeof(T));
        }

        ~Array()
        {
            // TODO: maybe also delete all values independently
            delete[] _values;
        }

        T& operator[](int index) { return _values[index]; }

        size_t count() { return _count; }

        // Range based for loop
        T * begin() { return _values; }
        T * end() { return _values + _count; }

        void DiscardAndResize(size_t count)
        {
            delete [] _values;
            _count = count;
            _values = new T [count];
        }
    };

    template <typename T>
    void DeletePointersInArray(Array<T*> array)
    {
        for (T * pointer : array)
        {
            delete pointer;
        }
    }
}