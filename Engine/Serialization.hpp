/*
Shophorn
Leo Tamminen
Created 07/02/2019
*/

#pragma once

#include <cassert>
#include <functional>

#include "ECS.hpp"

#include "FileOperations.hpp"

class SceneLoader;

namespace serialization
{
    using Value = fileOps::JsonDocument::ValueType;

    template <typename T>
    T deserialize(const Value & value);

    using AddDeserializedComponentFunction = std::function< void (Handle, const serialization::Value&)>;

    template <typename Component>
    void addDeserializedComponent (Handle entity, const serialization::Value & value)
    {
        core::ecs.addComponent<Component>(entity, serialization::deserialize<Component>(value));
    }


    // this is used to get mapped entities from scene file, so that serialized references could work
    // probably not the best
    inline SceneLoader * sceneLoader;

    template <typename T>
    void setIfHasMember(T * target, const char * name, const Value & value)
    {
        if (value.HasMember(name))
            *target = value[name].Get<T>();
    }
}





