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
    vec3 GetVec3(const Value & vec3Array)
    {
        auto array = vec3Array.GetArray();

        return vec3 (
            array[0].GetFloat(),
            array[1].GetFloat(),
            array[2].GetFloat()
        );
    }

    class SerializableActor
    {
    public:
        ActorType type;
        vec3 position;
        string modelPath;
        string texturePath;
        string shaderName;
    };

    Array<SerializableActor> ParseJsonActors(const Value &jsonActors)
    {
        Array<SerializableActor> actors(jsonActors.Size());

        for (int i = 0; i < jsonActors.Size(); i++)
        {
            auto object = jsonActors[i].GetObject();

            actors[i].type = GetActorType(object["type"].GetString());
            actors[i].position = GetVec3(object["position"]);
            actors[i].modelPath = object["model"].GetString();
            actors[i].texturePath = object["texture"].GetString();
            actors[i].shaderName = object["shader"].GetString();
        }
        return actors;
    }

    class SerializableScenery
    {
    public:
        Array<vec3> positions;
        string modelPath;
        string texturePath;
        string shaderName;
    };

    Array<SerializableScenery> ParseJsonSceneries(const Value & jsonScenery)
    {
        int count = jsonScenery.Size();
        Array<SerializableScenery> sceneries(count);

        for (int i = 0; i < count; i++)
        {
            auto object = jsonScenery[i].GetObject();

            auto positionsArray = object["positions"].GetArray();
            int positionCount = positionsArray.Size();
            Array<vec3> positions (positionCount);

            for (int ii = 0; ii < positionCount; ii++)
            {
                positions[ii] = GetVec3(positionsArray[ii]);
            }

            sceneries[i].positions = positions;
            sceneries[i].modelPath = object["model"].GetString();
            sceneries[i].texturePath = object["texture"].GetString();
            sceneries[i].shaderName = object["shader"].GetString();

        }
        return sceneries;
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
    int actorCount = actors.count();

    const Value & jsonScenery = doc["Scenery"];
    auto sceneries = ParseJsonSceneries(jsonScenery);
    int sceneryCount = sceneries.count();

    int sceneryRenderersCount = 0;
    for (int i = 0; i <sceneries.count(); i++)
    {
        sceneryRenderersCount += sceneries[i].positions.count();
    }

    Scene scene;

    scene.camera.position = vec3(0.0f, -2.5f, 1.0f);
    // scene.camera.aspectRatio = screen.aspectRatio();

    scene.light = Light(
            glm::normalize(vec3(0.6f,0.6f, 1.0f)),
            vec3(1.0f, 0.98f, 0.95f),
            1.0f
    );

    scene.actors.DiscardAndResize(actorCount);

    int rendererCount = actorCount + sceneryRenderersCount;
    scene.renderers.DiscardAndResize(rendererCount);

    scene.shaders = unordered_map<string, ShaderProgram>();


    // Build Actors
    int actorIndex = 0;
    for (int i = 0; i < actorCount; i++)
    {
        string shaderName = actors[i].shaderName;
        scene.LoadShaderIfNotLoader(shaderName);

        Mesh * mesh = new Mesh;
        AssetLoader::LoadOBJ(actors[i].modelPath.c_str(), mesh);
        mesh->LoadToGL(scene.shaders[shaderName].id);

        GLuint texture;
        AssetLoader::LoadTextureRGBA(actors[i].texturePath.c_str(), &texture);

        scene.renderers[i] = new Renderer(
            Transform(actors[i].position, vec3(0,0,0)),
            texture,
            mesh,
            &scene.shaders[shaderName]
        );

        // TODO: Move these to game section
        switch (actors[i].type)
        {
            case ActorType::Player:
                PlayerController * player;
                player = new PlayerController(&scene.renderers[i]->transform, 1.5f);
                scene.actors[actorIndex] = player;
                actorIndex++;
                break;

            case ActorType::Fish:
                FishController * fish;
                fish = new FishController(&scene.renderers[i]->transform, vec3(0.0f, 90.0f, 0.0f));
                scene.actors[actorIndex] = fish;
                actorIndex++;
                break;

        }

    }

    int rendererIndex = actorCount;
    for (int i = 0; i < sceneryCount; i++)
    {
        string shaderName = sceneries[i].shaderName;
        scene.LoadShaderIfNotLoader(shaderName);

        Mesh * mesh = new Mesh;
        AssetLoader::LoadOBJ(sceneries[i].modelPath.c_str(), mesh);
        mesh->LoadToGL(scene.shaders[shaderName].id);

        GLuint texture;
        AssetLoader::LoadTextureRGBA(sceneries[i].texturePath.c_str(), &texture);

        for (int ii = 0; ii < sceneries[i].positions.count(); ii++)
        {
            scene.renderers[rendererIndex] = new Renderer(
                    Transform(sceneries[i].positions[ii], vec3(0)),
                    texture,
                    mesh,
                    &scene.shaders[shaderName]
            );
            rendererIndex++;
        }
    }
    scene.actors.TrimDownToSize(actorIndex);
    return scene;
}