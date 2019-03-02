/*
LeoTamminen
Created 27/02/2019
*/

#include "Shaders.hpp"
#include "../Shader.hpp"
#include "../DEBUG.hpp"

void Shaders::addLoadInfo(const serialization::Value &loadInfoValues)
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

shaderHandle Shaders::getHandle(std::string name)
{
    assert(_nameInfoMap.find(name) != _nameInfoMap.end() && "name not found");

    auto * info = &_nameInfoMap[name];
    if (info->handle == 0)
    {
        _shaders.emplace_back(Shader::Load(info->path));
        info->handle = _shaders.size();
    }

    debug << info -> handle;
    return info->handle;
}