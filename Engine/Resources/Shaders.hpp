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



class ShaderManager
{
public:
    struct Handle
    {
        int index;
        ShaderManager * manager;
        Shader & get() const;
    };

    Handle create (const std::string & vertexPath, const std::string & fragmentPath);

    const auto begin() { return _shaders.cbegin(); }
    const auto end() { return _shaders.cend(); }

private:
    struct info
    {
        Handle handle { 0 };
        std::string path;
    };

    std::vector <Shader> _shaders;
};

using ShaderHandle = ShaderManager::Handle;

namespace resources
{
    inline ShaderManager shaders;
}
