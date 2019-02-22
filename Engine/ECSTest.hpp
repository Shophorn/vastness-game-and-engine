/*
LeoTamminen
Created 22/02/2019
*/

#pragma once

#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "Input.hpp"
#include "Rendering/RendererSystem.hpp"

namespace test
{
    struct playerControl
    {
        float speed = 1.0f;
    };

    struct playerControlSystem
    {
        using components = mtl::List<transform, playerControl>;

        void update(transform & tr, playerControl & pl, float deltaTime)
        {
            tr.position.x += core::input.horizontal() * deltaTime * pl.speed;
            tr.position.y += core::input.vertical() * deltaTime * pl.speed;
        }
    };

    struct followEntity
    {
        Handle handle;
        float speed{};
    };

    struct followEntitySystem
    {
        using components = mtl::List<followEntity, transform>;

        void update(const followEntity & fe, transform & tr, float dt)
        {
            vector3f target = core::ecs.getComponent<transform>(fe.handle).position;
            vector3f movement = target - tr.position;
            float m = magnitude(movement);
            if (m > 1.0)
                movement /= m;
            tr.position += fe.speed * dt * movement;
        }
    };
    
    
    inline void testECS()
    {
        using core::ecs;

        // move component registering to system registering, maybe
        ecs.registerComponent<playerControl>();
        ecs.registerComponent<renderer>();
        ecs.registerComponent<transform>();
        ecs.registerComponent<followEntity>();

        ecs.registerSystem<playerControlSystem>();
        ecs.registerSystem<rendererSystem>();
        ecs.registerSystem<followEntitySystem>();

//#define TEST
#if defined TEST
        int testCount = 1000;

    std::vector<Handle> handles;
    handles.reserve(testCount);

    for (int i = 0; i < testCount; i++)
    {
        handles[i] = ecs.createEntity();
        ecs.addComponent<transform>(handles[i]);
        ecs.addComponent<renderer>(handles[i]);
    }
#endif
        Handle player = ecs.createEntity();
        ecs.addComponent<playerControl>(player);
        ecs.addComponent<transform>(player);
        ecs.addComponent<renderer>(player);

        Handle e1 = ecs.createEntity();
        ecs.addComponent<transform>(e1, vector3f(0), vector3f(1), vector3f(0.5));
        ecs.addComponent<renderer>(e1);
        ecs.addComponent<followEntity>(e1, player, 0.1f);

        Handle e2 = ecs.createEntity();
        ecs.addComponent<transform>(e2, vector3f(2, 0 ,0), vector3f(1), vector3f(0.5));
        ecs.addComponent<renderer>(e2);
        ecs.addComponent<followEntity>(e2, e1, 0.1f);
    }
}
