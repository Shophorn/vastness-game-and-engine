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
#include "Camera.hpp"

#include "../Game/ActorTypes.hpp"
#include "../Game/FishController.hpp"
#include "../Game/PlayerController.hpp"
#include "Screen.hpp"

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
        Transform transform;
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

            if (object.HasMember("transform"))
            {
                auto jsonTransform = object["transform"].GetObject();
                actors[i].transform = Transform(
                    GetVec3(jsonTransform["position"]),
                    GetVec3(jsonTransform["rotation"]),
                    GetVec3(jsonTransform["scale"])
                );
            }
            else if (object.HasMember("position"))
            {
                actors[i].transform = Transform(GetVec3(object["position"]), vec3(0), vec3(1));
            }


            actors[i].modelPath = object["model"].GetString();
            actors[i].texturePath = object["texture"].GetString();
            actors[i].shaderName = object["shader"].GetString();
        }
        return actors;
    }

    class SerializableScenery
    {
    public:
//        Array<vec3> positions;
        Array<Transform> transforms;
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

            Array<Transform> transforms;

            auto transformsArray = object["transforms"].GetArray();
            int transformCount = transformsArray.Size();

            transforms = Array<Transform>(transformCount);

            for (int ii = 0; ii < transformCount; ii++)
            {
                auto jsonTransform = transformsArray[ii].GetObject();
                transforms[ii] = Transform
                (
                    GetVec3(jsonTransform["position"]),
                    GetVec3(jsonTransform["rotation"]),
                    GetVec3(jsonTransform["scale"])
                );
            }

            sceneries[i].transforms = transforms;
            sceneries[i].modelPath = object["model"].GetString();
            sceneries[i].texturePath = object["texture"].GetString();
            sceneries[i].shaderName = object["shader"].GetString();

        }
        return sceneries;
    }

    SerializebleAnimationAtlas ParseJsonAnimation(const Value & animationObject)
    {
        SerializebleAnimationAtlas atlas;
        atlas.frameRate = animationObject["frame rate"].GetFloat();
        atlas.texturePath = animationObject["texture"].GetString();//"Game/Assets/astronaut_2x1.png";
        atlas.rows = animationObject["rows"].GetInt();
        atlas.columns = animationObject["columns"].GetInt();

//        SerializableAnimation idleAnimation;
//        idleAnimation.frameCount = animationObject["animations"].GetArray()[0].GetObject()["frames"].GetInt();
//        idleAnimation.name = animationObject["animations"].GetArray()[0].GetObject()["name"].GetString();
//
//        atlas.animations = Array<SerializableAnimation> {idleAnimation};

        auto animationsArray = animationObject["animations"].GetArray();
        int animationsCount = animationsArray.Size();
        atlas.animations = Array<SerializableAnimation>(animationsCount);
        for (int i = 0; i < animationsCount; i++)
        {
            auto animation = animationsArray[i].GetObject();
            atlas.animations[i].name = animation["name"].GetString();
            atlas.animations[i].frameCount = animation["frames"].GetInt();
        }


        return atlas;
    }
}

Scene SceneLoader::Load(const char * path)
{
    using namespace rapidjson;

    Document document = FileOperations::ReadJson(path);

    const Value& jsonActors = document["Actors"];
    auto actors = ParseJsonActors(jsonActors);
    int actorCount = actors.count();

    const Value & jsonScenery = document["Scenery"];
    auto sceneries = ParseJsonSceneries(jsonScenery);
    int sceneryCount = sceneries.count();

    int sceneryRenderersCount = 0;
    for (int i = 0; i <sceneries.count(); i++)
    {
        sceneryRenderersCount += sceneries[i].transforms.count();
    }

    Scene scene;

    const Value & cameraValue = document["Camera"];
    scene.camera = Camera(
            GetVec3(cameraValue["position"]),
            GetVec3(cameraValue["target"]),
            cameraValue["field of view"].GetFloat(),
            cameraValue["near clipping plane"].GetFloat(),
            cameraValue["far clipping plane"].GetFloat(),
            GetVec3(cameraValue["clear color"])
    );

    const Value & jsonLight = document["Light"];
    scene.light = Light(
        GetVec3(jsonLight["direction"]),
        GetVec3(jsonLight["color"]),
        jsonLight["intensity"].GetFloat()
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
            actors[i].transform,
            texture,
            mesh,
            &scene.shaders[shaderName]
        );

        // TODO: Move these to game section
        switch (actors[i].type)
        {
            case ActorType::Player:
            {
                PlayerController *player;
                player = new PlayerController(&scene.renderers[i]->transform, 1.5f);


                auto animationObject = document["Sprites"].GetArray()[0].GetObject();

                SpriteAnimator *animator = new SpriteAnimator(
                    scene.shaders[shaderName].id,
                    ParseJsonAnimation(animationObject)
                );

                scene.renderers[i]->animator = animator;
                player->animator = animator;
                scene.actors[actorIndex] = player;
                actorIndex++;
            }
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

        for (int ii = 0; ii < sceneries[i].transforms.count(); ii++)
        {
            scene.renderers[rendererIndex] = new Renderer(
                    sceneries[i].transforms[ii],
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

Screen SceneLoader::LoadContext(const char * path)
{
    using namespace rapidjson;

    Document document = FileOperations::ReadJson(path);

    const Value & context = document ["Context"].GetObject();

    auto screenSize = context["window"].GetArray();

    return Screen::Create(
        context["title"].GetString(),
        screenSize[0].GetInt(),
        screenSize[1].GetInt()
    );

}
