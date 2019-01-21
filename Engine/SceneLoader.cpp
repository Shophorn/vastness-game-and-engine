/*
LeoTamminen
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
    // Mock scene "file"
    /*
    Type : Player
    Position : vec3
    Model : "path"
    Texture : "path"
    */

    enum ActorType
    {
        None,
        Player,
        Fish
    };

    struct FileRecord
    {
        const ActorType type;
        const vec3 position;
        const char * modelPath = nullptr;
        const char * texturePath = nullptr;
        const char * shaderName = nullptr;

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

    Collections::Array<FileRecord> readFromFile()
    {
        return {
                FileRecord(ActorType::Fish, vec3(-1, 0, 0), "Assets/fish_a.obj", "Assets/Fish_A_ColorRGB_SmoothA.png", "default"),
                FileRecord(ActorType::Fish, vec3(1, 0, 1), "Assets/fish_a.obj", "Assets/Fish_A_ColorRGB_SmoothA.png", "default"),
                FileRecord(ActorType::Fish, vec3(1, 0, 0), "Assets/fish_b.obj", "Assets/Fish_B_ColorRGB_SmoothA.png", "default"),
                FileRecord(ActorType::Fish, vec3(-1, 0, 1), "Assets/fish_b.obj", "Assets/Fish_B_ColorRGB_SmoothA.png", "sprite"),
                FileRecord(ActorType::Player, vec3(0, 0, 0), "Assets/Quad.obj", "Game/Assets/dude.png", "sprite")
        };
    }

    vector<FileRecord> readFromFile(string path)
    {
        const char * jsonFormat = FileOperations::ReadFile(path.c_str());
        rapidjson::Document doc;
        doc.Parse(jsonFormat);

        string type = doc["type"].GetString();
        std::cout << type;

        return vector<FileRecord>(0);
    }
}


Scene SceneLoader::Load(string path)
{
    auto records = readFromFile();
    int count = records.count();


    readFromFile(path);


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
        AssetLoader::LoadOBJ(records[i].modelPath, mesh);
        mesh->LoadToGL(scene.shaders[shaderName].id);

        GLuint texture;
        AssetLoader::LoadTextureRGBA(records[i].texturePath, &texture);

        scene.renderers[i] = new Renderer(Transform(records[i].position, vec3(0,0,0)), texture, mesh, &scene.shaders[shaderName]);

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