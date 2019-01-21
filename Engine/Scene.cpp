/*
LeoTamminen
Created 21/01/2019
*/

#include "Scene.hpp"

void Engine::Scene::LoadShaderIfNotLoader(std::string shaderName)
{
    if (shaders.find(shaderName) == shaders.end())
    {
        shaders.insert_or_assign(shaderName, ShaderProgram::Load(shaderName));
    }
}
