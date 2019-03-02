/*
Shophorn Games
Leo Tamminen
Created 26/02/2019
*/

#pragma once

#include <GL/glew.h>

#include <string>
#include <unordered_map>

#include "../Serialization.hpp"

using textureHandle = GLuint;

struct textureLoadInfo
{
    constexpr static int RGBA = 0;
    constexpr static int RGB = 1;

    std::string path;
    int colorMode = RGBA;
};

class Textures
{
    struct textureInfo
    {
        textureHandle handle { 0 };
        textureLoadInfo loadInfo;
    };

    std::unordered_map<std::string, textureInfo> _nameInfoMap{};
public:
    void addLoadInfo(const serialization::Value & loadInfoValues);
    textureHandle getHandle(std::string name);
};

namespace resources
{
    inline Textures textures;
}


