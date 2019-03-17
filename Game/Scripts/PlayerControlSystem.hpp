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
    float speed { 1.0f };
};

struct playerControlSystem
{
    using components = mpl::List<transform, playerControl, UserInput>;

    void update(transform & tr, playerControl & pl, const UserInput & input, float dt)
    {
        vector3f inputVector (input.horizontal, input.vertical, 0);

        float length = magnitude(inputVector);

        if (length > 0.0f)
        {
            vector3f forward = inputVector / length;
            tr.rotation = quaternion::lookRotation(inputVector / length, vector3f::up);
        }

        if (length > 1.0f)
        {
            inputVector /= length;
        }
        tr.position += inputVector * dt * pl.speed;
    }
};

namespace serialization
{
    template <>
    inline playerControl deserialize<playerControl>(const Value & value)
    {
        playerControl p{};
        setIfHasMember(&p.speed, "speed", value);
        return p;
    }
}