/*
Shophorn Games
Leo Tamminen
Created 27/02/2019
*/

#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "../Rendering/Shader.hpp"
#include "../Serialization.hpp"

struct shaderHandle
{
    int index;
    Shader & get() const;
};

class Shaders
{
    struct info
    {
        shaderHandle handle { 0 };
        std::string path;
    };

    std::unordered_map<std::string, info> _nameInfoMap{};
    std::vector <Shader> _shaders;

public:
    void addLoadInfo(const serialization::Value & loadInfoValues);
    shaderHandle create (const std::string & vertexPath, const std::string & fragmentPath);
    Shader & get(shaderHandle handle)
    { 
        return _shaders[handle.index];
    };

    const auto begin() { return _shaders.cbegin(); }
    const auto end() { return _shaders.cend(); }
};

namespace resources
{
    inline Shaders shaders;
}


