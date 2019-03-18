/*
Shophorn Games
Leo Tamminen
Created 28/02/2019
*/

#pragma once

#include "../../Engine/Maths/Maths.hpp"
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
    using components = mpl::List<transform, playerControl, UserInput, CameraController3rdPerson>;

    void update(transform & tr, playerControl & pl, const UserInput & input, const CameraController3rdPerson & camera, float dt)
    {
        vector3f inputVector {input.horizontal, input.vertical, 0};

        float length = magnitude(inputVector);


        if (length > 1.0f)
        {
            inputVector /= length;
        }

        auto camRotation = quaternion::axisAngle(vector3f::up, camera.orbit);

        vector3f motion = 
            camRotation * vector3f::forward * inputVector.y 
            + camRotation * vector3f::right * inputVector.x;

        tr.position += motion * dt * pl.speed;

        if (length > 0.0f)
        {
            tr.rotation = quaternion::lookRotation(normalize(motion), vector3f::up);
        }
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