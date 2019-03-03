/*
Shophorn
Leo Tamminen
Created 07/02/2019
*/

#pragma once

#include <rapidjson/document.h>
#include <cassert>
#include <functional>

#include "ECS.hpp"

class EcsDeserializer;

namespace serialization
{
    using Value = rapidjson::Value;

    template <typename T>
    T deserialize(const Value & value);

    using AddDeserializedComponentFunction = std::function< void (Handle, const serialization::Value&)>;

    template <typename Component>
    void addDeserializedComponent (Handle entity, const serialization::Value & value)
    {
        core::ecs.addComponent<Component>(entity, serialization::deserialize<Component>(value));
    }

    // like what
    inline EcsDeserializer * ecsDeserializer;
}





