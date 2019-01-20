/*
Leo Tamminen
Created 27/12/2018
*/

#pragma once

#include "Actor.hpp"
#include "AssetLoader.hpp"
#include "Collections/Array.hpp"
//#include "Collections/Dictionary.hpp"

#include <unordered_map>
#include <string>

#include "Renderer.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Light.hpp"

#include "../Game/PlayerController.hpp"
#include "../Game/FishController.hpp"

#include <iostream>

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
            FileRecord(ActorType::Fish, vec3(-1, 0, 1), "Assets/fish_b.obj", "Assets/Fish_B_ColorRGB_SmoothA.png", "default"),
            FileRecord(ActorType::Player, vec3(0, 0, 0), "Assets/Quad.obj", "Assets/Fish_C_ColorRGB_SmoothA.png", "sprite")
        };

    }
}

namespace Engine::SceneLoader
{
    using Collections::Array;
    using namespace Game;
    using std::unordered_map;
    using std::string;

    class Scene
    {
    public:
        Camera camera;
        Light light;

        Array<Actor *> actors;
        Array<Renderer *> renderers;
        ShaderProgram shader;
        unordered_map<string, ShaderProgram> shaders;

    };

    Scene Load()
    {
        auto records = readFromFile();
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


}