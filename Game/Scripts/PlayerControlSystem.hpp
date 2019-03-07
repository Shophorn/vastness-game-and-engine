/*
Shophorn Games
Leo Tamminen
Created 28/02/2019
*/

#pragma once

#include "../../Engine/ECS.hpp"
#include "../../Engine/EcsCoreComponents.hpp"
#include "../../Engine/Input.hpp"
#include "../../Engine/Serialization.hpp"
#include "../../Engine/DEBUG.hpp"

struct playerControl
{
    float speed = 1.0f;
};

struct playerControlSystem
{
    using components = mpl::List<transform, playerControl>;

    void update(transform & tr, playerControl & pl, float dt)
    {
        vector3f input (core::input.horizontal(), core::input.vertical(), 0);

        float length = magnitude(input);

        if (length > 0.0f)
        {
            vector3f forward = input / length;
            tr.rotation = lookRotation(input / length, vector3f::up);
        }

        if (length > 1.0f)
        {
            input /= length;
        }
        tr.position += input * dt * pl.speed;
    }
};

namespace serialization
{
    template <>
    inline playerControl deserialize<playerControl>(const Value & value)
    {
        playerControl p{};
        if (value.HasMember("speed"))
        {
            p.speed = value ["speed"].GetFloat();
        }
        return p;
    }
}