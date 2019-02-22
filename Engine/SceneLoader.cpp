/*
Leo Tamminen
Created 21/01/2019
*/
#include "SceneLoader.hpp"
#include "Serialization.hpp"

// STL
#include <unordered_map>
#include <vector>
#include <iostream>

#include "AssetLoader.hpp"
#include "FileOperations.hpp"
#include "Camera.hpp"

#include "../Game/EntityTypes.hpp"
#include "../Game/PlayerController.hpp"
#include "Screen.hpp"

using namespace Core;
using namespace Game;

using std::unordered_map;
using std::string;
using std::vector;

using namespace rapidjson;

namespace keywords
{
    const char * entities = "Entities";
}

namespace
{
    vector3f GetVec3(const Value & vec3Array)
    {
        auto array = vec3Array.GetArray();

        return vector3f (
            array[0].GetFloat(),
            array[1].GetFloat(),
            array[2].GetFloat()
        );
    }

    class SerializableEntity
    {
    public:
        EntityType type;
        Transform transform;
        string modelPath;
        string texturePath;
        string shaderName;
    };

    vector<SerializableEntity> ParseJsonEntities(const Value &jsonEntities)
    {
        vector<SerializableEntity> entities(jsonEntities.Size());

        for (int i = 0; i < jsonEntities.Size(); i++)
        {
            auto object = jsonEntities[i].GetObject();

            entities[i].type = GetEntityType(object["type"].GetString());

            if (object.HasMember("transform"))
            {
                auto jsonTransform = object["transform"].GetObject();
                entities[i].transform = Transform(
                    GetVec3(jsonTransform["position"]),
                    GetVec3(jsonTransform["rotation"]),
                    GetVec3(jsonTransform["scale"])
                );
            }
            else if (object.HasMember("position"))
            {
                entities[i].transform = Transform(GetVec3(object["position"]), vector3f(0), vector3f(1));
            }

            entities[i].modelPath = object["model"].GetString();
            entities[i].texturePath = object["texture"].GetString();
            entities[i].shaderName = object["shader"].GetString();
        }
        return entities;
    }

    class SerializableScenery
    {
    public:
//        vector<vec3> positions;
        vector<Transform> transforms;
        string modelPath;
        string texturePath;
        string shaderName;
    };

    vector<SerializableScenery> ParseJsonSceneries(const Value & jsonScenery)
    {

        int count = jsonScenery.Size();
        vector<SerializableScenery> sceneries(count);

        for (int i = 0; i < count; i++)
        {
            auto object = jsonScenery[i].GetObject();

            vector<Transform> transforms;

            auto transformsArray = object["transforms"].GetArray();
            int transformCount = transformsArray.Size();

            transforms = vector<Transform>(transformCount);

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


        auto animationsArray = animationObject["animations"].GetArray();
        int animationsCount = animationsArray.Size();
        atlas.animations = vector<SerializableAnimation>(animationsCount);
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

    const Value& jsonEntities = document[keywords::entities];
    auto entities = ParseJsonEntities(jsonEntities);
    int entityCount = entities.size();

    const Value & jsonScenery = document["Scenery"];
    auto sceneries = ParseJsonSceneries(jsonScenery);
    int sceneryCount = sceneries.size();

    int sceneryRenderersCount = 0;
    for (int i = 0; i <sceneries.size(); i++)
    {
        sceneryRenderersCount += sceneries[i].transforms.size();
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

//    scene.entities.reserve(entityCount);

    int rendererCount = entityCount + sceneryRenderersCount;
    scene.renderers.reserve(rendererCount);


//    // Build Entities
//    int entityIndex = 0;
//    for (int i = 0; i < entityCount; i++)
//    {
//        string shaderName = entities[i].shaderName;
//        scene.LoadShaderIfNotLoader(shaderName);
//
//        Mesh * mesh = new Mesh;
//        AssetLoader::LoadOBJ(entities[i].modelPath.c_str(), mesh);
//        mesh->LoadToGL(scene.shaders[shaderName].id);
//
//        GLuint texture;
//        AssetLoader::LoadTextureRGBA(entities[i].texturePath.c_str(), &texture);
//
//        scene.renderers[i] = new Renderer(
//            entities[i].transform,
//            texture,
//            mesh,
//            &scene.shaders[shaderName]
//        );
//
//
//        // TODO: Move these to game section
//        switch (entities[i].type)
//        {
//            case EntityType::PLAYER:
//            {
//                using namespace Serialization;
//                PlayerController * player = new PlayerController(deserialize<PlayerController>(jsonEntities[i]));
//
//                // stupid simple hackery, bad bad
//                player->transform = &scene.renderers[i]->transform;
//                player->camera = &scene.camera;
//                player->cameraOffset = scene.camera.position;
//
//                auto animationObject = document["Sprites"].GetArray()[0].GetObject();
//
//                SpriteAnimator *animator = new SpriteAnimator(
//                    scene.shaders[shaderName].id,
//                    ParseJsonAnimation(animationObject)
//                );
//
//                player->renderer = scene.renderers[i];
//
//                scene.renderers[i]->animator = animator;
//                player->animator = animator;
//                scene.entities[entityIndex] = player;
//
//                entityIndex++;
//            }
//            break;
//        }
//
//    }

    int rendererIndex = entityCount;
    for (int i = 0; i < sceneryCount; i++)
    {
        string shaderName = sceneries[i].shaderName;
        scene.LoadShaderIfNotLoader(shaderName);

        Mesh * mesh = new Mesh;
        AssetLoader::LoadOBJ(sceneries[i].modelPath.c_str(), mesh);
        mesh->LoadToGL(scene.shaders[shaderName].id);

        GLuint texture;
        AssetLoader::LoadTextureRGBA(sceneries[i].texturePath.c_str(), &texture);

        for (int ii = 0; ii < sceneries[i].transforms.size(); ii++)
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
