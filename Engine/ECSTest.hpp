/*
LeoTamminen
Created 22/02/2019
*/

#pragma once

#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "Input.hpp"
#include "Rendering/RendererSystem.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "AssetLoader.hpp"

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

        GLuint playerTexture;
        loader::LoadTextureRGBA("Game/Assets/bricks.png", &playerTexture);
        int shaderHandle = core::renderManager.getShaderHandle("sprite");

        static Mesh mesh;
        static Mesh mesh2;

        loader::LoadMeshAsset("Assets/Cube.obj", &mesh);
        mesh.generateAndBindBuffers(core::renderManager.getShader(shaderHandle).id);

        Handle player = ecs.createEntity();
        ecs.addComponent<playerControl>(player);
        ecs.addComponent<transform>(player);
        ecs.addComponent<renderer>(player, mesh.vao(), playerTexture, mesh.elementCount(), shaderHandle);

        loader::LoadMeshAsset("Assets/fish_a.obj", &mesh2);
        shaderHandle = core::renderManager.getShaderHandle("sprite");
        mesh2.generateAndBindBuffers(core::renderManager.getShader(shaderHandle).id);
        GLuint fishTexture;
        loader::LoadTextureRGBA("Assets/Fish_A_ColorRGB_SmoothA.png", &fishTexture);

        Handle e1 = ecs.createEntity();
        ecs.addComponent<transform>(e1, transform{vector3f(0), vector3f(1), vector3f(1)});
        ecs.addComponent<renderer>(e1, mesh2.vao(), fishTexture, mesh2.elementCount(), shaderHandle);
        ecs.addComponent<followEntity>(e1, player, 0.1f);

        shaderHandle = core::renderManager.getShaderHandle("default");
        mesh2.generateAndBindBuffers(core::renderManager.getShader(shaderHandle).id);

        Handle e2 = ecs.createEntity();
        ecs.addComponent<transform>(e2, vector3f(2, 0 ,0), vector3f(1), vector3f(1));
        ecs.addComponent<renderer>(e2, mesh2.vao(), 0, mesh2.elementCount(), shaderHandle);
        ecs.addComponent<followEntity>(e2, e1, 0.1f);
    }
}
