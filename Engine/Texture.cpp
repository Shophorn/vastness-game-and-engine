/*
LeoTamminen
Created 25/02/2019
*/

#include "Texture.hpp"
#include "ResourceManager.hpp"

template <>
TextureInstance instantiate (TextureAsset * asset)
{
    return TextureInstance{};
}