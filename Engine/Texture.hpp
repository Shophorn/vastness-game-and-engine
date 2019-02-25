/*
Shophorn Games
Leo Tamminen
Created 25/02/2019
*/

#pragma once

#include <vector>
#include "ResourceManager.hpp"

struct TextureInstance
{
    GLuint textureID;
};

struct TextureAsset
{
    std::vector<float> pixelColours;
};

using texture_handle = InstanceHandle<TextureInstance>;

namespace core
{
    inline ResourceManager<TextureInstance, TextureAsset> textures {};
}