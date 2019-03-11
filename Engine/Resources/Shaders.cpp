/*
LeoTamminen
Created 27/02/2019
*/

#include "Shaders.hpp"
#include "../Rendering/Shader.hpp"
#include "../DEBUG.hpp"

Shader & shaderHandle::get() const
{
    return resources::shaders.get(*this);
}

void Shaders::addLoadInfo(const serialization::Value & loadInfoValues)
{
    auto jsonShaderArray = loadInfoValues.GetArray();
    for (const auto & item : jsonShaderArray)
    {
        auto obj = item.GetObject();
        auto name = obj["name"].GetString();
        auto path = obj["path"].GetString();
        _nameInfoMap.emplace( name, info{0, path} );
    }
}

shaderHandle Shaders::create(const std::string & vertexPath, const std::string & fragmentPath)
{
    _shaders.emplace_back(Shader::create(vertexPath, fragmentPath));
    return shaderHandle { _shaders.size() - 1 };
}