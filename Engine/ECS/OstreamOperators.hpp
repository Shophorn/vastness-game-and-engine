/*
Shophorn
Leo Tamminen
Created 18/02/2019
*/

#pragma once

#include "Handle.hpp"
#include <iostream>

namespace std
{
    inline ostream & operator << (ostream & os, const Handle & h)
    {
        os << "[" << h.index << " : " << h.counter << "]";
        return os;
    }
}