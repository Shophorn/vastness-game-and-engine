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

using shaderHandle = int;

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
    shaderHandle getHandle(std::string name);
    Shader get(shaderHandle handle) { return _shaders[handle - 1]; };

    const auto begin() { return _shaders.cbegin(); }
    const auto end() { return _shaders.cend(); }
};

namespace resources
{
    inline Shaders shaders;
}


