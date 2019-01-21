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
        int _count;
        T *_values;

    public:
        Array() : _count(0), _values(nullptr) {}
        explicit Array(int count) : _count(count), _values(new T[count]) {}

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

        Array<T> &  operator = (const Array<T> & other)
        {
            if (this == &other)
                return *this;

            _count = other._count;

            delete [] _values;
            _values = new T [_count];

            for (int i = 0; i < _count; i++)
            {
                _values[i] = other._values[i];
            }

            return *this;
        }

        T& operator[](int index) { return _values[index]; }

        int count() { return _count; }

        // Range based for loop
        T * begin() { return _values; }
        T * end() { return _values + _count; }

        void DiscardAndResize(int count)
        {
            delete [] _values;
            _count = count;
            _values = new T [count];
        }

        void TrimDownToSize(int size)
        {
            if (size >= _count)
                return;

            _count = size;
            T * trimmedValues = new T [_count];

            for (int i = 0; i < size; i++)
            {
                trimmedValues[i] = _values[i];
            }

            delete [] _values;
            _values = trimmedValues;
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