/*
LeoTamminen
Created 22/02/2019
*/

#pragma once

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <unordered_map>
#include <memory>

#include "ECS.hpp"
#include "FileOperations.hpp"
#include "Serialization.hpp"

#include "Resources/Textures.hpp"
#include "Resources/Shaders.hpp"
#include "Resources/Meshes.hpp"
#include "Rendering/RenderManager.hpp"

class SceneLoader
{
    using deserializeMap = std::unordered_map<std::string, serialization::AddDeserializedComponentFunction>;
    deserializeMap _deserializers;

    std::unordered_map<int, Handle> _mappedEntities{};
public:

    Handle getMappedHandle(int index)
    {
        assert (_mappedEntities.find(index) != _mappedEntities.end() && "Entity not yet loaded");
        return _mappedEntities[index];
    }

    void registerDeserializers(const deserializeMap & newDeserializers)
    {
        for (auto pair : newDeserializers)
        {
            _deserializers.emplace(pair);
        }
    }

    void build()
    {
        serialization::sceneLoader = this;

        using std::string;
        using std::unordered_map;
        using rapidjson::Document;

        string gamePath = "Game/game.json";
        Document document = fileOps::ReadJson(gamePath.c_str());

        // Cache load info, but only load assets on first usage
        resources::textures.addLoadInfo(document["Textures"]);
        resources::shaders.addLoadInfo(document["Shaders"]);
        resources::meshes.addLoadInfo(document["Meshes"]);

        core::renderManager.lighting.addSerializedLighting(document["Lighting"]);


        auto jsonEntities = document["Entities"].GetArray();
        for (const auto & item : jsonEntities)
        {
            Handle entity = core::ecs.createEntity();
            auto obj = item.GetObject();
            _mappedEntities.emplace(obj["id"].GetInt(), entity);

            for (auto & comp : obj["components"].GetArray())
            {
                string type = comp["type"].GetString();

                if (_deserializers.find(type) != _deserializers.end())
                   _deserializers[type](entity, comp);

            }
        }

        serialization::sceneLoader = nullptr;
    }
};
