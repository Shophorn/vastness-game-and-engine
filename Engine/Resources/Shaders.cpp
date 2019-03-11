/*
LeoTamminen
Created 27/02/2019
*/

#include "Shaders.hpp"
#include "../Rendering/Shader.hpp"
#include "../DEBUG.hpp"

Shader & ShaderManager::Handle::get() const
{
    return manager->_shaders[index];
}

ShaderManager::Handle ShaderManager::create(const std::string & vertexPath, const std::string & fragmentPath)
{
    _shaders.emplace_back(Shader::create(vertexPath, fragmentPath));
    return Handle { _shaders.size() - 1, this };
}