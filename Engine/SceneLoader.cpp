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

    struct FileRecord
    {
        ActorType type;
        vec3 position;
        string modelPath;
        string texturePath;
        string shaderName;

        FileRecord () : type(ActorType::None), position (vec3(0,0,0)) {}

        FileRecord (
                ActorType _type,
                vec3 _position,
                const char * _modelPath,
                const char * _texturePath,
                const char * _shaderName)
                :   type(_type),
                    position(_position),
                    modelPath (_modelPath),
                    texturePath(_texturePath),
                    shaderName(_shaderName)
        {}

    };

    Array<FileRecord> readFromFile(string path)
    {
        using namespace rapidjson;

        const char * jsonFormat = FileOperations::ReadFile(path.c_str());
        Document doc;
        doc.Parse(jsonFormat);

        const Value& actors = doc["Actors"];

        Array<FileRecord> records (actors.Size());

        for (int i = 0; i < actors.Size(); i++)
        {
            auto object = actors[i].GetObject();

            records[i] = FileRecord (
                GetActorType(object["type"].GetString()),
                GetVec3(object["position"].GetArray()),
                object["model"].GetString(),
                object["texture"].GetString(),
                object["shader"].GetString()
            );

        }
        return records;
    }
}

Scene SceneLoader::Load(string path)
{
    auto records = readFromFile(path);
    int count = records.count();

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
        string shaderName = records[i].shaderName;
        if (scene.shaders.find(shaderName) == scene.shaders.end())
        {
            ShaderProgram shader = ShaderProgram::Load(shaderName);
            scene.shaders.insert_or_assign(shaderName, shader);
        }

        Mesh * mesh = new Mesh;
        AssetLoader::LoadOBJ(records[i].modelPath.c_str(), mesh);
        mesh->LoadToGL(scene.shaders[shaderName].id);

        GLuint texture;
        AssetLoader::LoadTextureRGBA(records[i].texturePath.c_str(), &texture);

        scene.renderers[i] = new Renderer(Transform(records[i].position, vec3(0,0,0)), texture, mesh, &scene.shaders[shaderName]);

        // TODO: Move these to game section
        switch (records[i].type)
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