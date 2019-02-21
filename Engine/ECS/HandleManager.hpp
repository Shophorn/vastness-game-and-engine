/*
Shophorn
Leo Tamminen
Created 18/02/2019
*/
#pragma once

#include <vector>

#include "Handle.hpp"

class HandleManager
{
public:
    std::vector<Handle> handles;

    // todo: make pool of these, and on each reuse, handles counter gets increased

    Handle create ()
    {
        Handle h (handles.size(), 0);
        handles.emplace_back(h);
        return h;
    }
};