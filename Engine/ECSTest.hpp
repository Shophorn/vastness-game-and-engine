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

        /*
        load renderer
         1. load mesh
         2. load shader
         3. load textures
         4. construct material
        */

        GLuint playerTexture;
        loader::LoadTextureRGBA("Game/Assets/bricks.png", &playerTexture);

        auto spriteShaderHandle = core::renderManager.getShaderHandle("sprite");
        auto spriteShader = core::renderManager.getShader(spriteShaderHandle);
        auto meshHandle = core::meshes.instantiate("Assets/Cube.obj");
        auto mesh = core::meshes.get(meshHandle);
        setVertexAttributes(mesh, spriteShader);

        Handle player = ecs.createEntity();
        ecs.addComponent<playerControl>(player);
        ecs.addComponent<transform>(player);
        ecs.addComponent<renderer>(player, playerTexture, spriteShaderHandle, meshHandle);

        GLuint fishTexture;
        loader::LoadTextureRGBA("Assets/Fish_A_ColorRGB_SmoothA.png", &fishTexture);

        auto fishMeshHandle = core::meshes.instantiate("Assets/fish_a.obj");
        auto fishMesh = core::meshes.get(fishMeshHandle);
        setVertexAttributes(fishMesh, spriteShader);

        Handle e1 = ecs.createEntity();
        ecs.addComponent<transform>(e1, transform{vector3f(0), vector3f(1), vector3f(1)});
        ecs.addComponent<renderer>(e1, fishTexture, spriteShaderHandle, fishMeshHandle);
        ecs.addComponent<followEntity>(e1, player, 0.1f);


        auto defaultShaderHandle = core::renderManager.getShaderHandle("default");
        auto meshHandle2 = core::meshes.instantiate(fishMeshHandle);
        auto mesh222 = core::meshes.get(meshHandle2);
        setVertexAttributes(mesh222, core::renderManager.getShader(defaultShaderHandle));
        Handle e2 = ecs.createEntity();
        ecs.addComponent<transform>(e2, vector3f(2, 0 ,0), vector3f(1), vector3f(1));
        ecs.addComponent<renderer>(e2, 0, defaultShaderHandle, meshHandle2);
        ecs.addComponent<followEntity>(e2, e1, 0.1f);

        auto e3 = ecs.createEntity();
        ecs.addComponent<transform>(e3, vector3f(3, 0, 0),vector3f(0), vector3f(1));
        ecs.addComponent<renderer>(e3, fishTexture, spriteShaderHandle, fishMeshHandle);
        ecs.addComponent<followEntity>(e3, e2, 0.1f);
    }

    struct textureLoadInfo
    {
        constexpr static int RGBA = 0;
        constexpr static int RGB = 1;

        std::string path;
        int colorMode = RGBA;

        std::string toString()
        {
            return "[" + path + ", mode: " + (colorMode == RGBA ? "RGBA" : colorMode == RGB ? "RGB" : "none") + "]";
        }
    };

    struct material
    {
        GLuint texture;
        GLuint shader;
    };


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

        unordered_map<string, textureLoadInfo> texLoadInfos;
        auto jsonTextureArray = document["Textures"].GetArray();
        for (const auto & item : jsonTextureArray)
        {
            auto obj = item.GetObject();
            auto name = obj["name"].GetString();
            textureLoadInfo info;
            info.path = obj["path"].GetString();

            string colorModeStr = obj["color mode"].GetString();
            if (colorModeStr == "RGBA")
                info.colorMode = textureLoadInfo::RGBA;
            else if (colorModeStr == "RGB")
                info.colorMode = textureLoadInfo::RGB;

            texLoadInfos.emplace(name, info);
        }

        unordered_map<string, string> shaderPaths;
        auto jsonShaderArray = document["Shaders"].GetArray();
        for (const auto & item : jsonShaderArray)
        {
            auto obj = item.GetObject();
            auto name = obj["name"].GetString();
            auto path = obj["path"].GetString();
            shaderPaths.emplace(name, path);
        }

        auto getLoadedMesh = [&meshPaths] (std::string name)
        {
            auto path = meshPaths[name];
            return core::meshes.instantiate(path);
        };

        auto getLoadedShader = [&shaderPaths] (std::string name)
        {
            auto path = shaderPaths[name];
            return core::renderManager.getShaderHandle(path);
        };

        auto getLoadedTexture = [&texLoadInfos] (std::string name)
        {
            auto path = texLoadInfos[name].path;
            GLuint tex;
            loader::LoadTextureRGBA(path.c_str(), &tex);
            return tex;
        };

        using core::ecs;
        ecs.registerComponent<transform>();
        ecs.registerComponent<renderer>();
        ecs.registerComponent<playerControl>();
        ecs.registerComponent<followEntity>();

        ecs.registerSystem<rendererSystem>();
        ecs.registerSystem<playerControlSystem>();
        ecs.registerSystem<followEntitySystem>();

        unordered_map<int, Handle> jsonMappedEntities{};
        auto jsonEntities = document["Entities"].GetArray();
        for (const auto & item : jsonEntities)
        {
            auto obj = item.GetObject();
            Handle entity = ecs.createEntity();
            jsonMappedEntities.emplace(obj["id"].GetInt(), entity);

            for (auto & comp : obj["components"].GetArray())
            {
                string type = comp["type"].GetString();
                if("transform" == type)
                {
                    ecs.addComponent<transform>(entity, serialization::deserialize<transform>(comp));
                }
                else if ("renderer" == type)
                {
                    GLuint loadedTex = getLoadedTexture(comp["texture"].GetString());
                    auto meshHandle = getLoadedMesh(comp["mesh"].GetString());
                    auto shaderHandle = getLoadedShader(comp["shader"].GetString());

                    setVertexAttributes(core::meshes.get(meshHandle), core::renderManager.getShader(shaderHandle));

                    ecs.addComponent<renderer>(entity, loadedTex, shaderHandle, meshHandle);
                }
                else if ("playerControl" == type)
                {
                    ecs.addComponent<playerControl>(entity, 1.0);
                }
                else if ("followEntity" == type)
                {
                    int targetId = comp["target"].GetInt();
                    ecs.addComponent<followEntity>(entity, jsonMappedEntities[targetId], 0.2f);
                }
            }
        }
    }
}
