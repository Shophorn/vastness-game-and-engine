/*
Shophorn Games
Leo Tamminen
Created 28/02/2019
*/

#pragma once

#include "../../Engine/ECS.hpp"
#include "../../Engine/Input.hpp"
#include "../../Engine/Serialization.hpp"

struct playerControl
{
    float speed = 1.0f;
};

struct playerControlSystem
{
    using components = mtl::List<transform, playerControl>;

    void update(transform & tr, playerControl & pl, float dt)
    {
        tr.position.x += core::input.horizontal() * dt * pl.speed;
        tr.position.y += core::input.vertical() * dt * pl.speed;
    }
};

namespace serialization
{
    template <>
    playerControl deserialize<playerControl>(const Value & value)
    {
        playerControl p{};
        if (value.HasMember("speed"))
        {
            p.speed = value ["speed"].GetFloat();
        }
        return p;
    }
}