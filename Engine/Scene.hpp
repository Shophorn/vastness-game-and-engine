/*
LeoTamminen
Created 21/01/2019
*/

#pragma once

#include <unordered_map>
#include <string>

#include "Renderer.hpp"
#include "Camera.hpp"
#include "Light.hpp"


namespace Core
{
    using std::string;

    class Scene
    {
    public:
        Scene() {}

        Camera camera;
        Light light;

//        std::vector<Entity *> entities;
        std::vector<Renderer *> renderers;
        std::unordered_map <string, Shader> shaders;

        ~Scene() {}

        void LoadShaderIfNotLoader(string shaderName);

    };
}