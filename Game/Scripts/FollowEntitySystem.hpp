/*
Shophorn Games
Leo Tamminen
Created 03/03/2019
*/

#include "../../Engine/ECS.hpp"
#include "../../Engine/EcsCoreComponents.hpp"
#include "../../Engine/Serialization.hpp"

struct followEntity
{
    Handle targetHandle;
    float speed{0.5f};
};

struct followEntitySystem
{
    using components = mpl::List<followEntity, transform>;

    void update(const followEntity & fe, transform & tr, float dt)
    {
        vector3f target = core::ecs.getComponent<transform>(fe.targetHandle).position;
        vector3f movement = target - tr.position;
        float m = magnitude(movement);
        if (m > 1.0)
            movement /= m;
        tr.position += fe.speed * dt * movement;
        tr.rotation.y += 90 * dt;
    }
};

namespace serialization
{
    template <>
    inline followEntity deserialize<followEntity>(const Value & value)
    {
        followEntity p{};
        if (value.HasMember("speed"))
        {
            p.speed = value ["speed"].GetFloat();
        }

        int targetIndex = value["target"].GetInt();
        p.targetHandle = serialization::ecsDeserializer->getMappedHandle(targetIndex);
        return p;
    }
}
