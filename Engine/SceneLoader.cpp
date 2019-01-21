/*
Leo Tamminen
Created 21/01/2019
*/
#include "SceneLoader.hpp"

#include <rapidjson/document.h>

// STL
#include <unordered_map>
#include <vector>
#include <iostream>

#include "AssetLoader.hpp"
#include "VectorsAndMatrices.hpp"
#include "Collections/Array.hpp"
#include "FileOperations.hpp"

#include "../Game/ActorTypes.hpp"
#include "../Game/FishController.hpp"
#include "../Game/PlayerController.hpp"

using namespace Engine;
using namespace Game;
using namespace Collections;
using std::unordered_map;
using std::string;
using std::vector;

using namespace rapidjson;

namespace
{
    vec3 GetVec3(rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>::ConstArray array)
    {
        vec3 vec(0);
        vec[0] = array[0].GetFloat();
        vec[1] = array[1].GetFloat();
        vec[2] = array[2].GetFloat();

        return vec;
    }

    struct SerializableActor
    {
        ActorType type;
        vec3 position;
        string modelPath;
        string texturePath;
        string shaderName;
    };

    Array<SerializableActor> ParseJsonActors(const Value & jsonActors)
    {
        Array<SerializableActor> actors (jsonActors.Size());

        for (int i = 0; i < jsonActors.Size(); i++)
        {
            auto object = jsonActors[i].GetObject();

            actors[i].type = GetActorType(object["type"].GetString());
            actors[i].position = GetVec3(object["position"].GetArray());
            actors[i].modelPath = object["model"].GetString();
            actors[i].texturePath = object["texture"].GetString();
            actors[i].shaderName = object["shader"].GetString();
        }
        return actors;
    }

    struct SerializableProp
    {
        string modelPath;
        string texturePath;
        string shaderName;

//        Array<vec3> positions;
    };

    Array<SerializableProp> ParseJsonProps(const Value & jsonProps)
    {
        int count = jsonProps.Size();
        Array<SerializableProp> props (count);

        for (int i = 0; i < count; i++)
        {
            auto object = jsonProps[i].GetObject();

            props[i].modelPath = object["model"].GetString();
            props[i].texturePath = object["texture"].GetString();
            props[i].shaderName = object["shader"].GetString();
            auto jsonPositions = object["positions"].GetArray();

            int positionCount = jsonPositions.Size();
            Array<vec3> positions (positionCount);

            for (int ii = 0; ii < positionCount; ii++)
            {
                positions[i] = GetVec3(jsonPositions[ii].GetArray());
            }
        }
        return props;
    }
}

Scene SceneLoader::Load(string path)
{
    using namespace rapidjson;

    const char * jsonFormat = FileOperations::ReadFile(path.c_str());
    Document doc;
    doc.Parse(jsonFormat);

    const Value& jsonActors = doc["Actors"];
    auto actors = ParseJsonActors(jsonActors);
    int count = actors.count();

    const Value & jsonProps = doc["Props"];
    auto props = ParseJsonProps(jsonProps);


    Scene scene;

    scene.camera;
    scene.camera.position = vec3(0.0f, -2.5f, 1.0f);
    // scene.camera.aspectRatio = screen.aspectRatio();

    scene.light = Light(
            glm::normalize(vec3(0.6f,0.6f, 1.0f)),
            vec3(1.0f, 0.98f, 0.95f),
            1.0f
    );

    scene.actors.DiscardAndResize(count);
    scene.renderers.DiscardAndResize(count);
    scene.shaders = unordered_map<string, ShaderProgram>();

    for (int i = 0; i < count; i++)
    {
        string shaderName = actors[i].shaderName;
        if (scene.shaders.find(shaderName) == scene.shaders.end())
        {
            ShaderProgram shader = ShaderProgram::Load(shaderName);
            scene.shaders.insert_or_assign(shaderName, shader);
        }

        Mesh * mesh = new Mesh;
        AssetLoader::LoadOBJ(actors[i].modelPath.c_str(), mesh);
        mesh->LoadToGL(scene.shaders[shaderName].id);

        GLuint texture;
        AssetLoader::LoadTextureRGBA(actors[i].texturePath.c_str(), &texture);

        scene.renderers[i] = new Renderer(Transform(actors[i].position, vec3(0,0,0)), texture, mesh, &scene.shaders[shaderName]);

        // TODO: Move these to game section
        switch (actors[i].type)
        {
            case ActorType::Player:
                PlayerController * player;
                player = new PlayerController(&scene.renderers[i]->transform, 1.5f);
                scene.actors[i] = player;
                break;

            case ActorType::Fish:
                FishController * fish;
                fish = new FishController(&scene.renderers[i]->transform, vec3(0.0f, 90.0f, 0.0f));
                scene.actors[i] = fish;
                break;
        }
    }
    return scene;
}