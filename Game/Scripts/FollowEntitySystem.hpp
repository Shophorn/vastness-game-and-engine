/*
Shophorn Games
Leo Tamminen
Created 03/03/2019
*/

#pragma once

#include "../../Engine/ECS.hpp"
#include "../../Engine/EcsCoreComponents.hpp"
#include "../../Engine/Serialization.hpp"

struct followEntity
{
    Handle targetHandle;
    float speed {0.5f};
};

struct followEntitySystem
{
    using components = mpl::List<followEntity, transform>;

    void update(const followEntity & fe, transform & tr, float dt)
    {
        vector3f target = core::ecs.getComponent<transform>(fe.targetHandle).position;
        vector3f movement = target - tr.position;
        float m = magnitude(movement);

        vector3f forward = movement / m;
        tr.rotation = lookRotation(forward, vector3f::up);

        if (m > 1.0)
            movement /= m;
        tr.position += fe.speed * dt * movement;
    }
};

namespace serialization
{
    template <>
    inline followEntity deserialize<followEntity>(const Value & value)
    {
        followEntity p{};
            
        setIfHasMember(&p.speed, "speed", value);

        // ASSERT_HAS_FIELD(target)
        p.targetHandle = sceneLoader->getMappedHandle(value["target"].GetInt());
        return p;
    }
}
