/*
Leo Tamminen
Created 20/01/2019
*/

#pragma once

#include "../StringOperations.hpp"

namespace Engine::Collections
{
    using namespace StringOperations;

    template <typename T>
    class Dictionary
    {
    private:
        int _capacity;
        int _count;
        const char ** _keys;
        T * _values;

        // Return index of key, or -1 if not present
        int GetIndex(const char * key)
        {
            for (int i = 0; i < _count; i++)
            {
                if (equals(key, _keys[i]))
                {
                    return i;
                }
            }
            return -1;
        }

    public:
        Dictionary(int capacity = 4)
        {
            _capacity = capacity;
            _count = 0;
            _keys = new const char * [_capacity];
            _values = new T [_capacity];

            for (int i = 0; i < _capacity; i++)
            {
                _keys[i] = nullptr;
            }
        }

        ~Dictionary()
        {
            delete [] _keys;
            delete [] _values;
        }

        T& operator [] (const char * key)
        {
            int index = GetIndex(key);
            return _values[index];
        }

        T* begin() { return _values; }
        T * end() { return _values + _count; }

        bool ContainsKey(const char * key)
        {
            // GetIndex returns negative if it does not find entry
            return GetIndex(key) >= 0;
        }

        void Add(const char * key, T value)
        {
            if (_count == _capacity)
            {
                // add more pointers
                _capacity *= 2;

                const char ** newKeys = new const char * [_capacity];
                T * newValues = new T [_capacity];

                for (int i = 0; i < _count; i++)
                {
                    newKeys [i] = _keys[i];
                    newValues[i] = _values[i];
                }

                for (int i = _count; i < _capacity; i++)
                {
                    newKeys[i] = nullptr;
                }

                delete [] _keys;
                delete [] _values;

                _keys = newKeys;
                _values = newValues;
            }

            _keys[_count] = key;
            _values[_count] = value;

            _count++;
        }

        void Remove(const char * key)
        {
            int index = GetIndex(key);
            if (index >= 0)
            {
                _count--;

                if (index < _count)
                {
                    _keys[index] = _keys[_count];
                    _values[index] = _values[_count];
                }

                _keys [_count] = nullptr;
            }
        }

    };

}