/*
Shophorn
Leo Tamminen
Created 17/02/2019
*/

#pragma once

#include <unordered_map>
#include <vector>
#include <cassert>

#include "Handle.hpp"

// Base class for specified storages so we can make heterogeneous container
class ComponentStorage
{
    // todo custom allocation
};

template <typename Component>
class ComponentStorageHandler : public ComponentStorage
{
public:
    std::vector<Component> _data;
};

// Cost typeless container to one with type
template  <typename  Component>
ComponentStorageHandler<Component> * storage_cast(ComponentStorage * storage)
{
    return (ComponentStorageHandler<Component>*)storage;
}

struct ComponentInterface
{
    std::unordered_map<Handle, int> handleMap;
    ComponentStorage * storage;

    bool hasHandle(Handle h)
    {
        return handleMap.find(h) != handleMap.end();
    }

    template <typename Component, typename ... CtorArgs>
    void add(Handle h, CtorArgs ... args)
    {
        auto & data = storage_cast<Component>(storage)->_data;
        int index = (int)data.size();
        data.emplace_back(Component{args...});
        handleMap[h] = index;
    }


    template <typename Component>
    Component & get( Handle h)
    {
        assert (hasHandle(h) && "Invalid handle access");
        int index = handleMap[h];
        return storage_cast <Component> (storage) -> _data [index];
    }

    std::vector<Handle> getHandles()
    {
        std::vector<Handle> handles;
        handles.reserve(handleMap.size());
        for (auto h : handleMap)
            handles.emplace_back(h.first);
        return handles;
    }
};