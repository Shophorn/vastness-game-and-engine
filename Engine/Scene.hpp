/*
LeoTamminen
Created 21/01/2019
*/

#pragma once

#include <unordered_map>
#include <string>

#include "Entity.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include "Light.hpp"

#include "Collections/Array.hpp"

namespace Engine
{
    using namespace Collections;
    using std::unordered_map;
    using std::string;

    class Scene
    {
    public:
        Scene() {}

        Camera camera;
        Light light;

        Array<Entity *> actors;
        Array<Renderer *> renderers;
        unordered_map <string, ShaderProgram> shaders;

        ~Scene()
        {
            DeletePointersInArray(actors);
//            DeletePointersInArray(renderers);
        }

        void LoadShaderIfNotLoader(string shaderName);

    };
}