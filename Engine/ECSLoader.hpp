/*
LeoTamminen
Created 22/02/2019
*/

#pragma once

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>

#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "Input.hpp"
#include "Rendering/RendererSystem.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Loader.hpp"
#include "ResourceManager.hpp"
#include "FileOperations.hpp"
#include "Serialization.hpp"

#include "Resources/Textures.hpp"
#include "Resources/Shaders.hpp"
#include "Resources/Meshes.hpp"

namespace ECSLoader
{
    struct TEST_PlayerControl
    {
        float speed = 1.0f;
    };

    struct TEST_PlayerControlSystem
    {
        using components = mpl::List<transform, TEST_PlayerControl>;

        void update(transform & tr, TEST_PlayerControl & pl, float deltaTime)
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
        using components = mpl::List<followEntity, transform>;

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

    struct material
    {
        GLuint texture;
        GLuint shader;
    };

    template <typename Component>
    void addComponent (Handle entity, const serialization::Value & value)
    {
       core::ecs.addComponent<Component>(entity, serialization::deserialize<Component>(value));
    }

    inline void build()
    {
        using std::string;
        using std::unordered_map;
        using rapidjson::Document;

        string gamePath = "Game/game.json";
        Document document = fileOps::ReadJson(gamePath.c_str());

        unordered_map<string, string> meshPaths;
        auto jsonMeshArray = document["Meshes"].GetArray();
        for (const auto & meshItem : jsonMeshArray)
        {
            auto obj = meshItem.GetObject();
            auto name = obj["name"].GetString();
            auto path = obj["path"].GetString();
            meshPaths.emplace(name, path);
        }

        resources::textures.addLoadInfo(document["Textures"]);
        resources::shaders.addLoadInfo(document["Shaders"]);
        resources::meshes.addLoadInfo(document["Meshes"]);

        using core::ecs;
        ecs.registerComponent<transform>();
        ecs.registerComponent<renderer>();
        ecs.registerComponent<TEST_PlayerControl>();
        ecs.registerComponent<followEntity>();

        ecs.registerSystem<rendererSystem>();
        ecs.registerSystem<TEST_PlayerControlSystem>();
        ecs.registerSystem<followEntitySystem>();

        unordered_map<int, Handle> mappedEntities{};
        auto jsonEntities = document["Entities"].GetArray();
        for (const auto & item : jsonEntities)
        {
            Handle entity = ecs.createEntity();
            auto obj = item.GetObject();
            mappedEntities.emplace(obj["id"].GetInt(), entity);

            for (auto & comp : obj["components"].GetArray())
            {
                string type = comp["type"].GetString();
                if("transform" == type)             { addComponent<transform>(entity, comp); }
                else if ("renderer" == type)        { addComponent<renderer>(entity, comp); }

                else if ("playerControl"== type)   { ecs.addComponent<TEST_PlayerControl>(entity, 1.0); }
                else if ("followEntity" == type)    { ecs.addComponent<followEntity>(entity, mappedEntities[comp["target"].GetInt()], 0.2f); }
            }
        }
    }
}
